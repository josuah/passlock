#include "arg.h"
#include "listxt.h"
#include "log.h"
#include "mem.h"
#include <errno.h>
#include <sodium.h>
#include <unistd.h>

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
	char b3[512];
	buffer buffer_3[1] = { BUFFER_INIT(buffer_read, 3, b3, sizeof b3) };
	stralloc sa = STRALLOC_INIT;
	genalloc ga = GENALLOC_INIT;
	stralloc line = STRALLOC_INIT;
	char c, *s, *user, *pass, *hash, *path;
	size_t n, i;

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

	if (!*argv) usage();

	errno = 0;
	while (buffer_getc(buffer_3, &c) && stralloc_catc(&sa, c));
	if (errno != 0) log_fatalsys("read fd 3");

	s = sa.s;
	n = sa.n;

	user = s;
	if ((i = mem_chr(s, n, '\0')) == n) log_fatal("no username");
	s += i + 1;
	n -= i + 1;
	pass = s;
	if ((i = mem_chr(s, n, '\0')) == n) log_fatal("no passphrase");
	s += i + 1;
	n -= i + 1;
	if ((i = mem_chr(s, n, '\0')) == n) log_fatal("no timestamp");

	if (!listxt_get(flag_f, &line, &ga, 0, user)) log_fatalsys("read ", flag_f);
	if (genalloc_len(char *, &ga) < 3) {
		i = crypto_pwhash_str_verify(DUMMY, "", 0);
		log_fatal("invalid user");
	}

	hash = genalloc_s(char *, &ga)[1];

	if (crypto_pwhash_str_verify(hash, pass, str_len(pass)) != 0)
		log_fatal("invalid pass");

	path = genalloc_s(char *, &ga)[2];
	if (chdir(path) == -1) log_fatalsys("chdir", path);

	execvp(*argv, argv);
	log_fatalsys("exec", *argv);

	return 0;
}
