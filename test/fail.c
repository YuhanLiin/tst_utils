#include "tst_utils.h"

// These tests will actually fail so that the failure messages can be verified

tst_begin_test(fail, void)
{
    tst_abort();
} tst_end_test

tst_begin_test(unexpected_pass, void)
{
} tst_end_test

tst_begin_test(fail_with_args, int x, int y)
{
    (void)x; (void)y;
    tst_abort();
} tst_end_test

tst_begin_test(unexpected_pass_with_args, int x, int y)
{
    (void)x; (void)y;
} tst_end_test

tst_begin_suite(FAIL)
{
    tst_test(fail,);
    tst_test_xfail(unexpected_pass,);
    tst_test(fail_with_args, 42, 32);
    tst_test_xfail(unexpected_pass_with_args, 42, 32);
} tst_end_suite

int main(void)
{
    tst_suite(FAIL);
    return tst_results();
}
