#include <stdlib.h>

#include "backlog.h"

ws_s_backlog_database* WS_G_BACKLOG_DATABASE = NULL;

void ws_backlog_alloc(uint16_t record_amt) {
	WS_G_BACKLOG_DATABASE = malloc(sizeof(ws_s_backlog_database) + sizeof(ws_s_backlog_record) * record_amt);
	WS_G_BACKLOG_DATABASE->buffer_size = record_amt;
	WS_G_BACKLOG_DATABASE->buffer_start = 0;
	WS_G_BACKLOG_DATABASE->buffer_end = 0;
}

void ws_backlog_add_record(ws_s_backlog_record record) {
	static uint16_t id = 0;

	WS_G_BACKLOG_DATABASE->records[WS_G_BACKLOG_DATABASE->buffer_end].id = id++;
	WS_G_BACKLOG_DATABASE->records[WS_G_BACKLOG_DATABASE->buffer_end].sens_atm_pressure = record.sens_atm_pressure;
	WS_G_BACKLOG_DATABASE->records[WS_G_BACKLOG_DATABASE->buffer_end].sens_humidity = record.sens_humidity;
	WS_G_BACKLOG_DATABASE->records[WS_G_BACKLOG_DATABASE->buffer_end].sens_temperature = record.sens_temperature;

	// shift buffer start/end
	WS_G_BACKLOG_DATABASE->buffer_end = (WS_G_BACKLOG_DATABASE->buffer_end + 1) % WS_G_BACKLOG_DATABASE->buffer_size;
	if (WS_G_BACKLOG_DATABASE->buffer_end == WS_G_BACKLOG_DATABASE->buffer_start)
		WS_G_BACKLOG_DATABASE->buffer_start = (WS_G_BACKLOG_DATABASE->buffer_start + 1) % WS_G_BACKLOG_DATABASE->buffer_size;
}

ws_s_backlog_record* ws_backlog_get_record(uint16_t record_index) {
	return &WS_G_BACKLOG_DATABASE->records[record_index];
}

ws_s_backlog_record* ws_backlog_get_last_record(uint16_t record_offset) {
	return ws_backlog_get_record((WS_G_BACKLOG_DATABASE->buffer_end - record_offset - 1) % WS_G_BACKLOG_DATABASE->buffer_size);
}
