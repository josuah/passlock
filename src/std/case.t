void
test_std_case(void)
{
test_lib("std/case");

test_fn("case_cmp");

	test(1, case_cmp("MESSAGE", "()") != 0);
	test(2, case_cmp("MESSAGE`", "MessAgE`") == 0);

test_fn("case_cmpn");

	test(1, case_cmpn("1EfG1234", "1eFG4321", 4) == 0);
	test(2, case_cmpn("1EfG1234", "1eFG4321", 9) != 0);
	test(3, case_cmpn("1EfG1234", "1eFG4321", 4) == 0);
	test(4, case_cmpn("ANSWERED?", "ANSWERED", 9) != 0);

test_fn("case_start");

	test(1, case_start("", "SENT") == 0);
	test(2, case_start("", "CHARSET ") == 0);
}
