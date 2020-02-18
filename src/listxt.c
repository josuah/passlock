#include "listxt.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "buf.h"
#include "fmtnum.h"

void
listxt_free_list(struct listxt **list)
{
	for (; *list; list++)
		listxt_free(*list);
	free(list);
}

struct listxt **
listxt_file(char *path, char *s, size_t min, size_t max)
{
	FILE *fp;
	struct listxt **list, *lst;
	void *o;
	size_t len, n;

	list = NULL;

	fp = fopen(path, "r")
	if (!fp)
		return 0;

	for (n = 0; (len = listxt_getline(fp, &lst)); n++) {
		if (len > max || len < min) {
			errno = EINVAL;
			return 0;
		}
		o = realloc(list, n * sizeof *lst);
		if (!o) {
			list[n] = 0;
			listxt_free_list(list);
			listxt_free(lst);
			return 0;
		}
		list = o;
		list[n - 1] = lst,
		list[n] = 0;
	}
	close(file.fd);
	return list;
}

struct listxt **
listxt_add(struct listxt **link, char *field)
{
	*link = calloc(sizeof **link, 1);
	if (!*link)
		return 0;
	(*link)->field = field;
	return &(*link)->next;
}

void
listxt_free(struct listxt *lst)
{
	struct listxt *next;

	free(lst->field);
	for (next = lst->next; lst; lst = next, next = lst->next)
		free(lst);
}

size_t
listxt_getline(FILE *fp, struct listxt **link)
{
	struct listxt **first;
	char *field, *line;
	size_t n;

	errno = 0;

	*first = NULL;
	first = link;
	n = 0;
	line = NULL;
	if (getline(&line, &n, fp) == -1)
		goto error;
	for (n = 0; (field = strsep(&line, ":")); n++) {
		lst = listxt_add(lst, field);
	}
	return n;
error:
	free(line);
	listxt_free(*first);
	return 0;
}

int
listxt_valid(char *s)
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

int
listxt_put(FILE *fp, struct listxt *lst)
{
	for (; lst; lst = lst->next) {
		if (fprintf(fp, lst->next ? ":%s" : "%s", lst->field)) < 0)
			return 0;
	}
	if (fprintf(fp, "\n") < 0)
		return -1;
	return 0;
}

int
listxt_tmp(struct buf *buf, char const *path)
{
	char num[30];

	if (!buf_puts(buf, path, ".", fmtnum(num, getpid())))
		return 0;

	return 1;
}
