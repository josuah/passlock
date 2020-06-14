#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/file.h>
#include <time.h>
#include <unistd.h>

#include "log.h"
#include "util.h"

int
main(void)
{
	char buf[2048], *s, *e, *user, *pass, *date;
	int c;
	FILE *fp;

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
	date = ++s;
	if ((s = memchr(s, '\0', e-s)) == NULL)
		die("no timestamp");

	die("read following credentials user=%s pass=%s date=%s", user, pass, date);
	return 1;
}
