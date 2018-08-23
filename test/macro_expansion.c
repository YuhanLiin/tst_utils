// These test the corner cases of the macro expansions used in the header file.
// The main criteria here is whether everything compiles.

// These are type names used internally to construct assert function names.
// They should not be macro-expanded, so the header should compile even with this wonky definition.
#define uint ,,,
#define dbl ,,,
#define ulong ,,,
#define size ,,,
#define ptr ,,,
#define str ,,,

#include "tst_utils.h"

// See if suite and test names do macro-expand
#define suite_name(x) suite ## x
#define test_name(x) test ## x

tst_begin_test(test_name(0), void)
{
    tst_assert_eq_uint(0, 0);
    tst_assert_gt_dbl(5, 0);
    tst_assert_eq_str("", "");
    tst_assert_eq_size(0, 0);
    tst_assert_eq_ptr(NULL, NULL);
    tst_assert_eq_ulong(0, 0);
} tst_end_test

void macro_expansion_tests(void)
{
    tst_begin_suite(suite_name(0))
    {
        tst_test(test_name(0),);
    } tst_end_suite
}
