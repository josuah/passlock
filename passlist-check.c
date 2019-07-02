#include "arg.h"
#include "die.h"
#include "die.h"
#include "listxt.h"
#include "log.h"
#include <errno.h>
#include <sodium.h>
#include <unistd.h>

char *flag_f = "/etc/pass/default";

void
usage(void)
{
	log_usage(arg_0, "[-f passfile] prog [arg...]");
}

int
main(int argc, char **argv)
{
	char b3[512], bsa[512], *bga[3];
	buffer buffer_3[1] = { BUFFER_INIT(read, 3, b3, sizeof b3) };
	stralloc sa = STRALLOC_INIT(bsa);
	genalloc ga = GENALLOC_INIT(bga);
	stralloc line = STRALLOC_INIT(0);
	char c, *s, *user, *pass, *hash, *path;
	size_t n, i;

	log_init();

	ARG_BEGIN {
	case 'f': flag_f = ARG; break;
	default: usage();
	} ARG_END;

	if (!*argv) usage();

	errno = 0;
	while (buffer_getc(buffer_3, &c) && stralloc_catc(&sa, c));
	if (errno != 0) log_fs1(111, "could not read from file descriptor 3");

	s = sa.s;
	n = sa.n;

	user = s;
	if ((i = mem_chr(s, n, '\0')) == n) log_f1(2, "no username");
	s += i + 1;
	n -= i + 1;
	pass = s;
	if ((i = mem_chr(s, n, '\0')) == n) log_f1(2, "no passphrase");
	s += i + 1;
	n -= i + 1;
	if ((i = mem_chr(s, n, '\0')) == n) log_f1(2, "no timestamp");

	if (!listxt_get(flag_f, &line, &ga, 0, user)) die_read(flag_f);
	if (genalloc_len(char *, &ga) < 3)
		log_f1(1, "invalid user");

	hash = genalloc_s(char *, &ga)[1];
	if (crypto_pwhash_str_verify(hash, pass, str_len(pass)) != 0)
		log_f1(1, "invalid pass");

	genalloc_free(char *, &ga);
	stralloc_free(&sa);
	stralloc_free(&line);

	path = genalloc_s(char *, &ga)[2];
	if (chdir(path) == -1) die_chdir(path);

	execvp(*argv, argv);
	die_exec(*argv);

	return 0;
}
