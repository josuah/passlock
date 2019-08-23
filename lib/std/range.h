#ifndef STD_RANGE_H
#define STD_RANGE_H

#include "std/genalloc.h"
#include "std/int.h"

#define RANGE_INIT { 0, 0 }

struct range {
	u64 beg;
	u64 end;
};

int             range_compare(const void *, const void *);
int             range_contain(struct genalloc *, u64);
int             range_next(struct genalloc *, u64 *);
void            range_merge(struct genalloc *);
void            range_sort(struct genalloc *);
void            range_swap(struct range *);

#endif
