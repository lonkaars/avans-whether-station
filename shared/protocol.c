#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "protocol.h"

void ws_protocol_parse_byte(ws_s_protocol_parser_state* state, char input) {
  switch(input) {
    case WS_PROTOCOL_C_NEWLINE: {
      if (!state->valid) return;
      break;
    }

    case WS_PROTOCOL_C_SPACE: {
      if (!state->valid) return;
			state->arg_len++;
      return;
    }

    case WS_PROTOCOL_C_NULL: {
      state->valid = false;
      return;
    }

    default: {
      if (!state->valid) return;
      state->cmd[state->cmd_len++] = input;
      state->args_len[state->arg_len] += 1;
      if (state->cmd_len == WS_PROTOCOL_CMD_BUFFER_LEN) state->valid = false;
      return;
    }
  }
	// arg_len is used as an index while parsing, so add 1 to get length
	state->arg_len++;

	// parse cmd into argc and argv
	ws_protocol_cmd_init(state);
	// create response
	ws_s_protocol_response* response = ws_protocol_parse_finished(state->target);

	//TODO: send response
	char response_first_line[16];
	sprintf(response_first_line, "%s,%x\n", response->success == WS_PROTOCOL_CMD_RETURN_OK ? "ok" : "error", response->msg->bytes);
	ws_s_bin* response_first_line_bin = ws_bin_s_alloc(strlen(response_first_line));
	strncpy((char*) response_first_line_bin->data, response_first_line, strlen(response_first_line));
	ws_protocol_send_data(response_first_line_bin);
	ws_protocol_send_data(response->msg);
	
	free(response_first_line_bin);
	free(response->msg);
	free(response);

	//TODO: reset command in parser_state for next command

	return;
}

#define WS_CMD_MAP(parsed_cmd, name, code) \
	if (strlen(parsed_cmd->argv[0]) == strlen(name) && strncmp(parsed_cmd->argv[0], name, strlen(name)) == 0) return code;

static ws_e_protocol_cmd ws_protocol_get_cmd_code(ws_s_protocol_parsed_cmd* parsed_cmd) {
	WS_CMD_MAP(parsed_cmd, "last-records", WS_PROTOCOL_CMD_LAST_RECORDS);

	return WS_PROTOCOL_CMD_UNKNOWN;
}

ws_s_protocol_response* ws_protocol_parse_finished(ws_s_protocol_parsed_cmd* parsed_cmd) {
	ws_s_protocol_response* response = malloc(sizeof(ws_s_protocol_response));
	response->success = WS_PROTOCOL_CMD_RETURN_ERROR;
	response->msg = NULL;

	ws_e_protocol_cmd cmd_code = ws_protocol_get_cmd_code(parsed_cmd);
	if (cmd_code == WS_PROTOCOL_CMD_UNKNOWN) goto ws_protocol_parse_exit;
	if (cmd_code >= WS_PROTOCOL_CMD_AMOUNT) goto ws_protocol_parse_exit;

	void (*ws_protocol_res_handler)(ws_s_protocol_parsed_cmd*, ws_s_protocol_response*) =
		g_ws_protocol_res_handlers[cmd_code];
	if (ws_protocol_res_handler == NULL) goto ws_protocol_parse_exit;
	(*ws_protocol_res_handler)(parsed_cmd, response);

ws_protocol_parse_exit:

	if (response->msg == NULL) response->msg = ws_bin_s_alloc(0);
	return response;
}

void ws_protocol_parse_bytes(ws_s_protocol_parser_state* state, char* input, unsigned int length) {
  for (unsigned int i = 0; i < length; i++) ws_protocol_parse_byte(state, input[i]);
}

ws_s_protocol_parser_state* ws_protocol_parser_alloc() {
  ws_s_protocol_parser_state* parser_state = malloc(sizeof(ws_s_protocol_parser_state) + sizeof(uint16_t) * WS_PROTOCOL_CMD_MAX_ARGUMENTS);
  parser_state->cmd = malloc(sizeof(char) * WS_PROTOCOL_CMD_BUFFER_LEN);
  parser_state->valid = true;
  parser_state->cmd_len = 0;
  parser_state->arg_len = 0;
  parser_state->target = NULL;
  return parser_state;
}

void ws_protocol_cmd_init(ws_s_protocol_parser_state* state) {
  state->target = malloc(sizeof(ws_s_protocol_parsed_cmd) + sizeof(char*) * state->arg_len);
  for (unsigned int i = 0; i < state->arg_len; i++)
    state->target->argv[i] = malloc(sizeof(char) * (state->args_len[i] + 1));

  state->target->argc = state->arg_len;

	unsigned int head = 0;
	for (unsigned int i = 0; i < state->arg_len; i++) {
		strncpy(state->target->argv[i], &state->cmd[head], state->args_len[i]);
		state->target->argv[i][state->args_len[i]] = 0x00; // terminate argument with null byte
		head += state->args_len[i];
	}
}

void ws_protocol_parser_free(ws_s_protocol_parser_state* state) {
  if (state == NULL) return;
  if (state->target != NULL) ws_protocol_cmd_free(state->target);
  free(state->cmd);
  free(state);
  state = NULL;
  return;
}

void ws_protocol_cmd_free(ws_s_protocol_parsed_cmd* cmd) {
  for (unsigned int i = 0; i < cmd->argc; i++)
    free(cmd->argv[i]);
  free(cmd);
  cmd = NULL;
  return;
}
