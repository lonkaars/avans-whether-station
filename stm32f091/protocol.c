#include <stdio.h>

#include "../shared/protocol.h"
#include "backlog.h"
#include "util.h"
#include "server.h"
#include "esp8266.h"

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
		ws_server_req_respond_start(0, response->msg->bytes + ws_protocol_get_header_size(response));
	} else {
		ws_protocol_send_data(response_header, strlen(response_header));
		char line[response_line_size + 1]; // +1 for null terminator -> sprintf
		for (unsigned int i = 0; i < record_amount; i++) {
			ws_s_backlog_record* record = ws_backlog_get_last_record(i);
			sprintf(line, "%04x,%02x,%02x,%02x\n", record->id, record->sens_temperature, record->sens_humidity, record->sens_atm_pressure);
			ws_protocol_send_data(line, response_line_size);
		}
		ws_protocol_send_data("\r\n", 2); // test
	}
}

void ws_protocol_send_data(const char* data, unsigned int length) {
	ws_server_buffer_send_append((uint8_t*) data, length);
	// HAL_UART_Transmit(&huart1, (uint8_t*) data, length, HAL_MAX_DELAY);
}
