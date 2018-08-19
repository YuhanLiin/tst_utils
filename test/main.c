#include "tst_utils.h"

tst_begin_test(empty, void)
{
} tst_end_test

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

tst_begin_suite(SUITE_WITH_ASSERT)
{
    tst_assert_ne_int(0, 0);
} tst_end_suite

tst_begin_suite(ASSERTS)
{
    tst_test(int_asserts,);
    tst_test(long_asserts,);
} tst_end_suite

tst_begin_suite(ALL_SUITES)
{
    tst_suite(ASSERTS);
    tst_suite(SUITE_WITH_ASSERT);
} tst_end_suite

int main(void)
{
    tst_test_msg(empty, "top level test",);
    tst_suite(ALL_SUITES);
    return tst_results();
}
