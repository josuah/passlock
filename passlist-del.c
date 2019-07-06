#include "arg.h"
#include "buffer.h"
#include "die.h"
#include "fmt.h"
#include "listxt.h"
#include "log.h"
#include "open.h"
#include "stralloc.h"
#include <stdio.h> /* for rename(2) */

char *flag_f = "/etc/passlist/default";

void
usage(void)
{
	log_u(arg_0, "[-f passfile] user");
}

int
main(int argc, char **argv)
{
	char *user;
	char *gs[3];
	char bis[1024];
	char bos[1024];
	genalloc ga = GENALLOC_INIT(gs);
	buffer bi = BUFFER_INIT(read, 0, bis, sizeof bis);
	buffer bo = BUFFER_INIT(write, 0, bos, sizeof bos);
	stralloc line = STRALLOC_INIT(0);
	stralloc tmp = STRALLOC_INIT(0);

	log_init();

	ARG_BEGIN {
	case 'f': flag_f = ARG; break;
	default: usage();
	} ARG_END;

	if (!(user = *argv++)) usage();
	if (*argv) usage();

	if (!listxt_valid(user)) die_invalid("username");
	if (!listxt_get(flag_f, &line, &ga, 0, user)) die_open(flag_f);
	if (genalloc_len(char *, &ga) == 0) die_absent(user, flag_f);

	if (!listxt_tmp(&tmp, flag_f)) die_nomem();
	if ((bi.fd = open_read(flag_f)) == -1) die_open(flag_f);
	if ((bo.fd = open_truncate(tmp.s)) == -1) die_open(tmp.s);

	while (listxt_getline(&bi, &line, &ga)) {
		if (genalloc_len(char *, &ga) == 0) continue;
		if (str_equal(genalloc_s(char *, &ga)[0], user)) continue;
		if (!listxt_put(&bo, &ga)) die_write();
	}
	if (!buffer_flush(&bo)) die_write();

	if (rename(tmp.s, flag_f) == -1) die_rename(tmp.s, flag_f);

	return 0;
}
