#ifndef UTIL_H
#define UTIL_H

#include <stdarg.h>
#include <stddef.h>

char *arg0;
void die(char const *fmt, ...);
void warn(char const *fmt, ...);
void debug(char const *fmt, ...);
int strchomp(char *s);
size_t strlcpy(char *buf, char const *str, size_t sz);

#endif
