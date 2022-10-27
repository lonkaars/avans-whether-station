#include <stm32f0xx_hal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../shared/protocol.h"
#include "esp8266.h"
#include "server.h"
#include "setup.h"
#include "consts.h"

static ws_s_server_parser g_ws_server_parser = {
	.last_response = WS_SERVER_RC_NONE,
	.mode = WS_SERVER_LM_IDLE,

	.current_channel = 0,
	.channel_data_length = 0,
	.channel_data_counter = 0,
	.channel_listen_mode = WS_SERVER_CL_DATA_LENGTH,
};

static ws_s_protocol_req_parser_state* g_ws_protocol_parsers[WS_SERVER_MAX_CHANNELS] = {0};


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
#define next_few_bytes_are(code) (i + sizeof(code) - 1 < size && strncmp((char*)&data[i], code, sizeof(code) - 1) == 0)
void ws_server_req_incoming(uint8_t* data, size_t size) {
#ifdef WS_DBG_PRINT_ESP_OVER_USART2
	uint8_t red[] = { 0x1b, 0x5b, 0x33, 0x31, 0x6d };
	HAL_UART_Transmit(&huart2, red, sizeof(red), 100);
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
							g_ws_server_parser.current_channel *= 10;
							g_ws_server_parser.current_channel += byte - '0'; // ascii to int
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
							}
							break;
						}
						default: {}
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

void ws_server_req_respond(unsigned int channel, uint8_t* data, size_t size) {
	uint8_t Tx_send[]="AT+CIPSEND=0,LEN:";
	uint8_t Tx_close[]="AT+CIPCLOSE=0\r\n";
	return;
}

