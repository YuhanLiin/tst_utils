#include "tst_utils.h"

// These tests will actually fail so that the failure messages can be verified

tst_begin_test(fail, void)
{
    tst_abort();
} tst_end_test

tst_begin_test(fail_with_args, int x, int y)
{
    (void)x; (void)y;
    tst_abort();
} tst_end_test

tst_begin_test(fail_assertion, void)
{
    tst_assert_eq_int(0, 1);
} tst_end_test

// Quarantine all actual failures to a separate test environment, hence the main()
int main(void)
{
    tst_begin_suite(FAIL)
    {
        tst_test(fail,);
        tst_test(fail_with_args, 42, 32);
        tst_test(fail_assertion,);
    } tst_end_suite

    return tst_results();
}
