#pragma once
#include <stdint.h>
#include <stddef.h>

void magic_detect(const uint8_t *data, uint64_t size, char *out, int out_len);
