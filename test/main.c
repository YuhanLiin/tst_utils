#include "tst_utils.h"

tst_begin_test(empty, void)
{
} tst_end_test

tst_begin_test(obvious, void)
{
    tst_assert_eq_int(1 + 1, 2);
} tst_end_test

tst_begin_test(divisible, int a, int d)
{
    tst_assert_eq_int(a % d, 0);
} tst_end_test

tst_begin_suite(INT) 
{
    tst_test(empty,);
    tst_test_msg(divisible, "4 by 2", 4, 2);
    tst_test_msg(divisible, "6 by 3", 6, 3);
} tst_end_suite

int main(void)
{
    tst_test(empty,);
    tst_test_msg(obvious, "obviously the case",);
    tst_test(divisible, 4, 2);
    tst_suite(INT);
    return tst_results();
}
