#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <time.h>
#include <unistd.h>

#include <sodium.h>

#include "compat.h"
#include "log.h"
#include "passlock.h"

char *arg0;
char *flag['z'];

void
usage(void)
{
	fprintf(stderr, "usage: %s"
	  " [-v] [-s ms] -h /path/%%/home/ -p /path/%%/pass prog...\n", arg0);
	exit(1);
}

int
main(int argc, char **argv)
{
	char path_home[2048], path_pass[2048], buf[2048];
	char *s, *e, *user, *pass, *hash = NULL;
	size_t sz = 0;
	int c, sec = 0, ms = 0;
	FILE *fp;
	struct timespec ts;

	flag['s'] = "1";

	arg0 = *argv;
	while ((c = getopt(argc, argv, "s:h:p:")) > -1) {
		if (c == '?')
			usage();
		flag[c] = optarg ? optarg : "1";
	}
	argc -= optind;
	argv += optind;

	if (flag['v'] != NULL) {
		fprintf(stdout, "%s\n", VERSION);
		exit(0);
	}
	if (flag['s'] != NULL) {
		sec = atoi(flag['s']);
		if (sec == 0) {
			warn("invalid number");
			usage();
		}
	}
	if (flag['h'] == NULL)
		usage();
	if (flag['p'] == NULL)
		usage();
	if (*argv == NULL)
		usage();

	ms = sec * 2000 - randombytes_uniform(sec * 2000);

	debug("reading credentials from fd3");
	if ((fp = fdopen(3, "r")) == NULL)
		die("setting buffering on fd3");
	e = buf;
	while ((c = fgetc(fp)) != EOF && e < buf + sizeof(buf))
		*e++ = c;
	if (ferror(fp) || e == buf + sizeof(buf))
		die("reading fd3");
	fclose(fp);

	debug("parsing credentials");
	user = s = buf;
	if ((s = memchr(s, '\0', e-s)) == NULL)
		die("no username");
	pass = ++s;
	if ((s = memchr(s, '\0', e-s)) == NULL)
		die("no passphrase");

	/* ignore the trailing data */

	debug("formatting the home and pass paths");
	if (passlock_expand_str(path_home, sizeof(path_home), flag['h'], user) < 0)
		die("formatting home path out of '%s'", flag['p']);
	sz = sizeof(path_pass);
	if (passlock_expand_str(path_pass, sizeof(path_pass), flag['p'], user) < 0)
		die("formatting passfile path out of '%s'", flag['p']);

	debug("reading the password hash from filesystem");
	fp = fopen(path_pass, "r");
	if (fp == NULL) {
		warn("opening '%s' for reading", path_pass);
		goto sleep1;
	}
	if (getline(&hash, &sz, fp) < 0)
		die("reading %s", path_pass);
	sz = 0;
		debug("%c", hash[0]);
	strchomp(hash);
	fclose(fp);

	debug("checking password for '%s'", user);
	if (crypto_pwhash_str_verify(hash, pass, strlen(pass)) < 0) {
		warn("invalid password: user=%s hash=%s", user, hash);
		goto sleep2;
	}
	free(hash);

	info("user could log in: '%s', executing %s", user, *argv);
	if (chdir(path_home) < 0)
		die("chdir %s", path_home);
	if (setenv("HOME", path_home, 1) < 0)
		die("setenv HOME=%s", path_home);
	if (setenv("USER", user, 1) < 0)
		die("setenv USER=%s", user);

	debug("executing %s", *argv);
	execvp(*argv, argv);
	die("executing %s", *argv);

sleep1:
	debug("sleeping for attenuating statistical attacks", ms);
	sleep(1);

sleep2:
	debug("sleeping for %dms to blur timing attacks", ms);
	ts.tv_sec = ms / 1000;
	ts.tv_nsec = ms % 1000 * 1000000;
	nanosleep(&ts, &ts);

	return 1;
}
