#include <stm32f0xx_hal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../shared/protocol.h"
#include "esp8266.h"
#include "server.h"
#include "setup.h"
#include "consts.h"
#include "util.h"

ws_s_server_parser g_ws_server_parser = {
	.last_response = WS_SERVER_RC_NONE,
	.mode = WS_SERVER_LM_IDLE,

	.current_channel = 0,
	.channel_data_length = 0,
	.channel_data_counter = 0,
	.channel_listen_mode = WS_SERVER_CL_CHANNEL_ID,
};

static ws_s_protocol_req_parser_state* g_ws_protocol_parsers[WS_SERVER_MAX_CHANNELS] = {0};
static unsigned int g_ws_esp8266_dma_tx_buffer_size = 0;

void ws_server_req_parse_byte(unsigned int channel, uint8_t byte, bool ignore) {
	if (ignore) return;
	if (channel >= WS_SERVER_MAX_CHANNELS) return;

	if (g_ws_protocol_parsers[channel] == NULL) {
		g_ws_protocol_parsers[channel] = ws_protocol_req_parser_alloc();
	}

	ws_protocol_parse_req_byte(g_ws_protocol_parsers[channel], byte);
}

void ws_server_req_finish(unsigned int channel, bool ignore) {
	if (ignore) return;
	if (channel >= WS_SERVER_MAX_CHANNELS) return;
	
	if (g_ws_protocol_parsers[channel] != NULL) {
		ws_protocol_req_parser_free(g_ws_protocol_parsers[channel]);
		g_ws_protocol_parsers[channel] = NULL;
	}
}

// TODO: next_few_bytes_are assumes that the complete search string is in the
// buffer, so won't work for buffer cutoffs
#define next_few_bytes_are(code) (((i + sizeof(code) - 2) < size) && (strncmp((char*)&data[i], code, sizeof(code) - 1) == 0))
void ws_server_req_incoming(uint8_t* data, size_t size) {
#ifdef WS_DBG_PRINT_ESP_OVER_USART2
	ws_dbg_set_usart2_tty_color(1);
	HAL_UART_Transmit(&huart2, data, size, 100);
#endif

	for (unsigned int i = 0; i < size; i++) {
		uint8_t byte = data[i];

		switch (g_ws_server_parser.mode) {
			case WS_SERVER_LM_CMD_ECHO: {
				if (byte == '\n') g_ws_server_parser.mode = WS_SERVER_LM_STATUS_CODE;
				break;
			}
			case WS_SERVER_LM_STATUS_CODE: {
				bool code_got = false;
				if (next_few_bytes_are("OK")) {
					code_got = true;
					g_ws_server_parser.last_response = WS_SERVER_RC_OK;
				} else if (next_few_bytes_are("ERROR") || next_few_bytes_are("FAIL")) {
					code_got = true;
					g_ws_server_parser.last_response = WS_SERVER_RC_ERR;
				} else if (next_few_bytes_are("busy p...")) {
					code_got = true;
					g_ws_server_parser.last_response = WS_SERVER_RC_BUSY;
				}
				if (code_got) g_ws_server_parser.mode = WS_SERVER_LM_IDLE;
				break;
			}
			case WS_SERVER_LM_IDLE: {
				if (next_few_bytes_are("+IPD,")) {
					i += 4; // skip I, P, D, and comma
					g_ws_server_parser.mode = WS_SERVER_LM_IPD_LISTENING;
				} else if (next_few_bytes_are("> ")) {
					g_ws_server_parser.mode = WS_SERVER_LM_CIPSEND_LISTENING;
					ws_server_buffer_send_finish();
				}
				break;
			}
			case WS_SERVER_LM_IPD_LISTENING: {
					switch (g_ws_server_parser.channel_listen_mode) {
						case WS_SERVER_CL_CHANNEL_ID: {
							if (byte == ',') {
								g_ws_server_parser.channel_listen_mode = WS_SERVER_CL_DATA_LENGTH;
								break;
							}
							g_ws_server_parser.current_channel *= 10;
							g_ws_server_parser.current_channel += byte - '0'; // ascii to int
							break;
						}
						case WS_SERVER_CL_DATA_LENGTH: {
							if (byte == ':') {
								g_ws_server_parser.channel_listen_mode = WS_SERVER_CL_DATA_READ;
								if (g_ws_server_parser.channel_data_length > WS_PROTOCOL_CMD_BUFFER_LEN)
									g_ws_server_parser.channel_data_ignore = true;
								break;
							}
							g_ws_server_parser.channel_data_length *= 10;
							g_ws_server_parser.channel_data_length += byte - '0'; // ascii to int
							break;
						}
						case WS_SERVER_CL_DATA_READ: {
							ws_server_req_parse_byte(g_ws_server_parser.current_channel, byte, g_ws_server_parser.channel_data_ignore);
							g_ws_server_parser.channel_data_counter++;
							if (g_ws_server_parser.channel_data_counter == g_ws_server_parser.channel_data_length) {
								g_ws_server_parser.current_channel = 0;
								g_ws_server_parser.channel_data_counter = 0;
								g_ws_server_parser.channel_data_length = 0;
								g_ws_server_parser.channel_listen_mode = WS_SERVER_CL_CHANNEL_ID;
								ws_server_req_finish(g_ws_server_parser.current_channel, g_ws_server_parser.channel_data_ignore);
								g_ws_server_parser.mode = WS_SERVER_LM_IDLE;
							}
							break;
						}
						default: {}
					}
				break;
			}
			case WS_SERVER_LM_CIPSEND_LISTENING: {
				if (next_few_bytes_are("SEND OK") || next_few_bytes_are("ERROR")) {
					ws_server_req_respond_end(0);
				}
				break;
			}
			default: {}
		}
	}
}

