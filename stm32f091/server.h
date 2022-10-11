#pragma once

void ws_server_demo();

/** FreeRTOS task that listens for incoming requests from the esp */
void ws_server_listen_task();
