#include "listxt.h"
#include "str.h"

int
listxt_valid(char *s)
{
	while (1) switch (*s++) {
	case '\0': return 1;
	case '\n': case '\r': case ':': return 0;
	}
}
