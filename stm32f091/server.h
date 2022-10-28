#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum {
	WS_SERVER_LM_CMD_ECHO, /** @brief listen for echo of sent command */
	WS_SERVER_LM_STATUS_CODE, /** @brief listen for busy, ERROR or OK */
	WS_SERVER_LM_IDLE, /** @brief listen for incoming +IPD commands */
	WS_SERVER_LM_IPD_LISTENING, /** @brief +IPD received, now reading data */
	WS_SERVER_LM_CIPSEND_LISTENING, /** @brief AT+CIPSEND sent, now reading data */
} ws_e_server_listen_mode;

typedef enum {
	WS_SERVER_CL_CHANNEL_ID, /** @brief listen channel id */
	WS_SERVER_CL_DATA_LENGTH, /** @brief listen for data byte length */
	WS_SERVER_CL_DATA_READ, /** @brief listen for data and pipe to ws_protocol_parse_req_byte */
} ws_e_channel_listen_mode;

typedef enum {
	WS_SERVER_RC_NONE = -1,
	WS_SERVER_RC_BUSY,
	WS_SERVER_RC_ERR,
	WS_SERVER_RC_OK,
} ws_e_server_response_code;

typedef struct {
	ws_e_server_listen_mode mode;
	ws_e_server_response_code last_response;
	unsigned int current_channel;
	unsigned int channel_data_length;
	unsigned int channel_data_counter;
	ws_e_channel_listen_mode channel_listen_mode;
	bool channel_data_ignore;
} ws_s_server_parser;

/** @brief global server parser struct */
extern ws_s_server_parser g_ws_server_parser;

/**
 * @brief +IPD incoming request handler
 *
 * this function takes chunks of data from the esp8266 and parses +IPD
 * commands. when a valid +IPD command is detected, it gets forwarded to
 * ws_protocol_parse_req_byte.
 *
 * @param data  pointer to data array
 * @param size  amount of bytes allowed to be read from `data`
 */
void ws_server_req_incoming(uint8_t* data, size_t size);

/** @brief send AT response header for incoming request on specific channel */
void ws_server_req_respond_start(unsigned int channel, size_t size);
/** @brief send AT tcp close on specific channel */
void ws_server_req_respond_end(unsigned int channel);

/** @brief send data to esp, waiting until server returns to idle mode */
void ws_server_send(uint8_t* data, size_t size);

/**
 * @brief parse byte from channel
 *
 * automatically creates parser struct and passes data onto protocol parser
 * functions
 *
 * @param channel  request channel
 * @param byte  data byte
 * @param ignore  ignore mode
 */
void ws_server_req_parse_byte(unsigned int channel, uint8_t byte, bool ignore);

/**
 * @brief close connection
 *
 * deallocates any parser struct that were automatically created in
 * ws_server_req_parse_byte
 *
 * @param channel  request channel
 * @param ignore  ignore mode
 */
void ws_server_req_finish(unsigned int channel, bool ignore);

void ws_server_buffer_send_append(uint8_t* data, size_t size);
void ws_server_buffer_send_finish();
