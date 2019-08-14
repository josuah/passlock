#include "buffer.h"

#include "fmt.h"
#include "mem.h"
#include "str.h"
#include "stralloc.h"
#include <errno.h>
#include <unistd.h>

static char b0[8192];
buffer buffer_0[1] = { BUFFER_INIT(buffer_read, 0, b0, sizeof b0) };

static char b1[8192];
buffer buffer_1[1] = { BUFFER_INIT(buffer_write, 1, b1, sizeof b1) };

static char b2[256];
buffer buffer_2[1] = { BUFFER_INIT(buffer_write, 2, b2, sizeof b2) };

ssize_t
buffer_read(int fd, char *s, size_t n)
{
	ssize_t r;
	while ((r = read(fd, s, n)) == -1 && errno != EINTR);
	return r;
}

ssize_t
buffer_write(int fd, char *s, size_t n)
{
	ssize_t w;
	while ((w = write(fd, s, n)) == -1 && errno != EINTR);
	return w;
}

int
buffer_dump(int to, int from)
{
	char s[1024];
	ssize_t n;

	while ((n = buffer_read(from, s, sizeof s)) > 0)
		if (buffer_write(to, s, n) < n) return -1;
	return n;
}

int
buffer_fill(buffer *b)
{
	ssize_t r;

	r = b->op(b->fd, b->x + b->n, b->a - b->n);
	if (r <= 0) return 0;
	b->n += r;
	return r;
}

int
buffer_flush(buffer *b)
{
	ssize_t w = b->n - b->p;

	if (w != b->op(b->fd, b->x + b->p, w)) return 0;
	b->p = b->n = 0;
	return 1;
}

static size_t
buffer_getnofill(buffer *b, char *buf, size_t n)
{
	if (n > b->n - b->p) n = b->n - b->p;
	mem_copy(buf, b->x + b->p, n);
	b->p += n;
	if (b->p == b->n) b->p = b->n = 0;
	return n;
}

int
buffer_get(buffer *b, char *s, size_t n)
{
	ssize_t r;

	r = buffer_getnofill(b, s, n);
	n -= r;
	s += r;
	if (n == 0) return 1;
	if (n > b->a) return (size_t)b->op(b->fd, s, n) == n;
	if ((size_t)buffer_fill(b) < n) return 0;
	buffer_getnofill(b, s, n);
	return 1;
}

int
buffer_gettoken(buffer *b, stralloc *sa, char x)
{
	ssize_t r;
	ssize_t n = 0;
	char c;

	stralloc_zero(sa);
	while ((r = buffer_getc(b, &c)) > 0) {
		if (!stralloc_catb(sa, &c, 1)) return -1;
		if (c == x) return 1;
		++n;
	}
	return r;
}

void
buffer_init(buffer *b, ssize_t (*op)(), int fd, char *s, size_t n)
{
	b->fd = fd;
	b->op = op;
	b->x = s;
	b->a = n;
	b->n = 0;
	b->p = 0;
}

int
buffer_pad(buffer *b, char const *s, size_t n, char c)
{
	size_t i;

	for (i = str_len(s); i < n; i++)
		if (!buffer_putc(b, c)) return 0;
	return 1;
}

int
buffer_put(buffer *b, const char *s, size_t n)
{
	if (n > b->a - b->n) if (buffer_flush(b) <= 0) return 0;
	if (n > b->a) return (size_t)b->op(b->fd, s, n) == n;
	mem_copy(b->x + b->n, s, n);
	b->n += n;
	return 1;
}

int
buffer_putc(buffer *b, char c)
{
	return buffer_put(b, &c, 1);
}

int
buffer_putn(buffer *b, unsigned long ul)
{
	char num[30];

	return buffer_put(b, num, fmt_ulong(num, ul));
}
