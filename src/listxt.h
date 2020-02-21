#ifndef LISTXT_H
#define LISTXT_H

#include <stdio.h>

/**/
ssize_t		listxt_getline		(char **, size_t *, FILE *);
int		listxt_cmp		(char *, size_t, char *);
char *		listxt_get		(char *, size_t, char *);
int		listxt_isvalid		(char *);
int		listxt_fput		(FILE *, char *, size_t);
int		listxt_tmppath		(char *, size_t, char const *);

#endif
