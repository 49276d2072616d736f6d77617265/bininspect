#include <string.h>
#include <stdio.h>
#include "magic.h"
#include "endian.h"

static void set_str(char *out, int out_len, const char *s) {
    if (out_len <= 0) return;
    snprintf(out, (size_t)out_len, "%s", s);
}

// Minimal PE check without windows headers:
// - Starts with "MZ"
// - e_lfanew at offset 0x3C points to "PE\0\0"
static int is_pe(const uint8_t *d, uint64_t n) {
    if (n < 0x40) return 0;
    if (d[0] != 'M' || d[1] != 'Z') return 0;
    uint32_t off = read_u32_le(d + 0x3C);
    if ((uint64_t)off + 4 > n) return 0;
    return (d[off] == 'P' && d[off+1] == 'E' && d[off+2] == 0 && d[off+3] == 0);
}

void magic_detect(const uint8_t *d, uint64_t n, char *out, int out_len) {
    if (!d || n == 0) { set_str(out, out_len, "EMPTY"); return; }

    // ELF
    if (n >= 4 && d[0] == 0x7F && d[1] == 'E' && d[2] == 'L' && d[3] == 'F') {
        set_str(out, out_len, "ELF");
        return;
    }

    // PE
    if (is_pe(d, n)) {
        set_str(out, out_len, "PE");
        return;
    }

    // PDF
    if (n >= 5 && d[0]=='%' && d[1]=='P' && d[2]=='D' && d[3]=='F' && d[4]=='-') {
        set_str(out, out_len, "PDF");
        return;
    }

    // ZIP
    if (n >= 4 && d[0]=='P' && d[1]=='K' && d[2]==0x03 && d[3]==0x04) {
        set_str(out, out_len, "ZIP");
        return;
    }

    // GZIP
    if (n >= 2 && d[0]==0x1F && d[1]==0x8B) {
        set_str(out, out_len, "GZIP");
        return;
    }

    // PNG
    if (n >= 8 &&
        d[0]==0x89 && d[1]=='P' && d[2]=='N' && d[3]=='G' &&
        d[4]==0x0D && d[5]==0x0A && d[6]==0x1A && d[7]==0x0A) {
        set_str(out, out_len, "PNG");
        return;
    }

    // JPEG
    if (n >= 3 && d[0]==0xFF && d[1]==0xD8 && d[2]==0xFF) {
        set_str(out, out_len, "JPEG");
        return;
    }

    // GIF
    if (n >= 6 && d[0]=='G' && d[1]=='I' && d[2]=='F' && d[3]=='8' &&
        (d[4]=='7' || d[4]=='9') && d[5]=='a') {
        set_str(out, out_len, "GIF");
        return;
    }

    // TAR (ustar at offset 257)
    if (n > 262 && d[257]=='u' && d[258]=='s' && d[259]=='t' && d[260]=='a' && d[261]=='r') {
        set_str(out, out_len, "TAR");
        return;
    }

    set_str(out, out_len, "UNKNOWN");
}
