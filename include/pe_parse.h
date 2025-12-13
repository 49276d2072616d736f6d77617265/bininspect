#pragma once
#include <stdint.h>
#include "inspect.h"

int pe_parse_minimal(const uint8_t *data, uint64_t size, PeInfo *out);
