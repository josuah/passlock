#include "listxt.h"
#include "str.h"

size_t
listxt_scan(char *s)
{
	return str_chr(s, ':');
}
