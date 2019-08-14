#include "arg.h"
#include "buffer.h"
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
	log_usage(arg_0, " [-v] [-f passfile] user");
}

int
main(int argc, char **argv)
{
	char *user;
	char bis[1024];
	char bos[1024];
	genalloc ga = GENALLOC_INIT;
	buffer bi = BUFFER_INIT(read, 0, bis, sizeof bis);
	buffer bo = BUFFER_INIT(write, 0, bos, sizeof bos);
	stralloc line = STRALLOC_INIT;
	stralloc tmp = STRALLOC_INIT;

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

	if (!(user = *argv++)) usage();
	if (*argv) usage();

	if (!listxt_valid(user)) log_fatalsys("invalid username");
	if (!listxt_get(flag_f, &line, &ga, 0, user)) log_fatalsys("open ", flag_f);
	if (genalloc_len(char *, &ga) == 0) log_fatalsys("user ",user," absent from ",flag_f);

	if (!listxt_tmp(&tmp, flag_f)) log_fatalsys("alloc");
	if ((bi.fd = open_read(flag_f)) == -1) log_fatalsys("open ",flag_f);
	if ((bo.fd = open_truncate(tmp.s)) == -1) log_fatalsys("open ",tmp.s);

	while (listxt_getline(&bi, &line, &ga)) {
		if (genalloc_len(char *, &ga) == 0) continue;
		if (str_equal(genalloc_s(char *, &ga)[0], user)) continue;
		if (!listxt_put(&bo, &ga)) log_fatalsys("write");
	}
	if (!buffer_flush(&bo)) log_fatalsys("write");

	if (rename(tmp.s, flag_f) == -1) log_fatalsys(tmp.s," -> ",flag_f);

	return 0;
}
