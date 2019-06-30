#ifndef GENALLOC_H
#define GENALLOC_H

#include "stralloc.h"
#include "mem.h"
#include <stddef.h>

typedef stralloc genalloc;

#define GENALLOC_INIT(s) STRALLOC_INIT(s)

#define genalloc_s(type, ga)        ((type *)(ga)->s)
#define genalloc_len(type, ga)      ((ga)->n / sizeof (type))
#define genalloc_catx(type, ga, x)  stralloc_catb((ga), (char const *)(x), sizeof (type))
#define genalloc_free(type, ga)     stralloc_free(ga)
#define genalloc_zero(type, ga)     stralloc_zero(ga)

#endif
