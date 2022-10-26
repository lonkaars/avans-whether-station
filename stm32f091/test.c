#include <stm32f0xx_hal.h>
#include <FreeRTOS.h>
#include <task.h>

#include "esp8266.h"

void ws_test_write_task() {
	uint8_t data[] = "AT\r\n";
	while (1) {
		ws_esp8266_send(data, sizeof(data));

		vTaskDelay(portTICK_PERIOD_MS * 100 * 1);
	}
}
