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
 * Find from <path> the first entry <*list> whose field number <pos>
 * is <value> and store it to <*list>.  If no value is found, list[0]
 * is set to NULL.
 *
 */
int
listxt_get(char *path, char **list, size_t n, size_t pos, char *value)
{
	FILE *fp;
	size_t sz;

	assert(pos < n);

	if ((fp = fopen(path, "r")) == NULL)
		return -1;

	*list = NULL;
	while (listxt_getline(list, &sz, n, fp) > -1) {
		/* <list[pos]> will not be NULL as we checked just above */
		if (list[pos] && strcmp(list[pos], value) == 0) {
			fclose(fp);
			return 0;
		}
	}
	if (ferror(fp)) {
		fclose(fp);
		return -1;
	}
	free(list[0]);
	list[0] = NULL;
	fclose(fp);
	return 0;
}

/*
 * Wrapper over getline() that takes the same arguments, but "list"
 * is also a pointer to a buffer of size <n> to be filled with fields
 * splitted with strfield into list[:], with list[0] containing a pointer
 * to the buffer.
 *
 * The first field is always set, the others can be set to the token
 * or NULL.
 */
int
listxt_getline(char **list, size_t *sz, size_t n, FILE *fp)
{
	char *line;
	ssize_t r;

	/* need to return the pointer to the buffer in list[0] */
	assert(n > 0);

	/* get a line from the file */
	line = *list;
	r = getline(&line, sz, fp);
	if (r <= 0)
		return -1;

	/* sanitize the entry*/
	if (memchr(line, '\0', r) == NULL) {
		errno = EBADMSG;
		return -1;
	}
	if (line[r - 1] == '\n')
		line[--r] = '\0';

	/* split <n> fields */
	while (n-- > 0)
		*list++ = strfield(&line, ":");

	/* make sure that the last field stops at the next delimiter */
	strfield(&line, ":");

	return (size_t)r;
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
listxt_fput(FILE *fp, char **list, size_t sz)
{
	for (; n > 0; list++, n--) {
		if (fprintf(fp, n > 1 ? "%s:" : "%s", *list) < 0)
			return 0;
	}
	if (fprintf(fp, "\n") < 0)
		return -1;
	return 0;
}

/*
 * Temporary path for atomically replacing the file with a new one.
 */
int
listxt_tmppath(char *tmp, size_t n, char const *path)
{
	size_t l;

	l = snprintf(tmp, n, "%s.%ld", (long)getpid())
	return (l >= n) ? 0 : -1;
}
