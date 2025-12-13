#pragma once
#include <stddef.h>
#include <stdint.h>

void sha256_hash(const uint8_t *data, size_t len, uint8_t out32[32]);
