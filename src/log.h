#ifndef LOG_H
#define LOG_H

#include <stdarg.h>

#define log_usage(...)		log_(1, 0, "usage", __VA_ARGS__, (char*)0)
#define log_bug(...)		log_(101, 0, "bug", __VA_ARGS__, (char*)0)
#define log_fatal(e, ...)	log_(e, 1, "fatal", __VA_ARGS__, (char*)0)
#define log_error(...)		log_(0, 2, "error", __VA_ARGS__, (char*)0)
#define log_warn(...)		log_(0, 3, "warn", __VA_ARGS__, (char*)0)
#define log_info(...)		log_(0, 4, "info", __VA_ARGS__, (char*)0)
#define log_debug(...)		log_(0, 5, __func__, __VA_ARGS__, (char*)0)

/**/
void		log_init		(int);
void		log_va			(int, int, char *, va_list);
void		log_			(int, int, char const *, ...);

#endif
