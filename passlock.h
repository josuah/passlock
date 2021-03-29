#ifndef PASSLOCK_H
#define PASSLOCK_H

#include <stddef.h>

enum passlock_err {
	PASSLOCK_ERR_MISSING_AT_SIGN = 1,
	PASSLOCK_ERR_MISSING_MAIL_LOCAL_PART,
	PASSLOCK_ERR_MISSING_MAIL_DOMAIN_PART,
	PASSLOCK_ERR_NAME_TOO_LONG,
	PASSLOCK_ERR_INVALID_USERNAME,
	PASSLOCK_ERR_BAD_PERCENT_CHAR,
};

/** src/passlock.c **/
char * passlock_strerror(int i);
int passlock_username_is_valid(char *username);
int passlock_expand_str(char *buf, size_t sz, char *fmt, char *username);

#endif
