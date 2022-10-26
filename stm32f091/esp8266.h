#pragma once

#include "consts.h"

#include <stdint.h>

extern char g_ws_esp8266_dma_rx_buffer[WS_DMA_RX_BUFFER_SIZE];

// void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *, uint16_t);
/** @brief This function handles DMA1 channel 2 to 3 and DMA2 channel 1 to 2 interrupts. */
void DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler(void);
/** @brief This function handles DMA1 channel 1 interrupt. */
void DMA1_Ch1_IRQHandler(void);
void USART1_IRQHandler(void);

void ws_esp8266_ATsendCommand(uint8_t* data);
int ws_esp8266_checkOK(uint8_t *receiveData,int length);
int ws_esp8266_receivingMsg(uint8_t *receiveData,int length);
int ws_esp8266_unlink(uint8_t *receiveData,int length);
void ws_esp8266_StartEsp();
void ws_esp8266_disconnect();
void ws_esp8266_mode();
void ws_esp8266_connect();
void ws_esp8266_serveraan();
void ws_esp8266_serveruit();
void ws_esp8266_mux();
void ws_esp8266_close();
