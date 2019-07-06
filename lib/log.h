#ifndef LOG_H
#define LOG_H

#define log_f(e, ...)  log_put(0, e, 0, "fatal: ", __VA_ARGS__, NULL)
#define log_fs(e, ...) log_put(0, e, 1, "fatal: ", __VA_ARGS__, NULL)
#define log_u(...)     log_put(0, 1, 0, "usage: ", __VA_ARGS__, NULL)
#define log_e(...)     log_put(1, 0, 0, "error: ", __VA_ARGS__, NULL)
#define log_es(...)    log_put(1, 0, 1, "error: ", __VA_ARGS__, NULL)
#define log_w(...)     log_put(2, 0, 0, "warning: ", __VA_ARGS__, NULL)
#define log_ws(...)    log_put(2, 0, 1, "warning: ", __VA_ARGS__, NULL)
#define log_i(...)     log_put(3, 0, 0, "info: ", __VA_ARGS__, NULL)
#define log_d(...)     log_put(4, 0, 0, "debug: ", __VA_ARGS__, NULL)

extern int log_level;

// bin/make-h lib/log.c
void    log_init(void);
void    log_put(int, int, int, ...);

#endif
