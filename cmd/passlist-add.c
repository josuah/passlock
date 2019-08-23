#include "std/arg.h"
#include "std/buffer.h"
#include "std/fmt.h"
#include "std/listxt.h"
#include "std/log.h"
#include "std/open.h"
#include "std/stralloc.h"
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
	struct buffer b = BUFFER_INIT(write, 0, bs, sizeof bs);
	struct genalloc ga = GENALLOC_INIT;
	int fd;
	struct stralloc line = STRALLOC_INIT;
	struct stralloc tmp = STRALLOC_INIT;
	struct stralloc pass = STRALLOC_INIT;

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

	if (!listxt_valid(user)) log_fatal(1, "invalid username");
	if (!listxt_valid(path)) log_fatal(1, "invalid path");
	if (!listxt_get(flag_f, &line, &ga, 0, user)) log_fatal_sys(111, "open ",flag_f);
	if (genalloc_len(char *, &ga) > 0) log_fatal(1, "user ",user," exist on ",flag_f);

	if ((fd = open_read(flag_f)) == -1) log_fatal_sys(111, "open ",flag_f);
	if (!listxt_tmp(&tmp, flag_f)) log_fatal_sys(111, "alloc");
	if ((b.fd = open_truncate(tmp.s)) == -1) log_fatal_sys(111, "open ",tmp.s);
	log_debug("copying \"",flag_f,"\" to \"",tmp.s,"\"");
	if (buffer_dump(b.fd, fd) == -1) log_fatal_sys(111, "copy");

	if (!buffer_getline(buffer_0, &pass)) log_fatal_sys(111, "read stdin");
	stralloc_chomp(&pass);

	log_debug("hashing password");
	if (crypto_pwhash_str(hash, pass.s, pass.n,
		crypto_pwhash_OPSLIMIT_MODERATE,
		crypto_pwhash_MEMLIMIT_MODERATE) != 0) log_fatal_sys(111, "alloc");

	if (!buffer_puts(&b, user)) log_fatal_sys(111, "write");
	if (!buffer_puts(&b, ":")) log_fatal_sys(111, "write");
	if (!buffer_puts(&b, hash)) log_fatal_sys(111, "write");
	if (!buffer_puts(&b, ":")) log_fatal_sys(111, "write");
	if (!buffer_puts(&b, path)) log_fatal_sys(111, "write");
	if (!buffer_puts(&b, "\n")) log_fatal_sys(111, "write");
	if (!buffer_flush(&b)) log_fatal_sys(111, "write");

	if (rename(tmp.s, flag_f) == -1) log_fatal_sys(111, tmp.s," -> ",flag_f);

	return 0;
}
