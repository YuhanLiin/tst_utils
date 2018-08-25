#include "tst_utils.h"

tst_begin_test(is_zero, int num)
    tst_assert_eq_int(num, 0);
tst_end_test

tst_begin_test_xfail(xpass, void)
{
}
tst_end_test

int main(void)
{
    tst_begin_suite(XPASS) {
        tst_test_xfail(is_zero, 0);
        tst_test_xfail_msg(is_zero, "should not pass", 0);

        tst_test_xfail(xpass,);
        tst_test_msg(xpass, "should xpass even when ran normally",);
    } tst_end_suite

    return tst_results();
}
