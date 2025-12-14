#include <stdlib.h>
#include <string.h>
#include "strings.h"

static int is_printable_ascii(uint8_t c) {
    return (c >= 0x20 && c <= 0x7E);
}

static int push_hit(StringsResult *r, uint64_t off, const uint8_t *buf, size_t len) {
    char *s = (char*)malloc(len + 1);
    if (!s) return 1;
    memcpy(s, buf, len);
    s[len] = '\0';

    size_t new_count = r->count + 1;
    StringHit *nh = (StringHit*)realloc(r->hits, new_count * sizeof(StringHit));
    if (!nh) {
        free(s);
        return 2;
    }

    r->hits = nh;
    r->hits[r->count].offset = off;
    r->hits[r->count].value = s;
    r->count = new_count;
    return 0;
}

int strings_extract_ascii(const uint8_t *data, uint64_t size, const StringsCfg *cfg, StringsResult *out) {
    if (!out) return 1;
    out->hits = NULL;
    out->count = 0;

    if (!data || size == 0) return 0;

    int min_len = (cfg && cfg->min_len > 0) ? cfg->min_len : 4;
    int max_results = (cfg && cfg->max_results > 0) ? cfg->max_results : 200;

    uint64_t i = 0;
    while (i < size) {
        if (!is_printable_ascii(data[i])) { i++; continue; }

        uint64_t start = i;
        while (i < size && is_printable_ascii(data[i])) i++;
        uint64_t len = i - start;

        if ((int)len >= min_len) {
            if ((int)out->count >= max_results) break;
            if (push_hit(out, start, data + start, (size_t)len) != 0) {
                strings_result_free(out);
                return 2;
            }
        }
    }

    return 0;
}

void strings_result_free(StringsResult *r) {
    if (!r) return;
    for (size_t i = 0; i < r->count; i++) free(r->hits[i].value);
    free(r->hits);
    r->hits = NULL;
    r->count = 0;
}
