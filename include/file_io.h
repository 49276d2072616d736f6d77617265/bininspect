#pragma once
#include <stdint.h>

typedef struct FileData {
    uint8_t *data;
    uint64_t size;
} FileData;

// Reads entire file into memory (MVP).
// Returns 0 on success.
int file_read_all(const char *path, FileData *out);
