#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum {
	WS_SERVER_LM_CMD_ECHO, /** @brief listen for echo of sent command */
	WS_SERVER_LM_STATUS_CODE, /** @brief listen for busy, ERROR or OK */
	WS_SERVER_LM_IDLE, /** @brief listen for incoming +IPD commands */
	WS_SERVER_LM_IPD_LISTENING, /** @brief +IPD received, now reading data */
} ws_e_server_listen_mode;

typedef enum {
	WS_SERVER_RC_NONE = -1,
	WS_SERVER_RC_BUSY,
	WS_SERVER_RC_ERR,
	WS_SERVER_RC_OK,
} ws_e_server_response_code;

typedef struct {
	int counter;
	ws_e_server_listen_mode mode;
	ws_e_server_response_code last_response;
} ws_s_server_parser;

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

/** @brief send response to incoming request on specific channel */
void ws_server_req_respond(unsigned int channel, uint8_t* data, size_t size);

/** @brief send data to esp, waiting until server returns to idle mode */
void ws_server_send(uint8_t* data, size_t size);

