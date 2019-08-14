#include "str.h"
#include "mem.h"

size_t
str_chr(char const *buf, char c)
{
	char *s = strchr(buf, c);
	return s ? (size_t)(s - buf) : strlen(buf);
}

size_t
str_rchr(char const *buf, char c)
{
	char *s = strrchr(buf, c);
	return s ? (size_t)(s - buf) : strlen(buf);
}
