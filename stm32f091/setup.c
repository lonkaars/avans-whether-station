#include <stm32f0xx_hal.h>
#include <stm32f0xx_hal_rcc.h>
#include <stm32f0xx_hal_i2c.h>
#include <stm32f0xx_hal_uart.h>
#include <FreeRTOS.h>
#include <task.h>

#include "setup.h"

I2C_HandleTypeDef hi2c1 = {
	.Instance = I2C1,
	.Init.Timing = 0x2000090E,
	.Init.OwnAddress1 = 0,
	.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT,
	.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE,
	.Init.OwnAddress2 = 0,
	.Init.OwnAddress2Masks = I2C_OA2_NOMASK,
	.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE,
	.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE,
};

UART_HandleTypeDef huart1 = {
  .Instance = USART1,
  .Init.BaudRate = 115200,
  .Init.WordLength = UART_WORDLENGTH_8B,
  .Init.StopBits = UART_STOPBITS_1,
  .Init.Parity = UART_PARITY_NONE,
  .Init.Mode = UART_MODE_TX_RX,
  .Init.HwFlowCtl = UART_HWCONTROL_NONE,
  .Init.OverSampling = UART_OVERSAMPLING_16,
  .Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE,
  .AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
};

UART_HandleTypeDef huart2 = {
	.Instance = USART2,
	.Init.BaudRate = 115200,
	.Init.WordLength = UART_WORDLENGTH_8B,
	.Init.StopBits = UART_STOPBITS_1,
	.Init.Parity = UART_PARITY_NONE,
	.Init.Mode = UART_MODE_TX_RX,
	.Init.HwFlowCtl = UART_HWCONTROL_NONE,
	.Init.OverSampling = UART_OVERSAMPLING_16,
	.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE,
	.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT,
};

static void ws_io_clock_setup();
static void ws_io_i2c_setup();
static void ws_io_usart1_setup();
static void ws_io_usart2_setup();
static void ws_setup_error_handler();

void ws_io_setup() {
	HAL_Init();

	ws_io_clock_setup();
	ws_io_i2c_setup();
	ws_io_usart1_setup();
	ws_io_usart2_setup();
}

static void ws_io_clock_setup() {
	if (HAL_OK != HAL_RCC_OscConfig(&(RCC_OscInitTypeDef){
		.OscillatorType = RCC_OSCILLATORTYPE_HSI,
		.HSIState = RCC_HSI_ON,
		.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT,
		.PLL.PLLState = RCC_PLL_ON,
		.PLL.PLLSource = RCC_PLLSOURCE_HSI,
		.PLL.PLLMUL = RCC_PLL_MUL12,
		.PLL.PREDIV = RCC_PREDIV_DIV2,
	})) return ws_setup_error_handler();

	if (HAL_OK != HAL_RCC_ClockConfig(&(RCC_ClkInitTypeDef){
		.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1,
		.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK,
		.AHBCLKDivider = RCC_SYSCLK_DIV1,
		.APB1CLKDivider = RCC_HCLK_DIV1,
	}, FLASH_LATENCY_1)) return ws_setup_error_handler();

	if (HAL_RCCEx_PeriphCLKConfig(&(RCC_PeriphCLKInitTypeDef){
		.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_I2C1,
		.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1,
		.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI,
	}) != HAL_OK) return ws_setup_error_handler();
}

static void ws_io_i2c_setup() {
	if (HAL_I2C_Init(&hi2c1) != HAL_OK)
		return ws_setup_error_handler();
	if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
		return ws_setup_error_handler();
	if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
		return ws_setup_error_handler();
}

static void ws_io_usart1_setup() {
	if (HAL_UART_Init(&huart1) != HAL_OK)
		return ws_setup_error_handler();
}

static void ws_io_usart2_setup() {
	if (HAL_UART_Init(&huart2) != HAL_OK)
		return ws_setup_error_handler();
}

void HAL_MspInit() {
  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();
  HAL_NVIC_SetPriority(PendSV_IRQn, 3, 0);
}

void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c) {
  if(hi2c->Instance != I2C1) return;

	__HAL_RCC_GPIOB_CLK_ENABLE();
	HAL_GPIO_Init(GPIOB, &(GPIO_InitTypeDef) {
		.Pin = GPIO_PIN_8|GPIO_PIN_9, //TODO: use #defines in setup.h
		.Mode = GPIO_MODE_AF_OD,
		.Pull = GPIO_NOPULL,
		.Speed = GPIO_SPEED_FREQ_HIGH,
		.Alternate = GPIO_AF1_I2C1,
	});
	__HAL_RCC_I2C1_CLK_ENABLE();
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart) {
	if(huart->Instance == USART1) {
		__HAL_RCC_USART1_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		HAL_GPIO_Init(GPIOA, &(GPIO_InitTypeDef){
    	.Pin = WS_PINOUT_USART1_TX_PIN | WS_PINOUT_USART1_RX_PIN,
    	.Mode = GPIO_MODE_AF_PP,
    	.Pull = GPIO_NOPULL,
    	.Speed = GPIO_SPEED_FREQ_HIGH,
    	.Alternate = GPIO_AF1_USART1,
		});

    // USART1 interrupt Init
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
	} else if (huart->Instance == USART2) {
		__HAL_RCC_USART2_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		HAL_GPIO_Init(GPIOA, &(GPIO_InitTypeDef) {
			.Pin = WS_PINOUT_USART2_TX_PIN | WS_PINOUT_USART2_RX_PIN,
			.Mode = GPIO_MODE_AF_PP,
			.Pull = GPIO_NOPULL,
			.Speed = GPIO_SPEED_FREQ_LOW,
			.Alternate = GPIO_AF1_USART2,
		});
	}
}

void SysTick_Handler() {
	HAL_IncTick();
	if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED) xPortSysTickHandler();
}

static void ws_setup_error_handler() {
	__disable_irq();
	for(;;);
}

void NMI_Handler() {
	for(;;);
}

void HardFault_Handler() {
	for(;;);
}
