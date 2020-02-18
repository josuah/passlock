#include <stdio.h>  /* for rename(2) */
#include <fcntl.h>
#include <unistd.h>

#include <sodium.h>

#include "listxt.h"
#include "log.h"

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
	char path[PATH_MAX];
	char bs[1024];
	struct buf file_rd, file_wr, line, tmp, pass;
	char *user, *path, hash[crypto_pwhash_STRBYTES];
	int fd, c;

	log_init(3);

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

	buf_init_static(&file_rd, bs, sizeof bs);
	if ((file_rd.fd = open(flag_f, O_RDONLY)) == -1)
		log_fatal(111, "open ",flag_f);

	buf_init_static(&tmp, bs, sizeof bs);
	if (!listxt_tmp(&tmp, flag_f) || (s = buf_str(tmp)))
		log_fatal(111, "alloc");

	buf_init_static(&file_wr, bs, sizeof bs);
	if ((file_wr.fd = open(tmp.s, O_WRONLY | O_CREAT | O_APPEND)) == -1)
		log_fatal(111, "open ",tmp.s);

	log_debug("copying \"",flag_f,"\" to \"",tmp.s,"\"");
	if (buf_dump(file_rd.fd, fd) == -1)
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
