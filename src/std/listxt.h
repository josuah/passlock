#ifndef LISTXT_H
#define LISTXT_H

#include "std/buffer.h"
#include "std/genalloc.h"
#include "std/stralloc.h"

int             listxt_get(char *, struct stralloc *, struct genalloc *, size_t, char *);
int             listxt_getline(struct buffer *, struct stralloc *, struct genalloc *);
int             listxt_put(struct buffer *, struct genalloc *);
int             listxt_tmp(struct stralloc *, char const *);
int             listxt_valid(char *);
size_t          listxt_scan(char *);

#endif
