#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>

#include "protocol.h"

void ws_protocol_res_last_records(ws_s_protocol_parsed_req_cmd* parsed_cmd, ws_s_protocol_res* response, bool send) {
	const char* response_text = ""
		"id,temperature,humidity,atmospheric_pressure\n"
		"10dc,2f,c5,7f\n"
		"10dd,30,c6,7f\n"
		"10de,31,c7,7f\n"
		"10df,35,ca,7e\n"
		"10e0,34,c9,7e\n";

	if (!send) {
		response->success = WS_PROTOCOL_CMD_RETURN_OK;
		response->csh = true;
		response->msg = ws_bin_s_alloc(0);
		response->msg->bytes = strlen(response_text);
	} else {
		// example send routine
		ws_s_bin* response_test = ws_bin_s_alloc(strlen(response_text));
		strncpy((char*) response_test->data, response_text, strlen(response_text));
		ws_protocol_send_data(response_test);
	}
}

void ws_protocol_send_data(ws_s_bin* data) {
	printf("%.*s", data->bytes, data->data);
}

int main() {
  // disable echo and enable raw mode
  fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
  struct termios term;
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag &= ~(ECHO | ICANON);
  term.c_cc[VTIME] = 0;
  term.c_cc[VMIN] = 1;
  tcsetattr(STDIN_FILENO, 0, &term);

  ws_s_protocol_req_parser_state* parser1 = ws_protocol_req_parser_alloc();

	fflush(stdout);

	char byte;
	while(read(STDIN_FILENO, &byte, 1) > 0)
		ws_protocol_parse_req_byte(parser1, byte);

	ws_protocol_req_parser_free(parser1);
	parser1 = NULL;

  return 0;
}
