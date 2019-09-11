#ifndef BASE64_H
#define BASE64_H

#include "std/int.h"
#include <stddef.h>

extern i8 base64_char[256];

size_t          base64_decode(char const *, size_t, char *, size_t *);
void            base64_encode(char const *, size_t, char *);

#endif
