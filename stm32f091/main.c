#include <stm32f0xx.h>
#include <stdint.h>

#define PORT GPIOA
#define PIN 5

int main() {
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN;

	PORT->MODER &= ~(0b11 << (PIN * 2));
	PORT->MODER |= (0b01 << (PIN * 2));

	uint8_t led = 1;

	while (1) {
		PORT->ODR &= ~(1 << PIN);
		PORT->ODR |= (led << PIN);
		led ^= 1;
		for (unsigned long i = 0; i < 50000; i++) asm("nop");
	}
}
