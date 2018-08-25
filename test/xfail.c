#include "tst_utils.h"

tst_begin_test(is_ten, int num)
    tst_assert_eq_int(num, 10);
tst_end_test

tst_begin_test_xfail(xfail, void)
    tst_abort();
tst_end_test

void xfail_tests(void)
{
    tst_begin_suite(XFAIL) {
        tst_test_msg_xfail(is_ten, "should xfail", 9);
        tst_test_xfail(xfail,);
        tst_test_msg(xfail, "xfail marked test should xfail even when run normally",);
    } tst_end_suite
}
