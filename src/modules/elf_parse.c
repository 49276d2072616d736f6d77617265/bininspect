#include <string.h>
#include "elf_parse.h"
#include "endian.h"

static uint16_t rd16(const uint8_t *p, int be) { return be ? read_u16_be(p) : read_u16_le(p); }
static uint32_t rd32(const uint8_t *p, int be) { return be ? read_u32_be(p) : read_u32_le(p); }
static uint64_t rd64(const uint8_t *p, int be) { return be ? read_u64_be(p) : read_u64_le(p); }

int elf_parse_minimal(const uint8_t *d, uint64_t n, ElfInfo *out) {
    if (!d || !out || n < 16) return 1;
    memset(out, 0, sizeof(*out));

    // magic
    if (!(d[0]==0x7F && d[1]=='E' && d[2]=='L' && d[3]=='F')) return 2;

    uint8_t cls  = d[4]; // EI_CLASS
    uint8_t data = d[5]; // EI_DATA
    int be = (data == 2);

    out->present = 1;
    out->elf_class = cls;
    out->elf_data = data;

    if (cls == 1) {
        if (n < 52) return 3;
        out->e_type    = rd16(d + 16, be);
        out->e_machine = rd16(d + 18, be);
        out->e_entry   = (uint64_t)rd32(d + 24, be);
        return 0;
    } else if (cls == 2) {
        if (n < 64) return 4;
        out->e_type    = rd16(d + 16, be);
        out->e_machine = rd16(d + 18, be);
        out->e_entry   = rd64(d + 24, be);
        return 0;
    }

    return 5;
}
