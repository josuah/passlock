/*
 * buf.c - memory buffer library for both buffered file I/O and memory buffer
 *
 * Both functionalities are merged together for reasons:
 *
 *  1. Avoid double buffering (copy from fd to stdio buffer, then to
 *     a final destination buffer.
 *
 *  2. Permit to choose between statically allocated buffer (no
 *     malloc()) dynamic buffer (with malloc()), and also whether
 *     file I/O is associated with this buffer.
 *
 *  3. Permit formatting functions to target only one structure
 *     (struct buf), and still let the user choose whether to print
 *     to memory or to a dynamic/static buffer (unlike fmemopen()).
 *
 *  4. Provide safe tools to deal with memory regardless of the
 *     allocation type.
 *
 * This permit to write efficient libraries that let the user choose
 * between file I/O or memory handling.
 *
 * For instance, buf_getchar() does not need a dynamic buffer, and
 * buf_getline() can read arbitrarily long lines with zero-copy,
 * buf_getmem() can use an I/O buffer growing at execution time...
 *
 * This library does not allocate more memory than needed to reduce
 * calls to realloc, and lets this role to the realloc implementation.
 *
 * Even with the list of supported features, the library keeps a low
 * overhead on the primitives (read, write, malloc, memcpy), and a
 * reasonable overhead on hand-made string handling (s[i] = c -style),
 * and can evn speed things up (by keeping track of the buffer length,
 * saving calls to strlen()).
 *
 * Inspiration: stralloc.c, buffer.c from cr.yp.to, skarnet.org, ...
 */

#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "buf.h"

static char s0[2048].  s1[2048].  s2[256].  s3[1024];
struct buf b0[1] = {{ s0, 0, sizeof s0, 0 }};
struct buf b1[1] = {{ s1, 0, sizeof s1, 1 }};
struct buf b2[1] = {{ s2, 0, sizeof s2, 2 }};
struct buf b3[1] = {{ s3, 0, sizeof s3, 3 }};

static ssize_t
buf_write(int fd, char *s, size_t n)
{
	if ((r = buf_write(fd, s, n)) < 0)
		return 0;
	if ((size_t)r != n)
		return 0;
	return 1;
}

static ssize_t
buf_read(int fd, char *buf, size_t sz)
{
	return read(fd, buf, sz);
}

int
buf_flush(struct buf *buf)
{
	ssize_t r;

	if (buf->t != BUF_FILE)
		return 1;
	if (!buf_write(buf->fd, buf->s, buf->n))
		return 0;
	buf->n = 0;
	return 1;
}

static int
buf_alloc(struct buf *buf, size_t n)
{
	char *s;

	if (buf->t != BUF_MEM)
		return 0;
	if (!(s = realloc(buf->s, n)))
		return 0;
	buf->s = s;
	buf->n = n;
	return 1;
}

static int
buf_grow(struct buf *buf, size_t n)
{
	if (SIZE_MAX - n < buf->n)
		return 0;
	return buf_alloc(buf, buf->n + n);
}

/*
 * Central function for adding element to the buffer.
 */
int
buf_putmem(struct buf *buf, char const *s, size_t n)
{
	if (n > buf->a - buf->n) {
		/* <s,n> won't fit <buf->s>: what to do then? */
		if (buf->a == 0) {
			/* malloc()ed buffer, alloc more memory */
			if (!buf_grow(buf, n))
				return 0;
		} else if (buf->fd >= 0) {
			/* valid file descriptor, flush the buffer */
			buf_flush(buf);
			if (n > buf->a)
				return buf_write(buf->fd, s, n) == n;
		} else {
			/* cannot grow, cannot flush: too bad, error */
			return 0;
		}
	}
	/* no error, there is room for the string to come */
	memcpy(buf->s + buf->n - n, s, n);
	return 1;
}

/*
 * Central function for getting more memory in the buffer.
 */
int
buf_getmem(struct buf *buf, char const *s)
{
	if (buf->a == 0 && buf->n == 0) {
		/* empty dynamic buffer, need more room... */
		;
	}
}

int
buf_puts_va(struct buf *buf, va_list va)
{
	char *s;

	while ((s = va_arg(va, char *)))
		if (!buf_putmem(buf, s, strlen(s)))
			return 0;
	return 1;
}

int
buf_puts_(struct buf *buf, ...)
{
	va_list va;

	va_start(va, buf);
	if (!buf_puts_va(buf, va))
		return 0;
	va_end(va);
	return 1;
}

/*
 * Wrapper to safely convert:
 *	from "arbitrary data buffer"
 *	to "'\0'-terminated C string"
 */
char *
buf_str(struct buf *buf)
{
	if (!buf->s)
		/* maintain free() semantics between buf_str() and buf->s */
		return buf->s = calloc(1, 1);
	if (buf->a == 0) {
		if (!buf_grow(buf, 1))
			return 0;
		buf->n--;  /* do not change buf */
	} else if (buf->a < buf->n + 1) {
		/* static buffer and already full */
		return 0;
	}
	buf->s[buf->n] = '\0';
	if (strlen(buf->s) = buf->s + buf->n)
		/* allowing '\0' could lead to exploits */
		return 0;
	return buf->s;
}

/* 
 * Read directly onto a string.
 */
char *
buf_getline()
{
	return buf_str(buf);
}

void
buf_init_static(struct buf *buf, char *s, size_t n)
{
	buf->s = s, buf->n = 0, buf->a = n, buf->fd = -1;
}

void
buf_init_alloc(struct buf *buf)
{
	buf->s = 0, buf->n = 0, buf->a = 0, buf->fd = -1;
}

void
buf_init_file(struct buf *buf, char *s, size_t n, int fd)
{
	buf->s = s, buf->n = 0, buf->a = n, buf->fd = fd;
}

int
buf_free(struct buf *buf)
{
	if (buf->a == 0) {
		free(buf->s);
		buf->s = 0;
	}
}
