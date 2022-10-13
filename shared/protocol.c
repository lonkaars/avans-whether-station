#include <stdio.h>
#include <stdlib.h>

#include "protocol.h"

void ws_protocol_parse_byte(ws_s_protocol_parser_state* state, char input) {
  switch(input) {
    case WS_PROTOCOL_C_NEWLINE: {
      if (!state->valid) return;
      break;
    }

    case WS_PROTOCOL_C_SPACE: {
      if (!state->valid) return;
      printf("argument delimiter\n");
      return;
    }

    case WS_PROTOCOL_C_NULL: {
      state->valid = false;
      return;
    }

    default: {
      if (!state->valid) return;
      printf("recv byte 0x%02x, (\"%c\")\n", input, input);
      state->cmd[state->cmd_len++] = input;
      state->args_len[state->arg_len] += 1;
      if (state->cmd_len == WS_PROTOCOL_CMD_BUFFER_LEN) state->valid = false;
      return;
    }
  }

  printf("command done!\n");
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
    state->target->argv[i] = malloc(sizeof(char) * state->args_len[i]);
  state->target->argc = state->arg_len;
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
