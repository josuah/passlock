#ifndef CASE_H
#define CASE_H

#include <ctype.h>
#include <string.h>

#define case_equal(buf1, buf2)     (!strcasecmp(buf1, buf2))
#define case_equaln(buf1, buf2, n) (!strncasecmp(buf1, buf2, n))
#define case_diff(buf1, buf2)      (strcasecmp(buf1, buf2))
#define case_diffn(buf1, buf2, n)  (strncasecmp(buf1, buf2, n))
#define case_lower(c)              (tolower(c))
#define case_upper(c)              (toupper(c))

#endif
