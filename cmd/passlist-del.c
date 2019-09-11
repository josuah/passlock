#include "std/arg.h"
#include "std/buffer.h"
#include "std/fmt.h"
#include "std/listxt.h"
#include "std/log.h"
#include "std/open.h"
#include "std/stralloc.h"
#include <stdio.h> /* for rename(2) */

char *flag_f = "/etc/passlist/default";

void
usage(void)
{
	log_usage(arg_0, " [-v] [-f passfile] user");
}

int
main(int argc, char **argv)
{
	char *user;
	char bis[1024];
	char bos[1024];
	struct genalloc ga = GENALLOC_INIT;
	struct buffer bi = BUFFER_INIT(read, 0, bis, sizeof bis);
	struct buffer bo = BUFFER_INIT(write, 0, bos, sizeof bos);
	struct stralloc line = STRALLOC_INIT;
	struct stralloc tmp = STRALLOC_INIT;

	log_init(3);

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

	if (!(user = *argv++)) usage();
	if (*argv) usage();

	if (!listxt_valid(user)) log_fatal(111, "invalid username");
	if (!listxt_get(flag_f, &line, &ga, 0, user)) log_fatal(111, "open ", flag_f);
	if (genalloc_len(char *, &ga) == 0) log_fatal(111, "user ",user," absent from ",flag_f);

	if (!listxt_tmp(&tmp, flag_f)) log_fatal(111, "alloc");
	if ((bi.fd = open_read(flag_f)) == -1) log_fatal(111, "open ",flag_f);
	if ((bo.fd = open_truncate(tmp.s)) == -1) log_fatal(111, "open ",tmp.s);

	while (listxt_getline(&bi, &line, &ga)) {
		if (genalloc_len(char *, &ga) == 0) continue;
		if (str_equal(genalloc_s(char *, &ga)[0], user)) continue;
		if (!listxt_put(&bo, &ga)) log_fatal(111, "write");
	}
	if (!buffer_flush(&bo)) log_fatal(111, "write");

	if (rename(tmp.s, flag_f) == -1) log_fatal(111, tmp.s," -> ",flag_f);

	return 0;
}
