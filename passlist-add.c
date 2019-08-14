#include "arg.h"
#include "buffer.h"
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
	log_usage(arg_0, " [-v] [-f passfile] user path <passphrase");
}

int
main(int argc, char **argv)
{
	char *user, *path, hash[crypto_pwhash_STRBYTES];
	char bs[1024];
	buffer b = BUFFER_INIT(write, 0, bs, sizeof bs);
	genalloc ga = GENALLOC_INIT;
	int fd;
	stralloc line = STRALLOC_INIT;
	stralloc tmp = STRALLOC_INIT;
	stralloc pass = STRALLOC_INIT;

	log_init();

	ARG_BEGIN {
	case 'v':
		buffer_puts(buffer_1, VERSION);
		buffer_flush(buffer_1);
		return 0;
	case 'f':
		flag_f = ARG;
		break;
	default:
		usage();
	} ARG_END;

	if (!(user = *argv++)) usage(); 
	if (!(path = *argv++)) usage();
	if (*argv) usage();

	if (!listxt_valid(user)) log_fatal("invalid username");
	if (!listxt_valid(path)) log_fatal("invalid path");
	if (!listxt_get(flag_f, &line, &ga, 0, user)) log_fatalsys("open ",flag_f);
	if (genalloc_len(char *, &ga) > 0) log_fatal("user ",user," exist on ",flag_f);

	if ((fd = open_read(flag_f)) == -1) log_fatalsys("open ",flag_f);
	if (!listxt_tmp(&tmp, flag_f)) log_fatalsys("alloc");
	if ((b.fd = open_truncate(tmp.s)) == -1) log_fatalsys("open ",tmp.s);
	log_debug("copying \"",flag_f,"\" to \"",tmp.s,"\"");
	if (fd_dump(b.fd, fd) == -1) log_fatalsys("copy");

	if (!buffer_getline(buffer_0, &pass)) log_fatalsys("read stdin");
	stralloc_chomp(&pass);

	log_debug("hashing password");
	if (crypto_pwhash_str(hash, pass.s, pass.n,
		crypto_pwhash_OPSLIMIT_MODERATE,
		crypto_pwhash_MEMLIMIT_MODERATE) != 0) log_fatalsys("alloc");

	if (!buffer_puts(&b, user)) log_fatalsys("write");
	if (!buffer_puts(&b, ":")) log_fatalsys("write");
	if (!buffer_puts(&b, hash)) log_fatalsys("write");
	if (!buffer_puts(&b, ":")) log_fatalsys("write");
	if (!buffer_puts(&b, path)) log_fatalsys("write");
	if (!buffer_puts(&b, "\n")) log_fatalsys("write");
	if (!buffer_flush(&b)) log_fatalsys("write");

	if (rename(tmp.s, flag_f) == -1) log_fatalsys(tmp.s," -> ",flag_f);

	return 0;
}
