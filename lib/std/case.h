#ifndef STD_CASE_H
#define STD_CASE_H

#include "std/int.h"
#include <ctype.h>
#include <string.h>

#define case_equal(buf1, buf2)     (!case_cmp(buf1, buf2))
#define case_equaln(buf1, buf2, n) (!case_cmpn(buf1, buf2, n))
#define case_start(buf1, buf2)     (!case_cmpn(buf1, buf2, strlen(buf2)))
#define case_diff(buf1, buf2)      (case_cmp(buf1, buf2))
#define case_diffn(buf1, buf2, n)  (case_cmpn(buf1, buf2, n))

extern u8 case_upper[256];
extern u8 case_lower[256];

int             case_cmp(char const *, char const *);
int             case_cmpn(char const *, char const *, size_t);

#endif
