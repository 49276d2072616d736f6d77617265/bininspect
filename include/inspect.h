#pragma once
#include <stdint.h>

typedef struct ElfInfo {
    int present;
    uint8_t elf_class; // 1=32, 2=64
    uint8_t elf_data;  // 1=LE, 2=BE
    uint16_t e_type;
    uint16_t e_machine;
    uint64_t e_entry;
} ElfInfo;

typedef struct InspectResult {
    char *path;
    uint64_t size;
    uint8_t magic16[16];
    char type_str[32];
    uint8_t sha256[32];
    double entropy;
    uint8_t *data;

    ElfInfo elf; // NEW
} InspectResult;


int inspect_file(const char *path, InspectResult *out);
void inspect_result_free(InspectResult *r);
