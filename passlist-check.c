#include <assert.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <sodium.h>

#include "listxt.h"
#include "log.h"

char *file = "/etc/passlist/default";
char *arg0;
char *dummy = "$argon2id$v=19$m=262144,t=3,p=1$4ES6M9HdwRuJmqzp4txihg$Dvxnm4JcP0uMZU0J6KF8zVuzIVlQH6miDEM1eclYScM";

void
usage(void)
{
	fprintf(stdout, "usage: %s [-v] [-f passfile] [-s sleep] prog...\n", arg0);
	exit(1);
}

int
main(int argc, char **argv)
{
	char c, *s, *e, *user, *pass, *date, buf[2048];
	char *line, *hash, *path;
	ssize_t hn, pn;
	FILE *fp;
	int ms;
	struct timespec ts;

	ms = 1000;
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
			ms = atoi(optarg);
			if (ms < 2) {
				error("invalid number");
				usage();
			}
			break;
		case '?':
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	ms += ms / 2 - randombytes_uniform(ms / 2);

	if (*argv == NULL)
		usage();

	debug("read the file descriptor 3 for user and password information");

	assert(fp = fdopen(3, "r"));
	e = buf;
	while (e < buf + sizeof(buf) && (c = fgetc(fp)) != EOF)
		*e++ = c;
	if (ferror(fp) || e == buf + sizeof(buf))
		fatal(111, "read fd 3");
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

	debug("search the pass file for a matching entry");

	line = listxt_get(file, 0, user);
	if (errno)
		fatal(111, "read ", file);
	if (line == NULL) {
		warn("unknown user");
		goto dummy;
	}

	hn = listxt_field(line, 1, &hash);
	if (hn < 0) {
		error("no hash field for this entry");
		goto dummy;
	}

	pn = listxt_field(line, 2, &path);
	if (pn == -1) {
		error("no path field for this entry");
		goto dummy;
	}

	info("verifying the password");

	hash = strsep(&hash, ":");
	if (crypto_pwhash_str_verify(hash, pass, strlen(pass)) == -1) {
		errno = 0; warn("invalid password: user=%s pass=%s hash=%s", user, pass, hash);
		goto sleep;
	}

	if (chdir(path) == -1)
		fatal(111, "chdir", path);

	free(line);

	execvp(*argv, argv);
	fatal(111, "exec", *argv);

dummy:
	debug("hash a dummy password");
	(void)crypto_pwhash_str_verify(dummy, "", 1);
	errno = 0;
sleep:
	debug("sleeping for %dms", ms);
	ts.tv_sec = ms / 1000;
	ts.tv_nsec = ms % 1000 * 1000 * 1000;
	while (nanosleep(&ts, &ts) == -1)
		continue;
	return 1;
}
