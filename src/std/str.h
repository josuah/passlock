#ifndef STD_STR_H
#define STD_STR_H

#include <stddef.h>
#include <string.h>

/*
 * Inspired from Dan Bernstein (cr.yp.to) code from for djbdns.
 */

#define str_equal(s1, s2)     (!strcmp(s1, s2))
#define str_equaln(s1, s2, n) (!strncmp(s1, s2, n))
#define str_len(s)            strlen(s)
#define str_start(s1, s2)     (!strncmp(s1, s2, strlen(s2)))

size_t          str_char(char const *, char);
size_t          str_char_r(char const *, char);
size_t          str_copy(char *, size_t, char const *);
size_t          str_str(char const *, char const *);

#endif
