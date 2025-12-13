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


typedef struct PeInfo {
    int present;
    uint16_t machine;
    uint16_t number_of_sections;
    uint32_t entry_rva;
    uint8_t  is_pe32_plus;   // 0=PE32, 1=PE32+
    uint64_t image_base;     // 32-bit or 64-bit stored here
    int parse_rc;
} PeInfo;

typedef struct InspectResult {
    char *path;
    uint64_t size;
    uint8_t magic16[16];
    char type_str[32];
    uint8_t sha256[32];
    double entropy;
    uint8_t *data;

    ElfInfo elf;
    PeInfo pe;
} InspectResult;



int inspect_file(const char *path, InspectResult *out);
void inspect_result_free(InspectResult *r);
