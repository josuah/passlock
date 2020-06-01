#include <errno.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <sodium.h>

#include "log.h"
#include "util.h"

char *arg0 = NULL;
char **argv = NULL;
char *flag['z'];

char *dummy = "$argon2id$v=19$m=262144,t=3,p=1$4ES6M9HdwRuJmqzp4txihg$Dvxnm4JcP0uMZU0J6KF8zVuzIVlQH6miDEM1eclYScM";

void
usage(void)
{
	fprintf(stdout, "usage: %s"
	 " [-v] -h /path/%%/home/ -p /path/%%/pass/ prog...\n", arg0);
	exit(1);
}

int
main(int argc, char **argv)
{
	char path_home[2048], path_pass[2048], buf[2048];
	char *s, *e, *user, *pass, *date, *hash;
	size_t sz;
	int c, ms;
	FILE *fp;
	struct timespec ts;

	flag['s'] = "1000";

	arg0 = *argv;
	while ((c = getopt(argc, argv, "h:p:")) > -1) {
		if (c == '?')
			usage();
		flag[c] = optarg ? optarg : "1";
	}
	argc -= optind;
	argv += optind;

	if (flag['v'] != NULL)
		fprintf(stdout, "%s\n", VERSION), exit(0);
	if (flag['s'] != NULL)
		if ((ms = atoi(flag['s'])) < 2)
			warn("invalid number"), usage();
	if (flag['h'] == NULL)
		usage();
	if (flag['p'] == NULL)
		usage();
	if (*argv == NULL)
		usage();

	ms += ms / 2 - randombytes_uniform(ms / 2);

	if ((fp = fdopen(3, "r")) == NULL)
		die("setting buffering on fd3");
	e = buf;
	while ((c = fgetc(fp)) != EOF && e < buf + sizeof(buf))
		*e++ = c;
	if (ferror(fp) || e == buf + sizeof(buf))
		die("reading fd3");
	fclose(fp);

	user = s = buf;
	if ((s = memchr(s, '\0', e-s)) == NULL)
		die("no username");
	pass = ++s;
	if ((s = memchr(s, '\0', e-s)) == NULL)
		die("no passphrase");
	date = ++s;
	if ((s = memchr(s, '\0', e-s)) == NULL)
		die("no timestamp");
	(void)date;

	if (path_fmt(path_home, sizeof(path_home), flag['h'], user) < 0)
		die("formatting home path out of '%s'", flag['p']);
	if (path_fmt(path_pass, sizeof(path_pass), flag['p'], user) < 0)
		die("formatting pass path out of '%s'", flag['p']);
	if ((fp = fopen(path_pass, "r")) == NULL) {
		warn("opening '%s' for reading", path_pass);
		goto dummy;
	}
	if (getline(&hash, &sz, fp) == -1)
		die("reading %s", path_pass);
	strchomp(hash);
	fclose(fp);

	debug("checking password for '%s'", user);
	if (crypto_pwhash_str_verify(hash, pass, strlen(pass)) < 0) {
		errno = 0; /* not a helpful message */
		warn("invalid password: user=%s hash=%s", user, hash);
		goto sleep;
	}
	free(hash);

	info("user could log in: '%s', executing %s", user, *argv);
	if (chdir(path_home) < 0)
		die("chdir", path_home);

	execvp(*argv, argv);
	die("exec", *argv);
dummy:
	debug("hash a dummy password to prevent statistical timing attacks");
	if (crypto_pwhash_str_verify(dummy, "", 1) < 0)
		{/* nothing */}
	errno = 0;
sleep:
	debug("sleeping for %dms to prevent timing attacks", ms);
	ts.tv_sec = ms / 1000;
	ts.tv_nsec = ms % 1000 * 1000000;
	while (nanosleep(&ts, &ts) < 0)
		continue;
	return 1;
}
