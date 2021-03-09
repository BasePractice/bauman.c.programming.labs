#ifndef BMAN_21_12_2020_MAIN_H
#define BMAN_21_12_2020_MAIN_H

#include <stdio.h>
#include <stdbool.h>

void *llibrary_load(const char *name);
void *llibrary_sym(void *library, const char *name);
void  llibrary_free(void *library);

#if defined(_MSC_VER)
#if defined(DLL_EXPORT)
#define DLL_EXPORT_API _declspec(dllexport)
#else
#define DLL_EXPORT_API _declspec(dllimport)
#endif
#else
#if defined(DLL_EXPORT)
#define DLL_EXPORT_API __attribute__ ((visibility ("default")))
#else
#define DLL_EXPORT_API
#endif
#endif

#if defined(WIN32) || defined(_MSC_VER)
#if defined(__GNUC__)
#define DLL_LIBRARY_PREFIX "lib"
#define DLL_LIBRARY_SUFFIX ".dll"
#else
#define DLL_LIBRARY_PREFIX ""
#define DLL_LIBRARY_SUFFIX ".dll"
#endif
#else
#if defined(__APPLE__)
#define DLL_LIBRARY_PREFIX "lib"
#define DLL_LIBRARY_SUFFIX ".dylib"
#else
#define DLL_LIBRARY_PREFIX "lib"
#define DLL_LIBRARY_SUFFIX ".so"
#endif
#endif

#endif //BMAN_21_12_2020_MAIN_H
