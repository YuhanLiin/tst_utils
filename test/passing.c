#include "tst_utils.h"

tst_begin_test(divisible, int a, int b)
{
    tst_assert_eq_int(a % b, 0);
} tst_end_test

void run_test_in_func(void)
{
    tst_test_msg(divisible, "should run perfectly when called from another function", (2, 1));
}

void passing_tests(void)
{
    tst_begin_suite(PASSING_TESTS)
    {
        tst_begin_suite(EMPTY_SUITE)
        {
        } tst_end_suite

        tst_begin_suite(PASSING_ASSERTS)
        {
            tst_test(int_asserts, ());
            tst_test(long_asserts, ());
            tst_test(uint_asserts, ());
            tst_test(ulong_asserts, ());
            tst_test(size_asserts, ());
            tst_test(char_asserts, ());
            tst_test(ptr_asserts, ());
            tst_test(str_asserts, ());
            tst_test(dbl_asserts, ());
        } tst_end_suite

        tst_begin_suite(TESTS_WITH_PARAMETERS)
        {
            tst_test_msg(divisible, "2 div 1", (2, 1));
            tst_test_msg(divisible, "2 div 2", (2, 2));
            tst_test_msg(divisible, "4 div 1", (4, 1));
        } tst_end_suite

        run_test_in_func();
    } tst_end_suite
}
