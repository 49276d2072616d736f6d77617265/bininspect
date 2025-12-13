#include <string.h>
#include "pe_parse.h"
#include "endian.h"

int pe_parse_minimal(const uint8_t *d, uint64_t n, PeInfo *out) {
    
    if (!d || !out || n < 0x40) return 1;
    memset(out, 0, sizeof(*out));

    // "MZ"
    if (d[0] != 'M' || d[1] != 'Z') return 2;

    uint32_t pe_off = read_u32_le(d + 0x3C);
    if ((uint64_t)pe_off + 4 + 20 > n) return 3;

    // "PE\0\0"
    if (!(d[pe_off]=='P' && d[pe_off+1]=='E' && d[pe_off+2]==0 && d[pe_off+3]==0)) return 4;

    const uint8_t *coff = d + pe_off + 4;

    out->present = 1;
    out->machine = read_u16_le(coff + 0);
    out->number_of_sections = read_u16_le(coff + 2);

    uint16_t opt_size = read_u16_le(coff + 16);
    const uint8_t *opt = coff + 20;
    if ((uint64_t)(opt - d) + opt_size > n) return 5;

    uint16_t magic = read_u16_le(opt + 0); // 0x10b PE32, 0x20b PE32+
    if (magic == 0x10b) {
        out->is_pe32_plus = 0;
        out->entry_rva = read_u32_le(opt + 16);
        out->image_base = (uint64_t)read_u32_le(opt + 28);
        return 0;
    } else if (magic == 0x20b) {
        out->is_pe32_plus = 1;
        out->entry_rva = read_u32_le(opt + 16);
        out->image_base = read_u64_le(opt + 24);
        return 0;
    }

    return 6; // unknown optional header magic
}
