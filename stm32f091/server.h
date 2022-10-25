#pragma once

#include <stdlib.h>
#include <stdint.h>

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

