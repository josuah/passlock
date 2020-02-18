#ifndef LISTXT_H
#define LISTXT_H


struct listxt {
	char *field;
	struct listxt *next;
};

/**/
void		listxt_free_list	(struct listxt **);
struct listxt **listxt_file		(char *, char *, size_t, size_t);
struct listxt **listxt_add		(struct listxt **, char *);
void		listxt_free		(struct listxt *);
size_t		listxt_getline		(FILE *, struct listxt **);
int		listxt_valid		(char *);
int		listxt_put		(FILE *, struct listxt *);
int		listxt_tmp		(struct buf *, char const *);

#endif
