#ifndef STD_TEST_H
#define STD_TEST_H

#include <stddef.h>

#define test_ok (!test_err)

size_t test_count;
size_t test_err;

void            test(int, int);
void            test_fn(char const *);
void            test_init(void);
void            test_lib(char const *);
void            test_summary(void);

#endif
