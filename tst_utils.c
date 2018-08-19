#include <string.h>
#include "tst_utils.h"

unsigned _tst_stat_passed = 0;
unsigned _tst_stat_failed = 0;
const unsigned _tst_indent_level = 0;

// Returns 1 if tests fail, 0 if tests succeed. Used to report test results
int tst_results(void)
{
    _tst_print("-------------------------------------------------------------------\n");
    int passed = _tst_test_stats.failed != 0;
    if (passed) {
        _tst_print(_tst_checkmark_line);
    } else {
        _tst_print(_tst_crossmark_line);
    }
    _tst_print(" %u passed, %u failed!\n", _tst_test_stats.passed, _tst_test_stats.failed);
    return passed;
}

/************************************ Assert definitions **********************************/

// Generates assertion function definition for the specified type as well as the
// comparison macro and format specifiers used for that type
#define _tst_decl_assert(assert_name, fmt_spec, type, cmp, cmp_text)\
_tst_assert_header(assert_name, type)\
{\
    if(!cmp(expr, expected)){\
        _tst_perror_line("Assert error at %s:%d: Expected %s="fmt_spec" to "cmp_text" "fmt_spec"\n",\
                filename, linenum, expr_str, expr, expected);\
        return 0;\
    } else {\
        return 1;\
    }\
}

// Declares the eq and ne assertions for the specified type.
// The cmp macro should test for equality.
#define _tst_decl_equality_asserts_for_type(type_name, fmt_spec, type, cmp)\
    _tst_decl_assert(_tst_concat(_tst_assert_eq_, type_name), fmt_spec, type, cmp, "equal")\
    _tst_decl_assert(_tst_concat(_tst_assert_ne_, type_name), fmt_spec, type, !cmp, "not equal")

// Declares the less/greater than assertions for specified type. Only available for numerical types.
// The cmp_gt and cmp_lt macros should test for greater than and less than.
#define _tst_decl_comparison_asserts_for_type(type_name, fmt_spec, type, cmp_gt, cmp_lt)\
    _tst_decl_assert(\
        _tst_concat(_tst_assert_gt_, type_name), fmt_spec, type, cmp_gt, "greater than")\
    _tst_decl_assert(\
        _tst_concat(_tst_assert_ge_, type_name), fmt_spec, type, !cmp_lt, "greater than or equal")\
    _tst_decl_assert(\
        _tst_concat(_tst_assert_lt_, type_name), fmt_spec, type, cmp_lt, "less than")\
    _tst_decl_assert(\
        _tst_concat(_tst_assert_le_, type_name), fmt_spec, type, !cmp_gt, "less than or equal")

// Declares all 6 assertions for specified type. Only available for numerical types
#define _tst_decl_all_asserts_for_type(type_name, fmt_spec, type, cmp, cmp_gt, cmp_lt)\
    _tst_decl_equality_asserts_for_type(type_name, fmt_spec, type, cmp)\
    _tst_decl_comparison_asserts_for_type(type_name, fmt_spec, type, cmp_gt, cmp_lt)

// These comparison macros work for all numerical types, except for _eq, which doesn't work with floats
#define _tst_int_cmp_eq(a, b) (a == b)
#define _tst_int_cmp_gt(a, b) (a > b)
#define _tst_int_cmp_lt(a, b) (a < b)

_tst_decl_all_asserts_for_type(int, "%d", int, _tst_int_cmp_eq, _tst_int_cmp_gt, _tst_int_cmp_lt)
_tst_decl_all_asserts_for_type(uint, "%u", unsigned, _tst_int_cmp_eq, _tst_int_cmp_gt, _tst_int_cmp_lt)

_tst_decl_all_asserts_for_type(
    ptr, "%p", const void *, _tst_int_cmp_eq, _tst_int_cmp_gt, _tst_int_cmp_lt)

_tst_decl_all_asserts_for_type(char, "'%c'", char, _tst_int_cmp_eq, _tst_int_cmp_gt, _tst_int_cmp_lt)
_tst_decl_all_asserts_for_type(size, "%zu", size_t, _tst_int_cmp_eq, _tst_int_cmp_gt, _tst_int_cmp_lt)

// These "long" asserts are for long long types
_tst_decl_all_asserts_for_type(
    long, "%lld", long long int, _tst_int_cmp_eq, _tst_int_cmp_gt, _tst_int_cmp_lt)
_tst_decl_all_asserts_for_type(
    ulong, "%llu", unsigned long long int, _tst_int_cmp_eq, _tst_int_cmp_gt, _tst_int_cmp_lt)

// TODO double equality asserts, which are nontrivial
_tst_decl_comparison_asserts_for_type(dbl, "%f", double, _tst_int_cmp_gt, _tst_int_cmp_lt)

// String comparisons using strcmp
#define _tst_str_cmp_eq(a, b) (strcmp(a, b) == 0)
#define _tst_str_cmp_gt(a, b) (strcmp(a, b) > 0)
#define _tst_str_cmp_lt(a, b) (strcmp(a, b) < 0)

_tst_decl_all_asserts_for_type(
    str, "\"%s\"", const char *, _tst_str_cmp_eq, _tst_str_cmp_gt, _tst_str_cmp_lt)

