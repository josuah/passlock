#ifndef STR_H
#define STR_H

#include <stddef.h>
#include <string.h>

#define str_copy(to, n, from) strlen(strncpy(to, from, n))
#define str_diff(s1, s2)      strcmp(s1, s2)
#define str_diffn(s1, s2, n)  strncmp(s1, s2, n)
#define str_equal(s1, s2)     (!strcmp(s1, s2))
#define str_equaln(s1, s2, n) (!strncmp(s1, s2, n))
#define str_len(s)            strlen(s)
#define str_start(s1, s2)     (!strncmp(s1, s2, strlen(s2)))
#define str_dup(s)            strdup(s)

// bin/make-h lib/str.c
size_t  str_chr(char const *, char);
size_t  str_rchr(char const *, char);

#endif
