#include "tst_utils.h"

#include "test/all_tests.h"

tst_begin_test(empty, void)
{
} tst_end_test

int main(void)
{
    tst_test_msg(empty, "top level test",);
    passing_tests();
    xfail_tests();
    ignore_tests();
    asserts_passing_tests();
    asserts_xfailing_tests();
    teardown_tests();
    macro_expansion_tests();
    array_asserts_passing_tests();
    array_asserts_xfailing_tests();

    return tst_results();
}
