#ifndef LISTXT_H
#define LISTXT_H

#include <stdio.h>

/**/
ssize_t		listxt_getline		(char **, size_t *, FILE *);
ssize_t		listxt_field		(char *, size_t, char **);
int		listxt_cmp		(char *, size_t, char *);
char *		listxt_get		(char *, size_t, char *);
int		listxt_isvalid		(char *);
void		listxt_fmt		(char **, ssize_t *);
int		listxt_tmppath		(char *, size_t, char const *);

#endif
