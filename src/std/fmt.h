#ifndef STD_FMT_H
#define STD_FMT_H

#include "std/int.h"
#include <stddef.h>

// assuming a type_fmt function, convert type to a string using the buffer buf
#define fmt(type, buf, ...) ((buf)[type ## _fmt(buf, __VA_ARGS__)] = '\0', (buf))

size_t          fmt_i(char *, i64, u8);
size_t          fmt_minus(char *, int);
size_t          fmt_pad(char *, size_t, char const *, size_t);
size_t          fmt_plusminus(char *, int);
size_t          fmt_u(char *, u64, u8);
size_t          fmt_u0(char *, u64, size_t, u8);
size_t          fmt_xmem(char const *, size_t, char *);

#endif
