#include "std/str.h"

#include "std/mem.h"

size_t
str_chr(char const *buf, char c)
{
	char *s = strchr(buf, c);
	return s ? (size_t)(s - buf) : strlen(buf);
}

size_t
str_str(char const *buf, char const *needle)
{
	char *s = strstr(buf, needle);
	return s ? (size_t)(s - buf) : strlen(buf);
}

size_t
str_rchr(char const *buf, char c)
{
	char *s = strrchr(buf, c);
	return s ? (size_t)(s - buf) : strlen(buf);
}
