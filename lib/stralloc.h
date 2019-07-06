#ifndef STRALLOC_H
#define STRALLOC_H

#include "str.h"
#include <stddef.h>

typedef struct stralloc {
	char* s;
	size_t n;
	size_t a;
	int h;
} stralloc;

#define STRALLOC_INIT(s) { s, 0, s ? sizeof s : 0, !s }

#define stralloc_cat0(sa)           stralloc_catb((sa), "", 1)
#define stralloc_cats(sa, s)        stralloc_catb((sa), s, str_len(s))
#define stralloc_cat(sa1, sa2)      stralloc_catb((sa1), (sa2)->s, (sa2)->n)
#define stralloc_readyplus(sa, len) stralloc_ready((sa), (sa)->n + (len))
#define stralloc_zero(sa)           ((sa)->n = 0)

// bin/make-h lib/stralloc.c
int     stralloc_catb(stralloc *, const char *, size_t);
int     stralloc_catc(stralloc *, char);
int     stralloc_ready(stralloc *, size_t);
void    stralloc_chomp(stralloc *);
void    stralloc_free(stralloc *);

#endif
