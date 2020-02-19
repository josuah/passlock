#include <assert.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include <sodium.h>

#include "listxt.h"
#include "log.h"

char *file = "/etc/passlist/default";
char *arg0;

void
usage(void)
{
	fprintf(stdout, "usage: %s [-v] [-f passfile] [-s sleep] prog [arg...]", arg0);
	exit(1);
}

int
main(int argc, char **argv)
{
	char c, *s, *e, *user, *pass, *date, buf[2048];
	char *list[3], *hash, *path;
	FILE *fp;
	int sec;

	optind = 0;
	arg0 = *argv;
	while ((c = getopt(argc, argv, "vf:s:")) > -1) {
		switch (c) {
		case 'v':
			fprintf(stdout, "%s\n", VERSION);
			exit(0);
		case 'f':
			file = optarg;
			break;
		case 's':
			sec = atoi(optarg);
			if (sec <= 0) {
				error("invalid number");
				usage();
			}
		case '?':
			usage();
		}
	}

	if (*argv)
		usage();

	/* read the file descriptor 3 into a memory buffer <buf> */
	assert(fp = fdopen(3, "r"));
	e = buf;
	while (e < buf + sizeof(buf) && (c = fgetc(fp)) != EOF)
		*e++ = c;
	if (ferror(fp) || e == buf + sizeof(buf))
		fatal(111, "read fd 3");

	/* extract the informations from that memory buffer */
	s = buf;
	user = s;
	s = memchr(s, '\0', e-s);
	if (s == NULL)
		fatal(100, "no username");
	s++;
	pass = s;
	s = memchr(s, '\0', e-s);
	if (s == NULL)
		fatal(100, "no passphrase");
	s++;
	date = s;
	s = memchr(s, '\0', e-s);
	if (s == NULL)
		fatal(100, "no timestamp");

	(void)date;

	/* search the pass file for a matching entry */
	switch (listxt_get(file, list, 3, 0, user)) {
	case -1:
		fatal(111, "read ", file);
	case 0:
		fatal(1, "unknown user");
	}

	hash = list[1];
	if (crypto_pwhash_str_verify(hash, pass, strlen(pass)) == -1) {
		sleep(sec);
		fatal(1, "invalid pass");
	}

	path = list[2];
	if (chdir(path) == -1)
		fatal(111, "chdir", path);

	free(list[0]);

	execvp(*argv, argv);
	fatal(111, "exec", *argv);

	return 0;
}
