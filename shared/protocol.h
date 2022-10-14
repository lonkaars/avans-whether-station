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

/**
 * @brief parsed cmd struct, holds arguments similar to argc and argv provided
 * to `int main()`
 */
typedef struct {
	int argc; /** argument count */
	char* argv[]; /** argument array, null terminated strings */
} ws_s_protocol_parsed_cmd;

/**
 * @brief holds parser state variables for `ws_protocol_parse_byte` function.
 * each incoming tcp request should get it's own parser 'instance'
 */
typedef struct {
	ws_s_protocol_parsed_cmd* target; /** parsed cmd reference */
	bool valid; /** command still valid flag */
	char* cmd; /** raw cmd */
	uint16_t cmd_len; /** raw cmd string length */
	uint16_t arg_len; /** amount of arguments */
	uint16_t args_len[]; /** array of argument lengths */
} ws_s_protocol_parser_state;

/** @brief return values for command handlers */
typedef enum {
	WS_PROTOCOL_CMD_RETURN_OK = 0,
	WS_PROTOCOL_CMD_RETURN_ERROR = 1,
} ws_e_protocol_cmd_return_value;

/** @brief request response data struct */
typedef struct {
	ws_e_protocol_cmd_return_value success;
	ws_s_bin* msg;
} ws_s_protocol_response;

/**
 * @brief allocate parser struct
 *
 * @return pointer to newly allocated struct
 */
ws_s_protocol_parser_state* ws_protocol_parser_alloc();
/** @brief deallocate parser struct, automatically frees all child pointers */
void ws_protocol_parser_free(ws_s_protocol_parser_state* state);
/**
 * @brief initialize ws_s_protocol_parsed_cmd struct pointer of
 * ws_s_protocol_parser_state (internal only)
 */
void ws_protocol_cmd_init(ws_s_protocol_parser_state* state);
/** @brief deallocate ws_s_protocol_parsed_cmd struct pointer (internal only) */
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
 * @brief handle complete command
 *
 * this function gets called when ws_protocol_parse_byte has detected a
 * finished command. this function decides which command handler gets called,
 * given that argv[0] contains a valid command. command argument parsing is
 * handled by the command handler function.
 *
 * @remark [server]
 *
 * @return response
 *
 * @param parsed_cmd  cmd parsed into ws_s_protocol_parsed_cmd struct
 */
ws_s_protocol_response* ws_protocol_parse_finished(ws_s_protocol_parsed_cmd* parsed_cmd);

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
 * @param response  response struct with uninitialized pointer to msg
 */
void ws_protocol_res_last_records(ws_s_protocol_parsed_cmd* parsed_cmd, ws_s_protocol_response* response);

/** @brief cmd codes (used to call handlers) */
typedef enum {
	WS_PROTOCOL_CMD_UNKNOWN = -1,

	WS_PROTOCOL_CMD_LAST_RECORDS = 0,
} ws_e_protocol_cmd;

/** @brief response handlers, called when a command is parsed */
static void (*g_ws_protocol_res_handlers[WS_PROTOCOL_CMD_AMOUNT])(ws_s_protocol_parsed_cmd*, ws_s_protocol_response*) = {
	[WS_PROTOCOL_CMD_LAST_RECORDS] = &ws_protocol_res_last_records
};

