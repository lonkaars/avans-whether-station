#pragma once

#include <stdint.h>

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
