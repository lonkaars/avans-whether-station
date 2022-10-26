#include <stm32f0xx_hal.h>
#include <FreeRTOS.h>
#include <task.h>

#include "setup.h"

uint8_t tx_buffer[] = "AT\r\n";

void ws_test_read_task() {
	uint8_t* buf; // TODO: not working
	while (1) {
		HAL_UART_Receive_DMA(&huart1, buf, 1);
		HAL_UART_Transmit(&huart2, buf, 1, 100);
	}
}

void ws_test_write_task() {
	while (1) {
		HAL_UART_Transmit_DMA(&huart1, tx_buffer, sizeof(tx_buffer));
		__HAL_UART_ENABLE_IT(&huart1, UART_IT_TXE);

		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
		vTaskDelay(portTICK_PERIOD_MS * 1000 * 1);
	}
}
