#include "tst_utils.h"

static int teardown_flag;
static int body_flag;

// On failure, this test sets the teardown flag and ignores the body flag. Otherwise both are set.
tst_begin_test(teardown_test, int pass)
{
    teardown_flag = 0;
    body_flag = 0;
    if (!pass) tst_abort();
    int unused; (void)unused;
    body_flag = 1;
tst_teardown:
    teardown_flag = 1;
} tst_end_test_teardown

// Test whether the teardown and actual body of the test was reached
tst_begin_test(teardown_set, void)
{
    tst_assert_ne_int(teardown_flag, 0);
} tst_end_test

tst_begin_test(body_set, void)
{
    tst_assert_ne_int(body_flag, 0);
} tst_end_test

tst_begin_test(body_not_set, void)
{
    tst_assert_eq_int(body_flag, 0);
} tst_end_test


tst_begin_suite(TEARDOWN)
{
    tst_test(teardown_test, 1);
    tst_test_msg(teardown_set, "teardown should occur on test pass",);
    tst_test_msg(body_set, "test body should not be skipped on test pass",);

    tst_test_xfail(teardown_test, 0);
    tst_test_msg(teardown_set, "teardown should occur on test failure",);
    tst_test_msg(body_not_set, "test body should be skipped on test failure",);
} tst_end_suite

void teardown_tests(void)
{
    tst_suite(TEARDOWN);
}
