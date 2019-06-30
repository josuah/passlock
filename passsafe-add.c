#include "arg.h"
#include "buffer.h"
#include "fd.h"
#include "fmt.h"
#include "listxt.h"
#include "log.h"
#include "open.h"
#include "stralloc.h"
#include <stdio.h>  /* for rename(2) */

#define die_open(p)     log_fs3(111, "could not open \"",p,"\"")
#define die_read(f)     log_fs3(111, "could not read line from \"",f,"\"")
#define die_nomem()     log_fs1(111, "could not allocate memory")
#define die_exist(u,f)  log_fs5(1, "user \"",u,"\" already in \"",f,"\"")
#define die_write()     log_fs1(111, "could not write to the temporary pass file")
#define die_rename(f,t) log_fs5(111, "could not rename \"",f,"\" to \"",t,"\"")
#define die_invalid(s)  log_f2(1, "invalid character(s) in the ",s)
#define die_copy()      log_fs1(111, "could not copy the file")

char *flag_f = NULL;

void
usage(void)
{
	log_usage(arg_0, "-f passfile user path <passphrase");
}

int
main(int argc, char **argv)
{
	char *user;
	char *path;
	char bx[1024];
	char *gx[3];
        buffer b = BUFFER_INIT(write, 0, bx, sizeof bx);
	stralloc pass = STRALLOC_INIT(0);
	stralloc sa = STRALLOC_INIT(0);
	genalloc ga = GENALLOC_INIT(gx);
	int fd;
	char num[30];

	ARG_BEGIN {
	case 'f': flag_f = ARG; break;
	default: usage();
	} ARG_END;

	if (!flag_f) usage();
	if (!(user = *argv++)) usage(); 
	if (!(path = *argv++)) usage();

	if (!listxt_valid(user)) die_invalid("username");
	if (!listxt_valid(path)) die_invalid("path");

	if (!listxt_get(flag_f, &sa, &ga, 0, user)) die_open(flag_f);
	if (genalloc_len(char *, &ga) > 0) die_exist(user, flag_f);

	if (!buffer_getline(buffer_0, &pass)) die_read("stdin");
	stralloc_chomp(&pass);
	if (!stralloc_cat0(&pass)) die_nomem();
	if (!listxt_valid(pass.s)) die_invalid("passphrase");

	num[fmt_long(num, getpid())] = '\0';
	stralloc_zero(&sa);
	if (!stralloc_cats(&sa, flag_f)) die_nomem();
	if (!stralloc_cats(&sa, ".")) die_nomem();
	if (!stralloc_cats(&sa, num)) die_nomem();
	if (!stralloc_cat0(&sa)) die_nomem();

	if ((fd = open_read(flag_f)) == -1) die_open(flag_f);
	if ((b.fd = open_truncate(sa.s)) == -1) die_open(&sa);
	if (fd_dump(b.fd, fd) == -1) die_copy();

	if (!buffer_puts(&b, user)) die_write();
	if (!buffer_puts(&b, ":")) die_write();
	if (!buffer_puts(&b, pass.s)) die_write();
	if (!buffer_puts(&b, ":")) die_write();
	if (!buffer_puts(&b, path)) die_write();
	if (!buffer_puts(&b, "\n")) die_write();
	if (!buffer_flush(&b)) die_write();

	if (rename(sa.s, flag_f) == -1) die_rename(sa.s, flag_f);

	return 0;
}
