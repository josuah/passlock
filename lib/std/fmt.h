#ifndef STD_FMT_H
#define STD_FMT_H

#include "std/int.h"
#include <stddef.h>

size_t          fmt_8long(char *, unsigned long);
size_t          fmt_fill(char *, size_t, char const *, size_t);
size_t          fmt_long(char *, long);
size_t          fmt_minus(char *, int);
size_t          fmt_pad(char *, size_t, char const *, size_t);
size_t          fmt_plusminus(char *, int);
size_t          fmt_strn(char *, size_t, char const *);
size_t          fmt_ulong(char *, unsigned long);
size_t          fmt_ulong0(char *, unsigned long, size_t);
size_t          fmt_utf8(char *, u32);
size_t          fmt_xlong(char *, unsigned long);
size_t          fmt_xlong0(char *, unsigned long, size_t);
size_t          fmt_xmem(char const *, size_t, char *);

#endif
