#include "passlock.h"

#include <assert.h>
#include <ctype.h>
#include <stdint.h>
#include <string.h>

#include "compat.h"

char *
passlock_strerror(int i)
{
	enum passlock_err err = (i > 0) ? i : -i;

	switch (err) {
	case PASSLOCK_ERR_MISSING_AT_SIGN:
		return "missing '@' from input";
	case PASSLOCK_ERR_NAME_TOO_LONG:
		return "name too long for this buffer";
	case PASSLOCK_ERR_INVALID_USERNAME:
		return "invalid username:"
		  " '/' characters, \".\" and \"..\", empty parts"
		  "... are forbidden";
	case PASSLOCK_ERR_MISSING_MAIL_LOCAL_PART:
		return "assuming the username is an email, the local part"
		  " (before '@') is missing";
	case PASSLOCK_ERR_MISSING_MAIL_DOMAIN_PART:
		return "assuming the username is an email, the domain part"
		  " (after '@') is missing";
	case PASSLOCK_ERR_BAD_PERCENT_CHAR:
		return "unknown percent expansion character";
	}
	assert(!"invalid passlock error code");
	return "unknown passlock error";
}

int
passlock_username_is_valid(char *username)
{
	if (strcmp(username, ".") == 0 || strcmp(username, "..") == 0)
		return 0; /* special semantics */

	if (username[0] == '\0')
		return 0; /* too short */

        for (char *s = username; *s != '\0'; s++)
                if ((!isalnum(*s) && !ispunct(*s)) || *s == '/')
			return 0; /* invalid char */
        return 1;
}

static int
passlock_expand_percent_d(char **buf, size_t *sz, char *username)
{
	char *at, *domain_part;
	size_t n;

	at = strchr(username, '@');
	if (at == NULL)
		return -PASSLOCK_ERR_MISSING_AT_SIGN;
	domain_part = at + 1;

	n = strlcpy(*buf, domain_part, strlen(domain_part) + 1);
	if (n >= *sz)
		return -PASSLOCK_ERR_NAME_TOO_LONG;
	if (n == 0)
		return -PASSLOCK_ERR_MISSING_MAIL_DOMAIN_PART;

	*buf += n;
	*sz += n;
	return 0;
}

static int
passlock_expand_percent_l(char **buf, size_t *sz, char *username)
{
	char *at;
	size_t n;

	at = strchr(username, '@');
	if (at == NULL)
		return -PASSLOCK_ERR_MISSING_AT_SIGN;

	n = at - username;
	if (n + 1 >= *sz)
		return -PASSLOCK_ERR_NAME_TOO_LONG;
	if (n == 0)
		return -PASSLOCK_ERR_MISSING_MAIL_LOCAL_PART;

	memcpy(*buf, username, n);
	(*buf)[n] = '\0';

	*buf += n;
	*sz += n;
	return 0;
}

static int
passlock_expand_percent_u(char **buf, size_t *sz, char *username)
{
	size_t n;

	n = strlcpy(*buf, username, *sz);
	if (n >= *sz)
		return -PASSLOCK_ERR_NAME_TOO_LONG;

	*buf += n;
	*sz += n;
	return 0;
}

static int
passlock_expand_percent_percent(char **buf, size_t *sz, char *ignored)
{
	(void)ignored;

	if (1 > *sz)
		return -PASSLOCK_ERR_NAME_TOO_LONG;
	**buf = '%';

	*buf += 1;
	*sz += 1;
	return 0;
}

static int
(*passlock_expand_fn[UINT8_MAX + 1])(char **, size_t *, char *) = {
	['l'] = passlock_expand_percent_l,
	['d'] = passlock_expand_percent_d,
	['u'] = passlock_expand_percent_u,
	['%'] = passlock_expand_percent_percent,
};

int
passlock_expand_str(char *buf, size_t sz, char *fmt, char *username)
{
	int ret;

	if (!passlock_username_is_valid(username))
		return -PASSLOCK_ERR_INVALID_USERNAME;

	for (char *s = fmt; *s != '\0'; s++) {
		if (*s == '%') {
			unsigned char c = *++s;

			if (passlock_expand_fn[c] == NULL)
				return -PASSLOCK_ERR_BAD_PERCENT_CHAR;
			ret = passlock_expand_fn[c](&buf, &sz, username);
			if (ret < 0)
				return ret;
		} else {
			if (--sz == 0)
				return -PASSLOCK_ERR_NAME_TOO_LONG;
			*buf++ = *s;
		}
	}

	if (--sz == 0)
		return -PASSLOCK_ERR_NAME_TOO_LONG;
	*buf++ = '\0';

	return 0;
}
