void
test_std_case(void)
{
	test_lib("std/case");

	test_fn("case_cmp");
	test(1, case_cmp("MESSAGE", "()") != 0);
	test(1, case_cmp("MESSAGE`", "MessAgE`") == 0);

	test_fn("case_cmpn");
	test(1, case_cmpn("1EfG1234", "1eFG4321", 4) == 0);
	test(1, case_cmpn("1EfG1234", "1eFG4321", 9) != 0);
	test(1, case_cmpn("1EfG1234", "1eFG4321", 4) == 0);
}
