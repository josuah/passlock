#include "listxt.h"
#include "stralloc.h"
#include "fmt.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int
listxt_tmp(stralloc *sa, char const *path)
{
	char num[50];

	num[fmt_long(num, getpid())] = '\0';
	stralloc_zero(sa);
	if (!stralloc_cats(sa, path)) return 0;
	if (!stralloc_cats(sa, ".")) return 0;
	if (!stralloc_cats(sa, num)) return 0;
	if (!stralloc_cat0(sa)) return 0;

	return 1;
}
