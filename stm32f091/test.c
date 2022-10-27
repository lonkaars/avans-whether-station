#include <stm32f0xx_hal.h>
#include <FreeRTOS.h>
#include <task.h>

#include "server.h"
#include "setup.h"

void ws_test_write_task() {
	uint8_t cmd1[] = "AT+CIPMUX=1\r\n";
	uint8_t cmd2[] = "AT+CWMODE=1\r\n";
	uint8_t cmd3[] = "AT+CWJAP=\"" WS_ESP8266_WLAN_SSID "\",\"" WS_ESP8266_WLAN_PASSWD "\"\r\n";
	while (1) {
		ws_server_send(cmd1, sizeof(cmd1));
		ws_server_send(cmd2, sizeof(cmd2));
		ws_server_send(cmd3, sizeof(cmd3));
		vTaskDelay(portTICK_PERIOD_MS * 1000 * 1);
	}
}
