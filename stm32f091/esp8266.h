#pragma once

#include "consts.h"

#include <stdlib.h>
#include <stdint.h>

/** @brief null-terminated rx buffer string */
extern uint8_t g_ws_esp8266_dma_rx_buffer[WS_DMA_RX_BUFFER_SIZE];
/** @brief null-terminated tx buffer string */
extern uint8_t g_ws_esp8266_dma_tx_buffer[WS_DMA_TX_BUFFER_SIZE];

/** @brief DMA1 channel 2-3 & DMA2 channel 1-2 interrupt handler */
void DMA1_Ch2_3_DMA2_Ch1_2_IRQHandler(void);
/** @brief DMA1 channel 1 interrupt handler */
void DMA1_Ch1_IRQHandler(void);
/** @brief USART1 interrupt handler */
void USART1_IRQHandler(void);

/** @brief send response to incoming request on specific channel */
void ws_esp8266_res_send(unsigned int channel, uint8_t* data, size_t size);

/** @brief send data to esp over uart with dma */
void ws_esp8266_send(uint8_t* data, size_t size);

// TODO: remove/update/document/refactor these functions
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
