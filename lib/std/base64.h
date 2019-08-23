#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>

size_t          base64_scan(char const *, size_t, char *, size_t *);
void            base64_fmt(char const *, size_t, char *);

#endif
