#ifndef LISTXT_H
#define LISTXT_H

#include "buffer.h"
#include "genalloc.h"
#include "stralloc.h"

// bin/make-h liblistxt/*.c
int     listxt_get(char *, stralloc *, genalloc *, size_t, char *);
int     listxt_getline(buffer *, stralloc *, genalloc *);
int     listxt_put(buffer *, genalloc *);
int     listxt_tmp(stralloc *, char const *);
int     listxt_valid(char *);
size_t  listxt_scan(char *);

#endif
