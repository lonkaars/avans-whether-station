#include <FreeRTOS.h>
#include <task.h>
#include <stm32f0xx.h>
#include <stdint.h>

#define PORT GPIOA
#define PIN 5

void task_1(void *pv_parameters) {
	uint8_t led = 1;

	while (1) {
		PORT->ODR &= ~(1 << PIN);
		PORT->ODR |= (led << PIN);
		led ^= 1;

		vTaskDelay(200 / portTICK_RATE_MS);
		// for (unsigned int gert = 0; gert < 100000; gert++)
		// 	asm("nop");
	}
}

int main() {
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN;

	PORT->MODER &= ~(0b11 << (PIN * 2));
	PORT->MODER |= (0b01 << (PIN * 2));
	
	// task_1(0);
	xTaskCreate(task_1, "task1", 128, NULL, 1, NULL);
	vTaskStartScheduler();
}
