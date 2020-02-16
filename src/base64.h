#ifndef BASE64_H
#define BASE64_H

#include <stdint.h>
#include <stddef.h>

/**/
void		base64_encode		(char const *, size_t, char *);
size_t		base64_decode		(char const *, size_t, char *, size_t *);

#endif
