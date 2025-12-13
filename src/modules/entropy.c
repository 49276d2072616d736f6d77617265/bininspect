#include <math.h>
#include "entropy.h"

double shannon_entropy_bits_per_byte(const uint8_t *data, size_t n) {
    if (!data || n == 0) return 0.0;

    unsigned long long freq[256] = {0};
    for (size_t i = 0; i < n; i++) freq[data[i]]++;

    double ent = 0.0;
    const double inv = 1.0 / (double)n;

    for (int b = 0; b < 256; b++) {
        if (freq[b] == 0) continue;
        double p = (double)freq[b] * inv;
        ent -= p * (log(p) / log(2.0));
    }
    return ent; // bits per byte
}
