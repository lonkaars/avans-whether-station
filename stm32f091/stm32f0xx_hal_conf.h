#pragma once

#define HSE_VALUE ((uint32_t)8000000)
#define HSE_STARTUP_TIMEOUT ((uint32_t)100)
#define HSI_VALUE ((uint32_t)8000000)
#define HSI_STARTUP_TIMEOUT ((uint32_t)5000)
#define HSI14_VALUE ((uint32_t)14000000)
#define HSI48_VALUE ((uint32_t)48000000)
#define LSI_VALUE ((uint32_t)40000)
#define LSE_VALUE ((uint32_t)32768)
#define LSE_STARTUP_TIMEOUT ((uint32_t)5000)

#define VDD_VALUE 3300U
#define TICK_INT_PRIORITY ((uint32_t)(1U<<__NVIC_PRIO_BITS) - 1U)

#define USE_RTOS 0U
#define PREFETCH_ENABLE 1U
#define INSTRUCTION_CACHE_ENABLE 0U
#define DATA_CACHE_ENABLE 0U
#define USE_SPI_CRC 0U

#define HAL_MODULE_ENABLED
#define HAL_UART_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_GPIO_MODULE_ENABLED
#define HAL_EXTI_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_I2C_MODULE_ENABLED

#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_rcc.h>
// #include <stm32f0xx_hal_dma.h>
#include <stm32f0xx_hal_gpio.h>
// #include <stm32f0xx_hal_cortex.h>
// #include <stm32f0xx_hal_flash.h>
// #include <stm32f0xx_hal_i2c.h>
// #include <stm32f0xx_hal_i2s.h>
// #include <stm32f0xx_hal_pwr.h>
// #include <stm32f0xx_hal_rtc.h>
// #include <stm32f0xx_hal_uart.h>
// #include <stm32f0xx_hal_usart.h>

#ifdef USE_FULL_ASSERT
#define assert_param(expr) ((expr) ? (void)0U : assert_failed((char *)__FILE__, __LINE__))
void assert_failed(char* file, uint32_t line);
#else
#define assert_param(expr) ((void)0U)
#endif
