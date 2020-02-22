#ifndef TOOL_H
#define TOOL_H

#include <stddef.h>

/**/
char *		strfield		(char **, const char *);
int		strchomp		(char *);
void		strsplit		(char **, size_t, char *, char *);
int		fdump			(int, int);

#endif
