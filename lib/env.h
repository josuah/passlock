#ifndef ENV_H
#define ENV_H

#include <stdlib.h>

#define env_get(name)          getenv(name)
#define env_set(name, value)   !setenv(name, value, 1)
#define env_unset(name, value) !unsetenv(name, value, 1)

#endif
