#include "log.h"
#include "env.h"
#include "int.h"
#include "str.h"

void
log_init(void)
{
	char *s;
	u32 u;

	if (!(s = env_get("LOG_LEVEL"))) return;
	if (s[u32_scan_base(&u, s, strlen(s), 10)] != '\0') return;
	log_level = u;
}
