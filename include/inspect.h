#pragma once
#include <stdint.h>

typedef struct InspectResult {
    char *path;
    uint64_t size;
    uint8_t magic16[16];
    char type_str[32];
    uint8_t sha256[32];
    double entropy;

    // internal buffer (MVP: we keep file in memory)
    uint8_t *data;
} InspectResult;

int inspect_file(const char *path, InspectResult *out);
void inspect_result_free(InspectResult *r);
