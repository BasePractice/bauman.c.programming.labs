#include <math.h>
#include <functions.h>


DLL_EXPORT_API void export_prime(long long *dst, size_t dst_size) {
    unsigned long i, j, c = 0;

    if (dst_size >= 1) {
        dst[c++] = 2;
    }
    if (dst_size >= 2) {
        dst[c++] = 3;
    }

    for (i = 5; c < dst_size; ++i) {
        for (j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                break;
            } else if (j + 1 > sqrt(i)) {
                dst[c++] = i;
            }
        }
    }
}

DLL_EXPORT_API size_t copy(long long *dst, size_t dst_size, const long long *src, size_t src_size) {
    bool without_write = dst == 0;
    size_t src_i, dst_i;

    if (without_write)
        dst_size = src_size;

    for (src_i = 0, dst_i = 0; src_i < src_size && dst_i < dst_size; src_i++) {
        if ( src[src_i] % 2 == 0 && src_i + 1 < src_size ) {
            if (false == without_write) {
                dst[dst_i] = src[src_i + 1];
            }
            ++dst_i;
        }
    }
    return dst_i;
}
