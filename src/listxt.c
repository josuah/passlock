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
#include "log.h"

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

ssize_t
listxt_field(char *line, size_t n, char **field)
{
	for (; n > 0 && line; n--) {
		line = strchr(line, ':');
		line += (line != NULL);
	}
	if (line == NULL)
		return -1;
	*field = line;
	line = strchr(*field, ':');
	return (line == NULL) ? strlen(*field) : line - *field;
}

int
listxt_cmp(char *line, size_t pos, char *value)
{
	ssize_t len;
	char *field;

	len = listxt_field(line, pos, &field);
	if (len == -1)
		return -1;
	if (strncmp(field, value, len) != 0)
		return -1;
	if ((line[len] != ':' && line[len] != '\0') || value[len] != '\0')
		return -1;
	return 0;
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
	return NULL;
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

void
listxt_fmt(char **field, ssize_t *len)
{
	if (*len == -1) {
		*field = ":";
		*len = 1;
	}
}

/*
 * Temporary path for atomically replacing the file with a new one.
 */
int
listxt_tmppath(char *tmp, size_t n, char const *path)
{
	size_t l;

	l = snprintf(tmp, n, "%s.%ld", path, (long)getpid());
	return (l >= n) ? -1 : 0;
}
