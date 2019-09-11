#ifndef STD_LOG_H
#define STD_LOG_H

#include "std/int.h"

/*
 * Inspired from Jan Mojžíš (mojzis.com) code for tinyssh.
 */

#define log_fatal(e, ...)     log_put(0,e,__FILE__,__LINE__, "fatal: ", __VA_ARGS__, NULL)
#define log_usage(...)        log_put(0,1,__FILE__,__LINE__, "usage: ", __VA_ARGS__, NULL)
#define log_error(...)        log_put(1,0,__FILE__,__LINE__, "error: ", __VA_ARGS__, NULL)
#define log_warning(...)      log_put(2,0,__FILE__,__LINE__, "warning: ", __VA_ARGS__, NULL)
#define log_info(...)         log_put(3,0,__FILE__,__LINE__, "info: ", __VA_ARGS__, NULL)
#define log_debug(...)        log_put(4,0,__FILE__,__LINE__, "debug: ", __VA_ARGS__, NULL)
#define log_trace( ...)       log_put(5,0,__FILE__,__LINE__, "trace: ", __func__, ": ", __VA_ARGS__, NULL)

extern int log_level;

void            log_init(int);
void            log_put(int, int, char const *, u64, ...);

#endif
