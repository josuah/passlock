void
test_std_fmt(void)
{
	char s[50];

	test_lib("std/fmt");

	test_fn("fmt_ulong");
	test(1, fmt_ulong(s, 345) == 3);
	test(2, mem_equal(s, "345", 3));
	test(3, fmt_ulong(s, 0) == 1);
	test(4, mem_equal(s, "0", 1));

	test_fn("fmt_ulong0");
	test(1, fmt_ulong0(s, 345, 10) == 10);
	test(2, mem_equal(s, "0000000345", 10));
	test(3, fmt_ulong0(s, 345, 2) == 3);
	test(4, mem_equal(s, "345", 3));
}
