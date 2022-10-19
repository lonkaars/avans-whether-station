#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>

#include "protocol.h"
#include "backlog.h"
#include "util.h"

void ws_protocol_res_last_records(ws_s_protocol_parsed_req_cmd* parsed_cmd, ws_s_protocol_res* response, bool send) {
	static unsigned int record_amount = 0;
	const char* response_header = "id,temperature,humidity,atmospheric_pressure\n";
	const size_t response_line_size = sizeof("xxxx,xx,xx,xx\n");

	if (!send) {
		response->success = WS_PROTOCOL_CMD_RETURN_OK;
		if (sscanf(parsed_cmd->argv[1], "%u", &record_amount) < 1) response->success = WS_PROTOCOL_CMD_RETURN_ERROR;
		record_amount = WS_MIN(record_amount, ws_backlog_get_record_count());
		response->csh = true;
		response->msg = ws_bin_s_alloc(0);
		response->msg->bytes = strlen(response_header) + response_line_size * record_amount;
	} else {
		// example send routine
		ws_protocol_send_data(response_header, strlen(response_header));
		char line[response_line_size + 1]; // +1 for null terminator -> sprintf
		for (unsigned int i = 0; i < record_amount; i++) {
			ws_s_backlog_record* record = ws_backlog_get_last_record(i);
			sprintf(line, "%04x,%02x,%02x,%02x\n", record->id, record->sens_temperature, record->sens_humidity, record->sens_atm_pressure);
			ws_protocol_send_data(line, response_line_size);
		}
	}
}

void ws_protocol_send_data(const char* data, unsigned int length) {
	printf("%.*s", length, data);
}

int main() {
	ws_backlog_alloc(10);

  // disable echo and enable raw mode
  fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
  struct termios term;
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag &= ~(ECHO | ICANON);
  term.c_cc[VTIME] = 0;
  term.c_cc[VMIN] = 1;
  tcsetattr(STDIN_FILENO, 0, &term);

  ws_s_protocol_req_parser_state* parser1 = ws_protocol_req_parser_alloc();

	ws_backlog_add_record((ws_s_backlog_record) {
		.sens_temperature = 0x29,
		.sens_humidity = 0x34,
		.sens_atm_pressure = 0x69,
	});

	ws_backlog_add_record((ws_s_backlog_record) {
		.sens_temperature = 0x00,
		.sens_humidity = 0x00,
		.sens_atm_pressure = 0x00,
	});

	ws_backlog_add_record((ws_s_backlog_record) {
		.sens_temperature = 0x01,
		.sens_humidity = 0x01,
		.sens_atm_pressure = 0x01,
	});

	fflush(stdout);

	char byte;
	while(read(STDIN_FILENO, &byte, 1) > 0)
		ws_protocol_parse_req_byte(parser1, byte);

	ws_protocol_req_parser_free(parser1);
	parser1 = NULL;

  return 0;
}
