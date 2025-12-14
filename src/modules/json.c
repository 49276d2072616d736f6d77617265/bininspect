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

void json_print_inspect(FILE *out, const InspectResult *r, const StringsResult *sr) {
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

    if (r->elf.present) {
        fprintf(out, ",\"elf\":{");
        fprintf(out, "\"class\":%u", (unsigned)r->elf.elf_class);
        fprintf(out, ",\"endianness\":%u", (unsigned)r->elf.elf_data);
        fprintf(out, ",\"type\":%u", (unsigned)r->elf.e_type);
        fprintf(out, ",\"machine\":%u", (unsigned)r->elf.e_machine);
        fprintf(out, ",\"entry\":%llu", (unsigned long long)r->elf.e_entry);
        fprintf(out, "}");
    }

    if (r->pe.present || r->pe.parse_rc != 0) {
        fprintf(out, ",\"pe\":{");
        fprintf(out, "\"present\":%d", r->pe.present);
        fprintf(out, ",\"parse_rc\":%d", r->pe.parse_rc);
        fprintf(out, ",\"machine\":%u", (unsigned)r->pe.machine);
        fprintf(out, ",\"sections\":%u", (unsigned)r->pe.number_of_sections);
        fprintf(out, ",\"entry_rva\":%u", (unsigned)r->pe.entry_rva);
        fprintf(out, ",\"pe32plus\":%u", (unsigned)r->pe.is_pe32_plus);
        fprintf(out, ",\"image_base\":%llu", (unsigned long long)r->pe.image_base);
        fprintf(out, "}");
    }

    if (sr && sr->count > 0) {
        fprintf(out, ",\"strings\":[");
        for (size_t i = 0; i < sr->count; i++) {
            if (i) fprintf(out, ",");
            fprintf(out, "{");
            fprintf(out, "\"offset\":%llu", (unsigned long long)sr->hits[i].offset);
            fprintf(out, ",\"value\":");
            json_escape(out, sr->hits[i].value ? sr->hits[i].value : "");
            fprintf(out, "}");
        }
        fprintf(out, "]");
    }

    fprintf(out, "}\n");
}
