#include <stdio.h>
#include <string.h>
#include "json.h"

static void json_escape(FILE *out, const char *s) {
    fputc('"', out);
    for (const unsigned char *p = (const unsigned char*)s; *p; p++) {
        unsigned char c = *p;
        switch (c) {
            case '\\': fputs("\\\\", out); break;
            case '"':  fputs("\\\"", out); break;
            case '\b': fputs("\\b", out); break;
            case '\f': fputs("\\f", out); break;
            case '\n': fputs("\\n", out); break;
            case '\r': fputs("\\r", out); break;
            case '\t': fputs("\\t", out); break;
            default:
                if (c < 0x20) fprintf(out, "\\u%04x", (unsigned)c);
                else fputc(c, out);
        }
    }
    fputc('"', out);
}

static void hex_bytes(FILE *out, const uint8_t *b, int n) {
    for (int i = 0; i < n; i++) fprintf(out, "%02x", b[i]);
}

void json_print_inspect(FILE *out, const InspectResult *r) {
    fprintf(out, "{");
    fprintf(out, "\"path\":"); json_escape(out, r->path ? r->path : "");
    fprintf(out, ",\"size\":%llu", (unsigned long long)r->size);
    fprintf(out, ",\"type\":"); json_escape(out, r->type_str);

    fprintf(out, ",\"magic16\":\"");
    for (int i = 0; i < 16 && (unsigned long long)i < r->size; i++) {
        fprintf(out, "%02x", r->magic16[i]);
    }
    fprintf(out, "\"");

    fprintf(out, ",\"sha256\":\""); hex_bytes(out, r->sha256, 32); fprintf(out, "\"");
    fprintf(out, ",\"entropy\":%.6f", r->entropy);

    // ELF extras (se preenchidos)
    if (r->elf.present) {
        fprintf(out, ",\"elf\":{");
        fprintf(out, "\"class\":%u", (unsigned)r->elf.elf_class);
        fprintf(out, ",\"endianness\":%u", (unsigned)r->elf.elf_data);
        fprintf(out, ",\"type\":%u", (unsigned)r->elf.e_type);
        fprintf(out, ",\"machine\":%u", (unsigned)r->elf.e_machine);
        fprintf(out, ",\"entry\":%llu", (unsigned long long)r->elf.e_entry);
        fprintf(out, "}");
    }

    fprintf(out, "}\n");
}
