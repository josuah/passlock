#include "std/range.h"

#include "std/genalloc.h"
#include "std/int.h"
#include <stdlib.h>

int
range_has(struct genalloc *ga, u64 u)
{
	for (size_t i = 0; i < genalloc_len(struct range, ga); i++) {
		struct range *r = genalloc_s(struct range, ga) + i;
		if (u >= r->beg && u <= r->end)
			return 1;
	}

	return 0;
}

void
range_merge(struct genalloc *ga)
{
	size_t n = genalloc_len(struct range, ga);
	size_t i1 = 0, i2 = 1;

	// zero the length, but still use the buffer
	genalloc_zero(struct range, ga);

	while (i2 < n) {
		struct range *r1 = genalloc_s(struct range, ga) + i1;
		struct range *r2 = genalloc_s(struct range, ga) + i2;

		if (r1->end >= r2->end) {
			i2++;
		} else if (r1->end >= r2->beg - 1) {
			r1->end = r2->end;
			i2++;
		} else {
			genalloc_cat(struct range, ga, r1);
			i1 = i2;
			i2++;
		}
	}

	if (n > 0) {
		struct range *r1 = genalloc_s(struct range, ga) + i1;
		genalloc_cat(struct range, ga, r1);
	}
}

int
range_compare(const void *v1, const void *v2)
{
	struct range const *r1 = v1, *r2 = v2;

	if (r1->beg < r2->beg) return -1;
	if (r1->beg > r2->beg) return 1;
	if (r1->end < r2->end) return -1;
	if (r1->end > r2->end) return 1;

	return 0;
}

void
range_swap(struct range *r)
{
	if (r->beg > r->end) {
		u64 r_beg = r->beg;
		r->beg = r->end;
		r->end = r_beg;
	}
}

void
range_sort(struct genalloc *ga)
{
	qsort(genalloc_s(struct range, ga),
		genalloc_len(struct range, ga),
		sizeof (struct range),
		range_compare);
}

int
range_next(struct genalloc *ga, u64 *pos)
{
	(*pos)++;
	for (size_t i = 0; i < genalloc_len(struct range, ga); i++) {
		struct range *r = genalloc_s(struct range, ga);
		if (r->beg <= *pos && *pos <= r->end) return 1;
		if (r->beg > *pos) { *pos = r->beg; return 1; }
	}

	return 0;
}
