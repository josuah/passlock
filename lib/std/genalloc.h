#ifndef STD_GENALLOC_H
#define STD_GENALLOC_H

#include "std/stralloc.h"
#include <stddef.h>

#define GENALLOC_INIT               STRALLOC_INIT
#define genalloc                    stralloc

#define genalloc_s(type, ga)        ((type *)(ga)->s)
#define genalloc_len(type, ga)      ((ga)->n / sizeof (type))
#define genalloc_cat(type, ga, x)  stralloc_catb((ga), (char const *)(x), sizeof (type))
#define genalloc_free(type, ga)     stralloc_free(ga)
#define genalloc_zero(type, ga)     stralloc_zero(ga)
#define genalloc_init(type, ga)     stralloc_init(ga)
#define genalloc_ready(type, ga, n) stralloc_ready((ga), sizeof (type) * (n))

#endif
