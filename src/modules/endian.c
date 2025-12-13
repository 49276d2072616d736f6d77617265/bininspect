#include "endian.h"

uint16_t read_u16_le(const uint8_t *p) {
    return (uint16_t)(p[0] | ((uint16_t)p[1] << 8));
}
uint32_t read_u32_le(const uint8_t *p) {
    return (uint32_t)(p[0] |
        ((uint32_t)p[1] << 8) |
        ((uint32_t)p[2] << 16) |
        ((uint32_t)p[3] << 24));
}
uint64_t read_u64_le(const uint8_t *p) {
    return (uint64_t)read_u32_le(p) | ((uint64_t)read_u32_le(p + 4) << 32);
}

uint16_t read_u16_be(const uint8_t *p) {
    return (uint16_t)(((uint16_t)p[0] << 8) | p[1]);
}
uint32_t read_u32_be(const uint8_t *p) {
    return (uint32_t)(((uint32_t)p[0] << 24) |
        ((uint32_t)p[1] << 16) |
        ((uint32_t)p[2] << 8) |
        p[3]);
}
uint64_t read_u64_be(const uint8_t *p) {
    return ((uint64_t)read_u32_be(p) << 32) | (uint64_t)read_u32_be(p + 4);
}
