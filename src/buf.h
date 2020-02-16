#ifndef BUF_H
#define BUF_H

#include <stdarg.h>
#include <stddef.h>

struct buf {
	char *s;
	size_t n, a;  /* used and allocated space */
	int fd;
};

#define buf_put(buf, ...)	buf_put_(buf, __VA_ARGS__, (char*)0)

/**/
struct buf b0[1];
struct buf b1[1];
struct buf b2[1];
struct buf b3[1];
struct buf b4[1];
ssize_t		buf_write		(int, char *, size_t);
ssize_t		buf_read		(int, char *, size_t);
int		buf_flush		(struct buf *);
int		buf_alloc		(struct buf *, size_t);
int		buf_grow		(struct buf *, size_t);
int		buf_put_mem		(struct buf *, char const *, size_t);
int		buf_put_va		(struct buf *, va_list);
int		buf_put_		(struct buf *, ...);
char *		buf_str			(struct buf *, char *, size_t);
void		buf_init_stat		(struct buf *, char *, size_t, int);
void		buf_init_mem		(struct buf *);
void		buf_init_write		(struct buf *, char *, size_t, int);
void		buf_init_read		(struct buf *, char *, size_t, int);
int		buf_close		(struct buf *);

#endif
