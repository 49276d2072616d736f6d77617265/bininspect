#pragma once
#include <stdint.h>

uint16_t read_u16_le(const uint8_t *p);
uint32_t read_u32_le(const uint8_t *p);
uint64_t read_u64_le(const uint8_t *p);

uint16_t read_u16_be(const uint8_t *p);
uint32_t read_u32_be(const uint8_t *p);
uint64_t read_u64_be(const uint8_t *p);
