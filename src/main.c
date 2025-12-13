#include <stdio.h>
#include <string.h>

#include "inspect.h"
#include "json.h"

static void print_usage(const char *prog) {
    fprintf(stderr, "Usage: %s [--json] <file>\n", prog);
}

int main(int argc, char **argv) {
    int json = 0;
    const char *path = NULL;

    if (argc < 2) {
        print_usage(argv[0]);
        return 2;
    }

    // Accept either:
    //   bininspect <file>
    //   bininspect --json <file>
    //   bininspect <file> --json
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--json") == 0) {
            json = 1;
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

    if (json) {
        json_print_inspect(stdout, &r);
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

    inspect_result_free(&r);
    return 0;
}
