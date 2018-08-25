#include "tst_utils.h"

static int side_effect_flag = 0;

tst_begin_test_ignore(ignore, (void))
    side_effect_flag = 1;
tst_end_test

tst_begin_test(fail, (void))
    side_effect_flag = 1;
    tst_assert_eq_str("a", "b");
tst_end_test

tst_begin_test_xfail(xpass, (void))
    side_effect_flag = 1;
    tst_assert_eq_str("", "");
tst_end_test

tst_begin_test(side_effect_set, void)
    /* Check if side effect has happened then reset it back to 0 */
    tst_assert_ne_int(side_effect_flag, 0);
    side_effect_flag = 0;
tst_end_test

void ignore_tests(void)
{
    tst_begin_suite(IGNORE) {
        tst_test(ignore, ());
        tst_test(side_effect_set, ());
        tst_test_msg_xfail(ignore, "should ignore even when running with xfail", ());
        tst_test(side_effect_set, ());
        tst_test_ignore(ignore, ());
        tst_test(side_effect_set, ());

        tst_test_ignore(fail, ());
        tst_test(side_effect_set, ());
        tst_test_ignore(xpass, ());
        tst_test(side_effect_set, ());
    } tst_end_suite
}
