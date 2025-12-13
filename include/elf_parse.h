#pragma once
#include <stdint.h>
#include "inspect.h"

int elf_parse_minimal(const uint8_t *data, uint64_t size, ElfInfo *out);
