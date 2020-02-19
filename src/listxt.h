#ifndef LISTXT_H
#define LISTXT_H

#include <stdio.h>

/**/
int		listxt_get		(char *, char **, size_t, size_t, char *);
int		listxt_getline		(char **, size_t *, size_t, FILE *);
int		listxt_isvalid		(char *);
int		listxt_fput		(FILE *, char **, size_t);
int		listxt_tmppath		(char *, size_t, char const *);

#endif