void ws_server_send(uint8_t* data, size_t size) {
	g_ws_server_parser.mode = WS_SERVER_LM_CMD_ECHO;
	ws_esp8266_send(data, size);
	while (g_ws_server_parser.mode != WS_SERVER_LM_IDLE) {};
}

void ws_server_buffer_send_append(uint8_t* data, size_t size) {
	// TODO: buffer overrun protection
	// while (!__HAL_DMA_GET_FLAG(&hdma_usart1_tx, DMA_FLAG_TC2)); // make sure buffer isn't used
	strncpy((char*) &g_ws_esp8266_dma_tx_buffer[g_ws_esp8266_dma_tx_buffer_size], (char*) data, size); // append string
	g_ws_esp8266_dma_tx_buffer_size += size; // shift head
}

// TODO: refactor this
void ws_server_buffer_send_finish() {
#ifdef WS_DBG_PRINT_ESP_OVER_USART2
	ws_dbg_set_usart2_tty_color(2);
	HAL_UART_Transmit(&huart2, g_ws_esp8266_dma_tx_buffer, g_ws_esp8266_dma_tx_buffer_size, 100);
#endif

	HAL_UART_Transmit_DMA(&huart1, g_ws_esp8266_dma_tx_buffer, g_ws_esp8266_dma_tx_buffer_size);
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_TXE);
	g_ws_esp8266_dma_tx_buffer_size = 0;
	while (!__HAL_DMA_GET_FLAG(&hdma_usart1_tx, DMA_FLAG_TC2));
}

// TODO: refactor this
void ws_server_req_respond_start(unsigned int channel, size_t size) {
	char* cmd = NULL;
	size_t len = asiprintf(&cmd, "AT+CIPSEND=%d,%d\r\n", channel, size);
	g_ws_server_parser.mode = WS_SERVER_LM_CMD_ECHO;
	ws_esp8266_send((uint8_t*) cmd, len);
	while (!__HAL_DMA_GET_FLAG(&hdma_usart1_tx, DMA_FLAG_TC2));
}

// TODO: refactor this
void ws_server_req_respond_end(unsigned int channel) {
	char* cmd = NULL;
	size_t len = asiprintf(&cmd, "AT+CIPCLOSE=%d\r\n", channel);
	g_ws_server_parser.mode = WS_SERVER_LM_CMD_ECHO;
	ws_esp8266_send((uint8_t*) cmd, len);
	while (!__HAL_DMA_GET_FLAG(&hdma_usart1_tx, DMA_FLAG_TC2));
}
