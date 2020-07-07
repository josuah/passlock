#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>

#define LEN(x) (sizeof (x) / sizeof *(x))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/** src/util.c **/
size_t strlcpy(char *buf, const char *str, size_t sz);
int strchomp(char *s);

#endif
