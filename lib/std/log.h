#ifndef STD_LOG_H
#define STD_LOG_H

#include "std/int.h"

#define log_fatal(e, ...)     log_put(0,e,0,__FILE__,__LINE__, "fatal: ", __VA_ARGS__, NULL)
#define log_fatal_sys(e, ...) log_put(0,e,1,__FILE__,__LINE__, "fatal: ", __VA_ARGS__, NULL)
#define log_usage(...)        log_put(0,1,0,__FILE__,__LINE__, "usage: ", __VA_ARGS__, NULL)
#define log_error(...)        log_put(1,0,0,__FILE__,__LINE__, "error: ", __VA_ARGS__, NULL)
#define log_error_sys(...)    log_put(1,0,1,__FILE__,__LINE__, "error: ", __VA_ARGS__, NULL)
#define log_warning(...)      log_put(2,0,0,__FILE__,__LINE__, "warning: ", __VA_ARGS__, NULL)
#define log_warning_sys(...)  log_put(2,0,1,__FILE__,__LINE__, "warning: ", __VA_ARGS__, NULL)
#define log_info(...)         log_put(3,0,0,__FILE__,__LINE__, "info: ", __VA_ARGS__, NULL)
#define log_debug(...)        log_put(4,0,0,__FILE__,__LINE__, "debug: ", __VA_ARGS__, NULL)

extern int log_level;

void            log_init(void);
void            log_put(int, int, int, char const *, u64, ...);

#endif
