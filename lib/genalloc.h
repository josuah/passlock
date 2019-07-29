#ifndef GENALLOC_H
#define GENALLOC_H

#include "stralloc.h"
#include <stddef.h>

#define GENALLOC_INIT               STRALLOC_INIT
#define genalloc_s(type, ga)        ((type *)(ga)->s)
#define genalloc_len(type, ga)      ((ga)->n / sizeof (type))
#define genalloc_catx(type, ga, x)  stralloc_catb((ga), (char const *)(x), sizeof (type))
#define genalloc_free(type, ga)     stralloc_free(ga)
#define genalloc_zero(type, ga)     stralloc_zero(ga)
#define genalloc_init(ga, s)        stralloc_init(ga, s)

typedef stralloc genalloc;

#endif
