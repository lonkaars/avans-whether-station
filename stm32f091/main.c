#include <FreeRTOS.h>
#include <task.h>
#include <stm32f0xx.h>
#include <stdint.h>
#include <stm32f0xx_hal_gpio.h>

void task_1() {
	uint8_t led = 1;

	while (1) {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, led);
		led ^= 1;

		vTaskDelay(1000 / portTICK_RATE_MS);
	}
}

int main() {
	HAL_GPIO_Init(GPIOA, &(GPIO_InitTypeDef) {
		.Mode = GPIO_MODE_OUTPUT_PP,
		.Pull = GPIO_NOPULL,
		.Pin = GPIO_PIN_5
	});

	xTaskCreate(task_1, "task1", 128, NULL, 1, NULL);
	vTaskStartScheduler();
}
