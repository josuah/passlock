#include "str.h"

size_t
str_chr(char const *buf, char c)
{
	char *s = strchr(buf, c);
	return s ? (size_t)(s - buf) : strlen(buf);
}
