#ifndef LOG_H
#define LOG_H

#define log_fatal(...)    log_put(0, 1, 0, "fatal: ", __VA_ARGS__, NULL)
#define log_fatalsys(...) log_put(0, 111, 1, "fatal: ", __VA_ARGS__, NULL)
#define log_usage(...)    log_put(0, 1, 0, "usage: ", __VA_ARGS__, NULL)
#define log_err(...)      log_put(1, 0, 0, "error: ", __VA_ARGS__, NULL)
#define log_errsys(...)   log_put(1, 0, 1, "error: ", __VA_ARGS__, NULL)
#define log_warn(...)     log_put(2, 0, 0, "warning: ", __VA_ARGS__, NULL)
#define log_warnsys(...)  log_put(2, 0, 1, "warning: ", __VA_ARGS__, NULL)
#define log_info(...)     log_put(3, 0, 0, "info: ", __VA_ARGS__, NULL)
#define log_debug(...)    log_put(4, 0, 0, "debug: ", __VA_ARGS__, NULL)

extern int log_level;

// bin/make-h lib/log.c
void    log_init(void);
void    log_put(int, int, int, ...);

#endif
