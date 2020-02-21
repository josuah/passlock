#include "listxt.h"

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "tool.h"

/*
 * Library for handling a simple plaintext column-separated field
 * name database with a variable number of fields.
 *
 * There is no way for a file to contain invalid input.
 */

/*
 * Read and parse one line from <fp> into list, an array of <n>
 * char pointers, filled with the fields from line.
 *
 * The first field is always set, the others can be set to the token
 * or NULL.
 *
 * After the last field is all the unparsed data if anything remains.
 * To know whether there is anything left, <*sz> can be used.
 */
ssize_t
listxt_getline(char **line, size_t *sz, FILE *fp)
{
	ssize_t r;

	r = getline(line, sz, fp);
	if (r == -1)
		return -1;

	r -= strchomp(*line);
	if (memchr(line, '\0', r) == NULL) {
		errno = EBADMSG;
		return -1;
	}
	return r;
}

int
listxt_cmp(char *line, size_t field, char *value)
{
	size_t n;

	do {
		if (field-- > 0)
			continue;

		n = strlen(value);
		if (strncmp(line, value, n) != 0)
			return -1;
		if (line[n] != ':' && line[n] != '\0')
			return -1;
		return 0;
	} while ((line = strchr(line, ':')));

	return -1;
}

/*
 * Read the file at <path> and look for the first field at position
 * <field> that matches <value>.  Return a pointer to such a field.
 */
char *
listxt_get(char *path, size_t field, char *value)
{
	FILE *fp;
	char *line;
	size_t sz;

	if ((fp = fopen(path, "r")) == NULL)
		return NULL;

	sz = 0;
	line = NULL;
	while (listxt_getline(&line, &sz, fp) > -1) {
		if (listxt_cmp(line, field, value) == 0) {
			fclose(fp);
			return line;
		}
	}
	free(line);
	fclose(fp);
	return NULL
}

/*
 * Return 1 if the name <s> is a valid field name.
 */
int
listxt_isvalid(char *s)
{
	for (;;) {
		switch (*s++) {
		case '\0':
			return 1;
		case '\n': case '\r': case ':':
			return 0;
		}
	}
}

/*
 * Append a listxt-formatted row of size <sz> to a file.
 * <sz> is the string size of the buffer, not the number of elements.
 *
 * Null bytes delimiters are converted back to 
 */
int
listxt_fput(FILE *fp, char *buf, size_t sz)
{
	memtr(buf, sz, '\0', ':');
	return fprintf(stdout, "%s\n", buf) > 0;
}

/*
 * Temporary path for atomically replacing the file with a new one.
 */
int
listxt_tmppath(char *tmp, size_t n, char const *path)
{
	size_t l;

	l = snprintf(tmp, n, "%s.%ld", path, (long)getpid());
	return (l >= n) ? 0 : -1;
}
