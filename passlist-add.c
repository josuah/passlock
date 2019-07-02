#include "arg.h"
#include "buffer.h"
#include "die.h"
#include "fd.h"
#include "fmt.h"
#include "listxt.h"
#include "log.h"
#include "open.h"
#include "stralloc.h"
#include <stdio.h>  /* for rename(2) */
#include <sodium.h>

char *flag_f = "/etc/passlist/default";

void
usage(void)
{
	log_usage(arg_0, "[-f passfile] user path <passphrase");
}

int
main(int argc, char **argv)
{
	char *user;
	char *path;
	char hash[crypto_pwhash_STRBYTES];
	char *gs[3];
	char bs[1024];
	genalloc ga = GENALLOC_INIT(gs);
	buffer b = BUFFER_INIT(write, 0, bs, sizeof bs);
	int fd;
	stralloc line = STRALLOC_INIT(0);
	stralloc tmp = STRALLOC_INIT(0);
	stralloc pass = STRALLOC_INIT(0);

	log_init();

	ARG_BEGIN {
	case 'f': flag_f = ARG; break;
	default: usage();
	} ARG_END;

	if (!(user = *argv++)) usage(); 
	if (!(path = *argv++)) usage();
	if (*argv) usage();

	if (!listxt_valid(user)) die_invalid("username");
	if (!listxt_valid(path)) die_invalid("path");
	if (!listxt_get(flag_f, &line, &ga, 0, user)) die_open(flag_f);
	if (genalloc_len(char *, &ga) > 0) die_exist(user, flag_f);

	if ((fd = open_read(flag_f)) == -1) die_open(flag_f);
	if (!listxt_tmp(&tmp, flag_f)) die_nomem();
	if ((b.fd = open_truncate(tmp.s)) == -1) die_open(tmp.s);
	log_d5("copying \"",flag_f,"\" to \"",tmp.s,"\"");
	if (fd_dump(b.fd, fd) == -1) die_copy();

	if (!buffer_puts(buffer_2, "Enter password: ")) die_write();
	if (!buffer_flush(buffer_2)) die_write();
	if (!buffer_getline(buffer_0, &pass)) die_read("stdin");
	stralloc_chomp(&pass);

	log_d1("hashing password");
	if (crypto_pwhash_str(hash, pass.s, pass.n,
		crypto_pwhash_OPSLIMIT_MODERATE,
		crypto_pwhash_MEMLIMIT_MODERATE) != 0) die_nomem();

	if (!buffer_puts(&b, user)) die_write();
	if (!buffer_puts(&b, ":")) die_write();
	if (!buffer_puts(&b, hash)) die_write();
	if (!buffer_puts(&b, ":")) die_write();
	if (!buffer_puts(&b, path)) die_write();
	if (!buffer_puts(&b, "\n")) die_write();
	if (!buffer_flush(&b)) die_write();

	if (rename(tmp.s, flag_f) == -1) die_rename(tmp.s, flag_f);

	return 0;
}
