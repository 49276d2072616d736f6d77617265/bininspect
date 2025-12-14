#pragma once
#include <stddef.h>
#include <stdint.h>

typedef struct StringsCfg {
    int min_len;         // default 4
    int max_results;     // default 200
} StringsCfg;

typedef struct StringHit {
    uint64_t offset;
    char *value;         // heap
} StringHit;

typedef struct StringsResult {
    StringHit *hits;     // heap array
    size_t count;
} StringsResult;

int strings_extract_ascii(const uint8_t *data, uint64_t size, const StringsCfg *cfg, StringsResult *out);
void strings_result_free(StringsResult *r);
