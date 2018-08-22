#include "tst_utils.h"

tst_begin_test(int_asserts, void)
{
    tst_assert_eq_int(-1, -1);
    tst_assert_ne_int(-2, -1);
    tst_assert_le_int(-2, -1);
    tst_assert_lt_int(-2, -1);
    tst_assert_ge_int(-2, -4);
    tst_assert_gt_int(-2, -4);
    tst_assert_ge_int(0, 0);
    tst_assert_le_int(0, 0);
} tst_end_test

tst_begin_test(long_asserts, void)
{
    tst_assert_eq_long(-1, -1);
    tst_assert_ne_long(-2, -1);
    tst_assert_le_long(-2, -1);
    tst_assert_lt_long(-2, -1);
    tst_assert_ge_long(-2, -4);
    tst_assert_gt_long(-2, -4);
    tst_assert_ge_long(0, 0);
    tst_assert_le_long(0, 0);
} tst_end_test

tst_begin_test(uint_asserts, void)
{
    tst_assert_eq_uint(1, 1);
    tst_assert_ne_uint(2, 1);
    tst_assert_ge_uint(2, 1);
    tst_assert_gt_uint(2, 1);
    tst_assert_le_uint(2, 4);
    tst_assert_lt_uint(2, 4);
    tst_assert_ge_uint(0, 0);
    tst_assert_le_uint(0, 0);
} tst_end_test

tst_begin_test(ulong_asserts, void)
{
    tst_assert_eq_ulong(1, 1);
    tst_assert_ne_ulong(2, 1);
    tst_assert_ge_ulong(2, 1);
    tst_assert_gt_ulong(2, 1);
    tst_assert_le_ulong(2, 4);
    tst_assert_lt_ulong(2, 4);
    tst_assert_ge_ulong(0, 0);
    tst_assert_le_ulong(0, 0);
} tst_end_test

tst_begin_test(size_asserts, void)
{
    tst_assert_eq_size(1, 1);
    tst_assert_ne_size(2, 1);
    tst_assert_ge_size(2, 1);
    tst_assert_gt_size(2, 1);
    tst_assert_le_size(2, 4);
    tst_assert_lt_size(2, 4);
    tst_assert_ge_size(0, 0);
    tst_assert_le_size(0, 0);
} tst_end_test

tst_begin_test(char_asserts, void)
{
    tst_assert_eq_char('a', 'a');
    tst_assert_ne_char('b', 'a');
    tst_assert_ge_char('b', 'a');
    tst_assert_gt_char('b', 'a');
    tst_assert_le_char('b', 'k');
    tst_assert_lt_char('b', 'k');
    tst_assert_ge_char('0', '0');
    tst_assert_le_char('0', '0');
} tst_end_test

tst_begin_test(ptr_asserts, void)
{
    char arr[2] = {0};
    tst_assert_eq_ptr(&arr[0], &arr[0]);
    tst_assert_ne_ptr(&arr[1], NULL);
    tst_assert_ge_ptr(&arr[1], &arr[0]);
    tst_assert_gt_ptr(&arr[1], &arr[0]);
    tst_assert_le_ptr(&arr[0], &arr[1]);
    tst_assert_lt_ptr(&arr[0], &arr[1]);
    tst_assert_ge_ptr(NULL, NULL);
    tst_assert_le_ptr(NULL, NULL);
} tst_end_test

tst_begin_test(str_asserts, void)
{
    tst_assert_eq_str("abc", "abc");
    tst_assert_ne_str("b", "a");
    tst_assert_ge_str("b", "ag");
    tst_assert_gt_str("b", "ag");
    tst_assert_le_str("b", "k");
    tst_assert_lt_str("b", "k");
    tst_assert_ge_str("", "");
    tst_assert_le_str("", "");
} tst_end_test

tst_begin_test(dbl_asserts, void)
{
    tst_assert_ge_dbl(2.5, 1.5);
    tst_assert_gt_dbl(2.5, 1.5);
    tst_assert_le_dbl(2.5, 4.5);
    tst_assert_lt_dbl(2.5, 4.5);
    tst_assert_ge_dbl(0.5, 0.5);
    tst_assert_le_dbl(0.5, 0.5);
} tst_end_test

tst_begin_test(divisible, int a, int b)
{
    tst_assert_eq_int(a % b, 0);
} tst_end_test

void run_test_in_func(void)
{
    tst_test_msg(divisible, "should run perfectly when called from another function", 2, 1);
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
            tst_test(int_asserts,);
            tst_test(long_asserts,);
            tst_test(uint_asserts,);
            tst_test(ulong_asserts,);
            tst_test(size_asserts,);
            tst_test(char_asserts,);
            tst_test(ptr_asserts,);
            tst_test(str_asserts,);
            tst_test(dbl_asserts,);
        } tst_end_suite

        tst_begin_suite(TESTS_WITH_PARAMETERS)
        {
            tst_test_msg(divisible, "2 div 1", 2, 1);
            tst_test_msg(divisible, "2 div 2", 2, 2);
            tst_test_msg(divisible, "4 div 1", 4, 1);
        } tst_end_suite

        run_test_in_func();
    } tst_end_suite
}
