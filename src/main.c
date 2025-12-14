#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "inspect.h"
#include "json.h"
#include "strings.h"

static void print_usage(const char *prog) {
    fprintf(stderr, "Usage: %s [--json] [--strings] [--min-len N] <file>\n", prog);
}

int main(int argc, char **argv) {
    int json = 0;
    int do_strings = 0;
    int min_len = 4;
    const char *path = NULL;

    if (argc < 2) {
        print_usage(argv[0]);
        return 2;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--json") == 0) {
            json = 1;
        } else if (strcmp(argv[i], "--strings") == 0) {
            do_strings = 1;
        } else if (strcmp(argv[i], "--min-len") == 0 && i + 1 < argc) {
            min_len = atoi(argv[++i]);
            if (min_len <= 0) min_len = 4;
        } else {
            path = argv[i];
        }
    }

    if (!path) {
        print_usage(argv[0]);
        return 2;
    }

    InspectResult r;
    int rc = inspect_file(path, &r);
    if (rc != 0) {
        fprintf(stderr, "Error: failed to inspect file (code=%d)\n", rc);
        return 1;
    }

    // Strings policy:
    // - If --strings: extract for human output (and also available to JSON)
    // - If --json: extract automatically (even without --strings)
    StringsResult sr = {0};
    int want_strings = do_strings || json;

    if (want_strings) {
        StringsCfg cfg;
        cfg.min_len = min_len;
        cfg.max_results = 200;
        (void)strings_extract_ascii(r.data, r.size, &cfg, &sr);
    }

    if (json) {
        json_print_inspect(stdout, &r, want_strings ? &sr : NULL);

        // Optional: if user explicitly asked --strings too, print the human list after JSON
        if (do_strings && sr.count > 0) {
            for (size_t i = 0; i < sr.count; i++) {
                printf("%012llx: %s\n",
                    (unsigned long long)sr.hits[i].offset,
                    sr.hits[i].value);
            }
        }

        strings_result_free(&sr);
        inspect_result_free(&r);
        return 0;
    }

    printf("path: %s\n", r.path);
    printf("size: %llu bytes\n", (unsigned long long)r.size);
    printf("type: %s\n", r.type_str);

    printf("magic(16): ");
    for (int i = 0; i < 16 && (unsigned long long)i < r.size; i++) {
        printf("%02X", r.magic16[i]);
        if (i != 15) printf(" ");
    }
    printf("\n");

    printf("sha256: ");
    for (int i = 0; i < 32; i++) printf("%02x", r.sha256[i]);
    printf("\n");

    printf("entropy: %.4f bits/byte\n", r.entropy);

    if (do_strings && sr.count > 0) {
        for (size_t i = 0; i < sr.count; i++) {
            printf("%012llx: %s\n",
                (unsigned long long)sr.hits[i].offset,
                sr.hits[i].value);
        }
    }

    strings_result_free(&sr);
    inspect_result_free(&r);
    return 0;
}
