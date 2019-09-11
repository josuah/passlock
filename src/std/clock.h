#ifndef STD_CLOCK_H
#define STD_CLOCK_H

#define clock_after(t1, t2) ((t1)->tv_sec == (t2)->tv_sec ? \
	(t1)->tv_nsec > (t2)->tv_nsec : (t1)->tv_sec > (t2)->tv_sec)

#endif
