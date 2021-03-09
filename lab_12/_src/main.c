#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdarg.h>
#include <main.h>
#if defined(WIN32) || defined(_MSC_VER)

#include <Windows.h>
#define dlopen(n, m) LoadLibrary(n)
#define dlsym(h, s)  GetProcAddress(h, s)
#define dlerror()    "unknown"
#define RTLD_NOW 0
#else
#include <dlfcn.h>
#endif


void *llibrary_load(const char *name) {
    return dlopen(name, RTLD_NOW);
}

void *llibrary_sym(void *library, const char *name) {
    return dlsym(library, name);
}

void  llibrary_free(void *library) {

}
