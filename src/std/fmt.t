#include "std/mem.h"

void
test_std_fmt(void)
{
	char s[50];

test_lib("std/fmt");

test_fn("fmt_u");

	test(1, fmt_u(s, 345, 10) == 3);
	test(2, mem_equal(s, "345", 3));
	test(3, fmt_u(s, 0, 10) == 1);
	test(4, mem_equal(s, "0", 1));

test_fn("fmt_u0");

	test(1, fmt_u0(s, 345, 10, 10) == 10);
	test(2, mem_equal(s, "0000000345", 10));
	test(3, fmt_u0(s, 345, 2, 10) == 3);
	test(4, mem_equal(s, "345", 3));
}
