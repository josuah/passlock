#ifndef STD_STRALLOC_H
#define STD_STRALLOC_H

#include "std/str.h"
#include <stddef.h>

struct stralloc {
	char* s;
	size_t n;
	size_t a;
};

#define STRALLOC_INIT { 0, 0, 0 }

#define stralloc_cat0(sa)           stralloc_catb((sa), "", 1)
#define stralloc_cats(sa, s)        stralloc_catb((sa), s, str_len(s))
#define stralloc_catc(sa, c)        stralloc_catb((sa), &c, 1)
#define stralloc_cat(sa1, sa2)      stralloc_catb((sa1), (sa2)->s, (sa2)->n)
#define stralloc_readyplus(sa, len) stralloc_ready((sa), (sa)->n + (len))
#define stralloc_zero(sa)           ((sa)->n = 0)

int             stralloc_catb(struct stralloc *, const char *, size_t);
int             stralloc_ready(struct stralloc *, size_t);
void            stralloc_chomp(struct stralloc *);
void            stralloc_free(struct stralloc *);
void            stralloc_init(struct stralloc *);
void            stralloc_strip(struct stralloc *);

#endif
