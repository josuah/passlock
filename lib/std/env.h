#ifndef STD_ENV_H
#define STD_ENV_H

#include <stdlib.h>

#define env_get(name)          getenv(name)
#define env_set(name, value)   !setenv(name, value, 1)
#define env_unset(name, value) !unsetenv(name, value, 1)

#endif
