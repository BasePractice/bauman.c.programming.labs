#ifndef BMAN_21_12_2020_FUNCTIONS_H
#define BMAN_21_12_2020_FUNCTIONS_H

#include <main.h>

DLL_EXPORT_API void export_prime(long long *dst, size_t dst_size);

DLL_EXPORT_API size_t copy(long long *dst, size_t dst_size, const long long *src, size_t src_size);

#endif //BMAN_21_12_2020_FUNCTIONS_H
