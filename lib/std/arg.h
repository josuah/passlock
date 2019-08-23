#ifndef STD_ARG_H
#define STD_ARG_H

#define ARG_BEGIN \
	arg_0 = *argv; (void)argc; \
	while ((*++argv) && (*argv)[0] == '-' && (*argv)[1] != '\0') { \
	if ((*argv)[1] == '-' && (*argv)[2] == '\0') { ++argv; break; } \
		for (int brk = 0; !brk && *++*argv != '\0' ;) { switch (**argv)

#define ARG_END } } 

#define ARG ((*++*argv != '\0' || *++argv != NULL) ? ((brk = 1), *argv) : (usage(), NULL))

extern char const *arg_0;

#endif
