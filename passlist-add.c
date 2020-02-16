#include <stdio.h>  /* for rename(2) */
#include <fcntl.h>

#include <sodium.h>

#include "src/buf.h"
#include "src/listxt.h"
#include "src/log.h"

char *flag_f = "/etc/passlist/default";
char *arg0 = NULL;

void
usage(void)
{
	log_usage(arg0, " [-v] [-f passfile] user path <passphrase");
}

int
main(int argc, char **argv)
{
	char bs[1024];
	struct buf buf;
	struct genalloc ga = GENALLOC_INIT;
	struct buf line = STRALLOC_INIT;
	struct buf tmp = STRALLOC_INIT;
	struct buf pass = STRALLOC_INIT;
	char *user, *path, hash[crypto_pwhash_STRBYTES];
	int fd, c;

	log_init(3);
	buf_init_file(&buf, write, 0, bs, sizeof bs)

	optind = 0;
	arg0 = *argv;
	while ((c = getopt(argc, argv, "vf:")) != -1) {
		switch (c) {
		case 'v':
			buf_puts(b1, VERSION);
			buf_flush(b1);
			break;
		case 'f':
			flag_f = optarg;
			break;
		case '?':
			usage();
		}
	}

	if (!(user = *argv++))
		usage(); 
	if (!(path = *argv++))
		usage();
	if (*argv)
		usage();

	if (!listxt_valid(user))
		log_fatal(1, "invalid username");
	if (!listxt_valid(path))
		log_fatal(1, "invalid path");
	if (!listxt_get(flag_f, &line, &ga, 0, user))
		log_fatal(111, "open ",flag_f);
	if (genalloc_len(char *, &ga) > 0)
		log_fatal(1, "user ",user," exist on ",flag_f);

	if ((fd = open(flag_f, O_RDONLY)) == -1)
		log_fatal(111, "open ",flag_f);
	if (!listxt_tmp(&tmp, flag_f))
		log_fatal(111, "alloc");
	if ((buf.fd = open(tmp.s, O_WRONLY | O_CREAT | O_APPEND)) == -1)
		log_fatal(111, "open ",tmp.s);
	log_debug("copying \"",flag_f,"\" to \"",tmp.s,"\"");
	if (buf_dump(buf.fd, fd) == -1)
		log_fatal(111, "copy");

	if (!buf_getline(b0, &pass))
		log_fatal(111, "read stdin");
	buf_chomp(&pass);

	log_debug("hashing password");
	if (crypto_pwhash_str(hash, pass.s, pass.n,
		crypto_pwhash_OPSLIMIT_MODERATE,
		crypto_pwhash_MEMLIMIT_MODERATE) != 0)
		log_fatal(111, "alloc");

	if (!buf_put(&buf, user,": ",hash,": ",path,"\n"))
		log_fatal(111, "write");
	if (!buf_flush(&b))
		log_fatal(111, "write");

	if (rename(tmp.s, flag_f) == -1)
		log_fatal(111, tmp.s," -> ",flag_f);

	return 0;
}
