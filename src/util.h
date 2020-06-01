#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>

/** src/util.c **/
size_t strlcpy(char *buf, const char *str, size_t sz);
int strchomp(char *s);
int is_valid(char *s);
int path_fmt(char *buf, size_t len, char *fmt, char *s);

#endif
