#include <stdlib.h>
#include <string.h>

#include "inspect.h"
#include "file_io.h"
#include "magic.h"
#include "hash_sha256.h"
#include "entropy.h"

#include "elf_parse.h"

int inspect_file(const char *path, InspectResult *out) {
    if (!path || !out) return 10;
    memset(out, 0, sizeof(*out));

    // out->path = strdup(path);
    // if (!out->path) return 11;
    size_t plen = strlen(path);
    out->path = (char*)malloc(plen + 1);
    if (!out->path) return 11;
    memcpy(out->path, path, plen + 1);


    FileData fd = {0};
    int rc = file_read_all(path, &fd);
    if (rc != 0) return 12;

    out->data = fd.data;
    out->size = fd.size;

    // magic16
    for (int i = 0; i < 16; i++) {
        out->magic16[i] = (fd.size > (uint64_t)i) ? fd.data[i] : 0;
    }

    // type detection
    magic_detect(fd.data, fd.size, out->type_str, (int)sizeof(out->type_str));

    // ELF minimal parse (only if type says ELF)
    if (strcmp(out->type_str, "ELF") == 0) {
        (void)elf_parse_minimal(fd.data, fd.size, &out->elf);
    }

    if (strcmp(out->type_str, "PE") == 0) {
        (void)pe_parse_minimal(fd.data, fd.size, &out->pe);
    }


    // sha256
    sha256_hash(fd.data, (size_t)fd.size, out->sha256);

    // entropy
    out->entropy = shannon_entropy_bits_per_byte(fd.data, (size_t)fd.size);

    // NOTE: ownership of fd.data transferred into out->data
    return 0;
}

void inspect_result_free(InspectResult *r) {
    if (!r) return;
    if (r->data) free(r->data);
    if (r->path) free(r->path);
    memset(r, 0, sizeof(*r));
}
