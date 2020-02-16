#include "listxt.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#include "buf.h"

struct listxt **
listxt_file(char *path, size_t n, char *s)
{
	char bx[1024];
	struct buf file;

	buf_

	if ((file.fd = open(path, O_RDONLY)) == -1)
		return 0;

	while (listxt_getline(&file, sa, ga)) {
		if (genalloc_len(char *, ga) < n)
			continue;
		if (strcmp(genalloc_s(char *, ga)[n], s) == 0)
			goto end;
	}
	genalloc_zero(char *, ga);
end:
	close(file.fd);
	return 1;
}

struct listxt **
listxt_add(struct listxt **link, char *field)
{
	if (!(*link = calloc(sizeof **link, 1)))
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

struct listxt *
listxt_getline(struct buf *file)
{
	struct buf mem;
	struct listxt **link, *first;
	size_t i, n;
	char *s;

	buf_init_mem(&mem);

	errno = 0;
	first = NULL;
	link = &first;

	if (!(str = buf_getline(file)))
		return 0;
	while ((field = strsep(&str, ":")))
		if (!(link = listxt_add(link)))
			goto error;
	return first;
error:
	buf_free(file)
	listxt_free(first);
	return 0;
}

int
listxt_valid(char *s)
{
	for (;;)
		switch (*s++) {
		case '\0':
			return 1;
		case '\n': case '\r': case ':':
			return 0;
		}
	}
}

int
listxt_put(struct buf *file, struct listxt *lst)
{
	for (; lst; lst = lst->next) {
		if (!buf_put(file, lst->field))
			return 0;
		if (lst->next)
			if (!buf_put(file, ":"))
				return 0;
	}
	if (!buf_put(b, "\n"))
		return 0;
	return 1;
}

int
listxt_tmp(struct buf *sa, char const *path)
{
	char num[30];

	if (!buf_put(buf, path, ".", fmt_num(num, getpid())))
		return 0;

	return 1;
}
