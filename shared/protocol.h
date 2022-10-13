#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "bin.h"

#define WS_PROTOCOL_CMD_MAX_ARGUMENTS (1)
#define WS_PROTOCOL_CMD_BUFFER_LEN (40)

#define WS_PROTOCOL_CMD_AMOUNT (1)

#define WS_PROTOCOL_C_NEWLINE (0x0a)
#define WS_PROTOCOL_C_SPACE (0x20)
#define WS_PROTOCOL_C_NULL (0x00)

typedef struct {
	int argc;
	char* argv[];
} ws_s_protocol_parsed_cmd;

typedef struct {
	ws_s_protocol_parsed_cmd* target;
	bool valid;
	char* cmd;
	uint16_t cmd_len;
	uint16_t arg_len;
	uint16_t args_len[];
} ws_s_protocol_parser_state;

//TODO: document
ws_s_protocol_parser_state* ws_protocol_parser_alloc();
void ws_protocol_parser_free(ws_s_protocol_parser_state* state);
void ws_protocol_cmd_init(ws_s_protocol_parser_state* state);
void ws_protocol_cmd_free(ws_s_protocol_parsed_cmd* cmd);

/**
 * @brief parse incoming data byte by byte until a finished command is detected
 *
 * @remark [server]
 *
 * @param state  parser state object, each incoming request should have it's own parser state
 * @param input  input byte
 */
void ws_protocol_parse_byte(ws_s_protocol_parser_state* state, char input);
/**
 * @brief parse incoming data chunk
 *
 * @remark [server]
 *
 * @param state  parser state object, each incoming request should have it's own parser state
 * @param input  input byte array
 * @param length  input byte array length
 */
void ws_protocol_parse_bytes(ws_s_protocol_parser_state* state, char* input, unsigned int length);

/**
 * @brief create a `last-records` request command
 * @remark [client]
 * @return ws_s_bin containing the command string
 */
ws_s_bin* ws_protocol_req_last_records(unsigned int record_amount);

/**
 * @brief `last-records` response handler
 *
 * @remark [server]
 *
 * gets fired when the weather station receives a complete `last-records`
 * command, and returns the response string
 *
 * @param parsed_cmd  complete parsed command from ws_protocol_parse_*
 *
 * @return ws_s_bin containing response string
 */
ws_s_bin* ws_protocol_res_last_records(ws_s_protocol_parsed_cmd* parsed_cmd);

typedef enum {
	WS_PROTOCOL_CMD_LAST_RECORDS = 0,
} ws_e_protocol_cmd;

static ws_s_bin* (*g_ws_protocol_res_handlers[WS_PROTOCOL_CMD_AMOUNT])(ws_s_protocol_parsed_cmd* parsed_cmd) = {
	[WS_PROTOCOL_CMD_LAST_RECORDS] = &ws_protocol_res_last_records
};

