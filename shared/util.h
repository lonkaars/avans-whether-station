#pragma once

#define WS_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define WS_MAX(a, b) (((a) > (b)) ? (a) : (b))

unsigned int ws_log16(unsigned int x);