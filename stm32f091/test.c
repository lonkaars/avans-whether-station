#include <stm32f0xx_hal.h>
#include <FreeRTOS.h>
#include <task.h>

#include "esp8266.h"
#include "setup.h"
#include "util.h"

void ws_test_read_task() {
	uint8_t* buf; // TODO: not working
	while (1) {
		HAL_UART_Receive_DMA(&huart1, buf, 1);
		HAL_UART_Transmit(&huart2, buf, 1, 100);
	}
}

void ws_test_write_task() {
	uint8_t data[] = "AT\r\n";
	while (1) {
		ws_esp8266_send(data, sizeof(data));

		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		vTaskDelay(portTICK_PERIOD_MS * 1000 * 1);
	}
}
