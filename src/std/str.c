#include "std/str.h"

#include "std/mem.h"

size_t
str_char(char const *s, char c)
{
	char *p = strchr(s, c);
	return p ? (size_t)(p - s) : strlen(s);
}

size_t
str_str(char const *s, char const *needle)
{
	char *p = strstr(s, needle);
	return p ? (size_t)(p - s) : strlen(s);
}

size_t
str_char_r(char const *s, char c)
{
	char *p = strrchr(s, c);
	return p ? (size_t)(p - s) : strlen(s);
}

size_t
str_copy(char *d, size_t n, char const *s)
{
	size_t i;

	for (i = 0; i < n - 1; i++) if ((d[i] = s[i]) == '\0') return i;

	d[i++] = '\0';
	return i;
}
