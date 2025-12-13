#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "file_io.h"

int file_read_all(const char *path, FileData *out) {
    if (!path || !out) return 1;
    out->data = NULL;
    out->size = 0;

    FILE *f = fopen(path, "rb");
    if (!f) return 2;

    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return 3; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return 4; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return 5; }

    uint8_t *buf = (uint8_t*)malloc((size_t)sz);
    if (!buf) { fclose(f); return 6; }

    size_t readn = fread(buf, 1, (size_t)sz, f);
    fclose(f);

    if (readn != (size_t)sz) {
        free(buf);
        return 7;
    }

    out->data = buf;
    out->size = (uint64_t)sz;
    return 0;
}
