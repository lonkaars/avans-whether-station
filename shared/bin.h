#pragma once

#include <stdint.h>

typedef struct {
  uint16_t bytes;
  uint8_t data[];
} ws_s_bin;

/** allocate new ws_s_bin struct and fill with `*data` for `bytes` bytes */
ws_s_bin *ws_bin_s_alloc(uint16_t bytes, uint8_t *data);

