#include <stm32f0xx_hal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "server.h"

void ws_server_req_incoming(uint8_t* data, size_t size) {
	// TODO: server req incoming implementation
	//
	// example +IPD command:
	// +IPD,0,15:last-records 5\n
	//
	// TODO: protocol req response parser -> (ws_esp8622_at_send(data, channel) ?)

	return;
}
