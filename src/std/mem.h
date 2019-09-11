#ifndef STD_MEM_H
#define STD_MEM_H

#include <stddef.h>
#include <string.h>

/*
 * Adapted from Dan Bernstein (cr.yp.to) code for djbdns (public domain) as
 * well as from Laurent Bercot (skarnet.org) code for skalibs (ISC licence).
 */

#define mem_copy(to, from, n)        memcpy(to, from, n)
#define mem_move(to, from, n)        memmove(to, from, n)
#define mem_diff(buf1, buf2, n)      memcmp(buf1, buf2, n)
#define mem_equal(buf1, buf2, n)     (!memcmp(buf1, buf2, n))
#define mem_set(buf, n, c)           memset(buf, c, n)
#define mem_str(buf, n, str)         mem_mem(buf, n, str, strlen(str))

size_t          mem_chr(char const *, size_t, char);
size_t          mem_mem(char const *, size_t, char const *, size_t);
void            mem_xor(unsigned char *, const unsigned char *, size_t);

#endif
