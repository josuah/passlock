#include <errno.h>
#include <sodium.h>
#include <unistd.h>

#include "src/listxt.h"
#include "src/log.h"
#include "src/mem.h"

#define DUMMY "$argon2id$v=19$m=262144,t=3,p=1$Ark5SdaPOY6+L9i2fDsvjw$wI/uFb9ReSF9rfX6x5wHsaXTsAYRAJPpz1LjpqBR3tI"

char *flag_f = "/etc/passlist/default";

void
usage(void)
{
	log_usage(arg_0, " [-v] [-f passfile] prog [arg...]");
}

int
main(int argc, char **argv)
{
	struct stralloc sa = STRALLOC_INIT;
	struct genalloc ga = GENALLOC_INIT;
	struct stralloc line = STRALLOC_INIT;
	char c, *s, *user, *pass, *hash, *path;
	char b3[512];
	size_t n, i;

	log_init(3);

	optind = 0;
	arg0 = *argv;
	while ((c = getopt(argc, argv, "vf:")) != -1) {
		switch (c) {
		case 'v':
			buf_puts(buf_1, VERSION);
			buf_flush(buf_1);
			break;
		case 'f':
			flag_f = optarg;
			break;
		case '?':
			usage();
		}
	}

	if (!*argv)
		usage();

	errno = 0;
	while (buf_getc(buf_3, &c) && stralloc_catc(&sa, c))
		continue;
	if (errno)
		log_fatal(111, "read fd 3");

	s = sa.s;
	n = sa.n;

	user = s;
	if ((i = mem_chr(s, n, '\0')) == n)
		log_fatal(2, "no username");
	s += i + 1;
	n -= i + 1;
	pass = s;
	if ((i = mem_chr(s, n, '\0')) == n)
		log_fatal(2, "no passphrase");
	s += i + 1;
	n -= i + 1;
	if ((i = mem_chr(s, n, '\0')) == n)
		log_fatal(2, "no timestamp");

	if (!listxt_get(flag_f, &line, &ga, 0, user))
		log_fatal(111, "read ", flag_f);
	if (genalloc_len(char *, &ga) < 3) {
		i = crypto_pwhash_str_verify(DUMMY, "", 0);
		log_fatal(1, "invalid user");
	}

	hash = genalloc_s(char *, &ga)[1];

	if (crypto_pwhash_str_verify(hash, pass, str_len(pass)) != 0)
		log_fatal(1, "invalid pass");

	path = genalloc_s(char *, &ga)[2];
	if (chdir(path) == -1)
		log_fatal(111, "chdir", path);

	execvp(*argv, argv);
	log_fatal(111, "exec", *argv);

	return 0;
}
