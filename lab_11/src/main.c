#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdarg.h>
#include <main.h>

enum ParseState {
    PLAIN_TEXT, START_FORMAT, COMPLETE_FORMAT
};

enum Mod {
    MOD_NONE, MOD_L, MOD_H
};

enum Function {
    FUN_S, FUN_C, FUN_D, FUN_I, FUN_X, FUN_UNKNOWN
};

static inline int my_strlen(char *text) {
    char *start = text;
    while (*text) {
        ++text;
    }
    return (int) (text - start);
}

static void long_to_string(long n, char **out, size_t *len) {
    static char buf[(CHAR_BIT * sizeof(long) - 1) * 10 / 33 + 3];
    char *p = &buf[sizeof(buf) - 1];
    long i = n;

    *p = '\0';
    if (i >= 0) {
        i = -i;
    }
    do {
        p--;
        *p = (char) ('0' - i % 10);
        i /= 10;
    } while (i);
    if (n < 0) {
        p--;
        *p = '-';
    }
    *len = (size_t) (&buf[sizeof(buf)] - p) - 1;
    *out = p;
}

static int num_hex_digits(unsigned n) {
    if (!n) return 1;

    int ret = 0;
    for (; n; n >>= 4) {
        ++ret;
    }
    return ret;
}

static void long_to_hex(long n, char **out, size_t *len) {
    static char hex[((CHAR_BIT * sizeof(long) - 1) * 10 / 33 + 3) * 2];
    const char hex_lookup[] = "0123456789abcdef";
    char *h = &hex[sizeof(hex) - 1];
    int i = num_hex_digits(n);

    *len = i;
    if (i & 1) {
        *h++ = '0';
    }
    h[i] = '\0';

    for (--i; i >= 0; n >>= 4, --i) {
        h[i] = hex_lookup[n & 0xf];
    }
    *out = h;
}

int my_snprintf(char *s, size_t n, const char *format, ...) {
    int write = 0, would = 0;
    char *it;
    va_list args;
    bool write_on = true;
    enum Mod mode = MOD_NONE;
    enum Function fun = FUN_UNKNOWN;
    enum ParseState state = PLAIN_TEXT;

    va_start(args, format);
    it = (char *) format;
    while (0 != *it) {
        write_on = write < n;
        switch (state) {
            default:
            case PLAIN_TEXT: {
                if ('%' == (*it)) {
                    state = START_FORMAT;
                    break;
                }
                mode = MOD_NONE;
                if (write + 1 >= n) {
                    write_on = false;
                    s[write++] = 0;
                }
                if (write_on)
                    s[write++] = (*it);
                would++;
                break;
            }
            case COMPLETE_FORMAT: {
                switch (fun) {
                    case FUN_X: {
                        char *p = 0;
                        size_t len = 0;
                        long arg;
                        if (mode == MOD_L) {
                            arg = va_arg(args, long);
                        } else if (mode == MOD_H) {
                            arg = (short) va_arg(args, int);
                        } else {
                            arg = va_arg(args, int);
                        }
                        long_to_hex(arg, &p, &len);
                        if (write + len > n && write_on) {
                            int need_write = (write + len) - n - 2;
                            memcpy(s + write, p, need_write);
                            write += need_write;
                            write_on = false;
                            s[write] = 0;
                        } else {
                            memcpy(s + write, p, len);
                            write += len;
                        }
                        would += len;
                        break;
                    }
                    case FUN_D:
                    case FUN_I: {
                        char *p = 0;
                        size_t len = 0;
                        long arg;
                        if (mode == MOD_L) {
                            arg = va_arg(args, long);
                        } else if (mode == MOD_H) {
                            arg = (short) va_arg(args, int);
                        } else {
                            arg = va_arg(args, int);
                        }
                        long_to_string(arg, &p, &len);
                        if (write + len > n && write_on) {
                            int need_write = (write + len) - n - 2;
                            memcpy(s + write, p, need_write);
                            write += need_write;
                            write_on = false;
                            s[write] = 0;
                        } else {
                            memcpy(s + write, p, len);
                            write += len;
                        }
                        would += len;
                        break;
                    }
                    case FUN_S: {
                        if (mode == MOD_L) {
                            fprintf(stderr, "l mode to string not implement yet");
                            break;
                        }
                        char *arg = va_arg(args, char *);
                        int len = my_strlen(arg);
                        if (write + len > n && write_on) {
                            int need_write = (write + len) - n - 2;
                            memcpy(s + write, arg, need_write);
                            write += need_write;
                            write_on = false;
                        } else {
                            memcpy(s + write, arg, len);
                            write += len;
                        }
                        would += len;
                        break;
                    }
                    case FUN_C: {
                        if (mode == MOD_L) {
                            fprintf(stderr, "l mode to string not implement yet");
                            break;
                        }
                        int arg = va_arg(args, int);
                        if (write + 2 > n) {
                            write_on = false;
                            s[write++] = 0;
                        }
                        if (write_on)
                            s[write++] = (char) arg;
                        would += 1;
                        break;
                    }
                    default:
                        break;
                }
                state = PLAIN_TEXT;
                mode = MOD_NONE;
                fun = FUN_UNKNOWN;
                break;
            }
            case START_FORMAT: {
                if ('%' == (*it)) {
                    state = PLAIN_TEXT;
                    if (write_on)
                        s[write++] = '%';
                    would++;
                } else {
                    if ('l' == (*it)) {
                        mode = MOD_L;
                    } else if ('h' == (*it)) {
                        mode = MOD_H;
                    } else if ('s' == (*it)) {
                        state = COMPLETE_FORMAT;
                        fun = FUN_S;
                        continue;
                    } else if ('c' == (*it)) {
                        state = COMPLETE_FORMAT;
                        fun = FUN_C;
                        continue;
                    } else if ('x' == (*it)) {
                        state = COMPLETE_FORMAT;
                        fun = FUN_X;
                        continue;
                    } else if ('d' == (*it)) {
                        state = COMPLETE_FORMAT;
                        fun = FUN_D;
                        continue;
                    } else if ('i' == (*it)) {
                        state = COMPLETE_FORMAT;
                        fun = FUN_I;
                        continue;
                    }
                }
                break;
            }
        }
        ++it;
    }
    va_end(args);
    if (write <= n) {
        s[write] = 0;
    }
    return would;
}

#if defined(ENTRY_POINT)

int main(int argc, char **argv) {
    return EXIT_SUCCESS;
}

#endif
