#ifndef LISTXT_H
#define LISTXT_H

#include "buf.h"

struct listxt {
	char *field;
	struct listxt *next;
};

/**/
int		listxt_get		(char *, struct buf *, struct genalloc *, size_t, char *);
struct listxt **listxt_add		(struct listxt **, char *);
void		listxt_free		(struct listxt *);
struct listxt *	listxt_getline		(struct buf *);
int		listxt_valid		(char *);
int		listxt_put		(struct buf *, struct listxt *);
int		listxt_tmp		(struct buf *, char const *);

#endif
