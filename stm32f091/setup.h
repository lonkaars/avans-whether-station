#pragma once

#include <stm32f0xx_hal_i2c.h>
#include <stm32f0xx_hal_uart.h>

#define WS_PINOUT_I2C_SDA_PIN GPIO_PIN_9
#define WS_PINOUT_I2C_SDA_PORT GPIOB
#define WS_PINOUT_I2C_SCL_PIN GPIO_PIN_8
#define WS_PINOUT_I2C_SCL_PORT GPIOB
#define WS_PINOUT_USART_RX_PIN GPIO_PIN_3
#define WS_PINOUT_USART_RX_PORT GPIOA
#define WS_PINOUT_USART_TX_PIN GPIO_PIN_2
#define WS_PINOUT_USART_TX_PORT GPIOA

extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart2;

void ws_io_setup();

