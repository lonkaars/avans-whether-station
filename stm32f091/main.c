#include <FreeRTOS.h>
#include <task.h>
#include <stm32f0xx.h>
#include <stdint.h>
#include <stm32f0xx_hal.h>

void task_1() {
	// uint8_t led = 1;

	while (1) {
		// HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, led);
		// led ^= 1;
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

		vTaskDelay(1000 / portTICK_RATE_MS);
	}
}

int main() {
	HAL_Init();
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Pin = GPIO_PIN_5;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	xTaskCreate(task_1, "task1", 128, NULL, 1, NULL);
	vTaskStartScheduler();
}
