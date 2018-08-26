#include <string.h>
#include "tst_utils.h"

struct _tst_Stats _tst_stats = {0};
unsigned _tst_indent_level = 0;

// Returns 1 if tests fail, 0 if tests succeed. Used to report test results
int tst_results(void)
{
    _tst_print("-------------------------------------------------------------------\n");
    // Fails and xpasses will fail the suite
    int passed = _tst_stats.failed == 0 && _tst_stats.xpassed == 0;
    const char * symbol =
        passed ? _tst_green(_tst_checkmark_line) : _tst_red(_tst_crossmark_line);
    _tst_print(
        "%s %u passed, %u failed, %u xfailed, %u xpassed, %u ignored.\n",
        symbol, _tst_stats.passed, _tst_stats.failed,
        _tst_stats.xfailed, _tst_stats.xpassed, _tst_stats.ignored);
    // Return 0 if everything is going well
    return !passed;
}

/************************************ Assert definition macros **********************************/

#define _tst_print_assert_err(filename, linenum)\
    _tst_perror_line(_tst_red("") "Assert error at %s:%d: ", filename, linenum)

// Generates assertion function definition for the specified type as well as the
// comparison macro and format specifiers used for that type
#define _tst_def_assert(assert_name, fmt_spec, type, cmp, cmp_text)\
_tst_assert_header(assert_name, type)\
{\
    if(!cmp(expr, expected)){\
        _tst_print_assert_err(filename, linenum);\
        _tst_perror(\
            "Expected %s="fmt_spec" to "cmp_text" "fmt_spec"\n", expr_str, expr, expected);\
        return 0;\
    }\
    return 1;\
}

// Declares the eq and ne assertions for the specified type.
// The cmp macro should test for equality.
#define _tst_def_equality_asserts_for_type(type_name, fmt_spec, type, cmp)\
    _tst_def_assert(_tst_assert_eq_ ## type_name, fmt_spec, type, cmp, "equal")\
    _tst_def_assert(_tst_assert_ne_ ## type_name, fmt_spec, type, !cmp, "not equal")

// Declares the less/greater than assertions for specified type. Only available for numerical types.
// The cmp_gt and cmp_lt macros should test for greater than and less than.
#define _tst_def_comparison_asserts_for_type(type_name, fmt_spec, type, cmp_gt, cmp_lt)\
    _tst_def_assert(\
        _tst_assert_gt_ ## type_name, fmt_spec, type, cmp_gt, "be greater than")\
    _tst_def_assert(\
        _tst_assert_lt_ ## type_name, fmt_spec, type, cmp_lt, "be less than")\

// Declares the less/greater than or equal conditions for specified type
#define _tst_def_cmp_equality_assert_for_type(type_name, fmt_spec, type, cmp_ge, cmp_le)\
    _tst_def_assert(\
        _tst_assert_ge_ ## type_name, fmt_spec, type, cmp_ge, "be greater than or equal to")\
    _tst_def_assert(\
        _tst_assert_le_ ## type_name, fmt_spec, type, cmp_le, "be less than or equal to")

// Declares all 6 assertions for specified type. Only available for numerical types
#define _tst_def_all_asserts_for_type(type_name, fmt_spec, type, cmp_eq, cmp_gt, cmp_lt, cmp_ge, cmp_le)\
    _tst_def_equality_asserts_for_type(type_name, fmt_spec, type, cmp_eq)\
    _tst_def_comparison_asserts_for_type(type_name, fmt_spec, type, cmp_gt, cmp_lt)\
    _tst_def_cmp_equality_assert_for_type(type_name, fmt_spec, type, cmp_ge, cmp_le)

/************************************ Array Assert definition macros **********************************/

// Defines array comparison function for specific type
// Assume that if cmp_gt(a, b) and cmp_lt(a, b) are both untrue, then a must equal b.
// Populates idx with the index on which the comparison was done and result is same as with strlen.
#define _tst_def_array_cmp(type, type_name, cmp_gt, cmp_lt)\
static int _tst_array_cmp_ ## type_name(const type * arr1, const type * arr2, size_t len, size_t * idx)\
{\
    for (*idx = 0; (*idx) < len; (*idx)++) {\
        if (cmp_gt(arr1[*idx], arr2[*idx])) {\
            return 1;\
        } else if (cmp_lt(arr1[*idx], arr2[*idx])) {\
            return -1;\
        }\
    }\
    return 0;\
}

// Defines array assert.
// Arg cmp is an actual function that has strcmp semantics and returns index where comparison was completed
// Arg op is the comparison binop to use between cmp result and 0
#define _tst_def_assert_array(assert_name, fmt_spec, type, cmp, op, cmp_text, is_not_eq)\
_tst_assert_array_header(assert_name, type)\
{\
    size_t _idx = 0;\
    if(!(cmp(expr, expected, len, &_idx) op 0)) {\
        _tst_print_assert_err(filename, linenum);\
        /* Since array equality can't be pinned on a specific element, use different msg for ne asserts */\
        /* Also, if the index goes past the end of the array then it can't be used to print elements */\
        if (is_not_eq && _idx == len) {\
            _tst_perror("Expected %s to "cmp_text" %s\n", expr_str, expected_str);\
        } else {\
            _tst_perror(\
                "Expected %s[%zu]="fmt_spec" to "cmp_text" %s[%zu]="fmt_spec"\n",\
                expr_str, _idx, expr[_idx], expected_str, _idx, expected[_idx]);\
        }\
        return 0;\
    }\
    return 1;\
}

// Same as above but for array types
#define _tst_def_equality_asserts_for_array(type_name, fmt_spec, type, cmp)\
    _tst_def_assert_array(_tst_assert_eq_ ## type_name, fmt_spec, type, cmp, ==, "equal", 0)\
    _tst_def_assert_array(_tst_assert_ne_ ## type_name, fmt_spec, type, cmp, !=, "not equal", 1)

#define _tst_def_comparison_asserts_for_array(type_name, fmt_spec, type, cmp)\
    _tst_def_assert_array(\
        _tst_assert_gt_ ## type_name, fmt_spec, type, cmp, >, "be greater than", 1)\
    _tst_def_assert_array(\
        _tst_assert_lt_ ## type_name, fmt_spec, type, cmp, <, "be less than", 1)\

#define _tst_def_cmp_equality_assert_for_array(type_name, fmt_spec, type, cmp)\
    _tst_def_assert_array(\
        _tst_assert_ge_ ## type_name, fmt_spec, type, cmp, >=, "be greater than or equal to", 0)\
    _tst_def_assert_array(\
        _tst_assert_le_ ## type_name, fmt_spec, type, cmp, <=, "be less than or equal to", 0)\

#define _tst_def_all_asserts_for_array(type_name, fmt_spec, type, cmp)\
    _tst_def_equality_asserts_for_array(type_name, fmt_spec, type, cmp)\
    _tst_def_comparison_asserts_for_array(type_name, fmt_spec, type, cmp)\
    _tst_def_cmp_equality_assert_for_array(type_name, fmt_spec, type, cmp)

/****************************** Assert definitions and comparison macros ****************************/

// These comparison macros work for all numerical types, except for _eq, which doesn't work with floats
#define _tst_int_cmp_eq(a, b) (a == b)
#define _tst_int_cmp_gt(a, b) (a > b)
#define _tst_int_cmp_lt(a, b) (a < b)
#define _tst_int_cmp_ge(a, b) (a >= b)
#define _tst_int_cmp_le(a, b) (a <= b)

_tst_def_all_asserts_for_type(
    int, "%d", int,
    _tst_int_cmp_eq, _tst_int_cmp_gt, _tst_int_cmp_lt, _tst_int_cmp_ge, _tst_int_cmp_le)
_tst_def_all_asserts_for_type(
    uint, "%u", unsigned,
    _tst_int_cmp_eq, _tst_int_cmp_gt, _tst_int_cmp_lt, _tst_int_cmp_ge, _tst_int_cmp_le)

_tst_def_all_asserts_for_type(
    ptr, "%p", const void *,
    _tst_int_cmp_eq, _tst_int_cmp_gt, _tst_int_cmp_lt, _tst_int_cmp_ge, _tst_int_cmp_le)

_tst_def_all_asserts_for_type(
    char, "'%c'", char,
    _tst_int_cmp_eq, _tst_int_cmp_gt, _tst_int_cmp_lt, _tst_int_cmp_ge, _tst_int_cmp_le)
_tst_def_all_asserts_for_type(
    size, "%zu", size_t,
    _tst_int_cmp_eq, _tst_int_cmp_gt, _tst_int_cmp_lt, _tst_int_cmp_ge, _tst_int_cmp_le)

// These "long" asserts are for long long types
_tst_def_all_asserts_for_type(
    long, "%lld", long long int,
    _tst_int_cmp_eq, _tst_int_cmp_gt, _tst_int_cmp_lt, _tst_int_cmp_ge, _tst_int_cmp_le)
_tst_def_all_asserts_for_type(
    ulong, "%llu", unsigned long long int,
    _tst_int_cmp_eq, _tst_int_cmp_gt, _tst_int_cmp_lt, _tst_int_cmp_ge, _tst_int_cmp_le)

// TODO double equality asserts, which are nontrivial
_tst_def_comparison_asserts_for_type(dbl, "%f", double, _tst_int_cmp_gt, _tst_int_cmp_lt)

// String comparisons using strcmp
#define _tst_str_cmp_eq(a, b) (strcmp(a, b) == 0)
#define _tst_str_cmp_gt(a, b) (strcmp(a, b) > 0)
#define _tst_str_cmp_lt(a, b) (strcmp(a, b) < 0)
#define _tst_str_cmp_ge(a, b) (strcmp(a, b) >= 0)
#define _tst_str_cmp_le(a, b) (strcmp(a, b) <= 0)

_tst_def_all_asserts_for_type(
    str, "\"%s\"", const char *,
    _tst_str_cmp_eq, _tst_str_cmp_gt, _tst_str_cmp_lt, _tst_str_cmp_ge, _tst_str_cmp_le)


/*************************** Array Assert definitions and comparison *************************/

// Defines both the array comparison and assert definitions. Used if the asserts require a custom cmp
#define _tst_def_array_cmp_and_assert(assert_def_macro, type, fmt_spec, type_name, cmp_gt, cmp_lt)\
    _tst_def_array_cmp(type, type_name, cmp_gt, cmp_lt)\
    assert_def_macro(type_name ## _arr, fmt_spec, type, _tst_array_cmp_ ## type_name)

_tst_def_array_cmp_and_assert(
    _tst_def_all_asserts_for_array, int, "%d", int, _tst_int_cmp_gt, _tst_int_cmp_lt)

_tst_def_array_cmp_and_assert(
    _tst_def_all_asserts_for_array, unsigned, "%u", uint, _tst_int_cmp_gt, _tst_int_cmp_lt)

_tst_def_array_cmp_and_assert(
    _tst_def_all_asserts_for_array, void * const, "%p", ptr, _tst_int_cmp_gt, _tst_int_cmp_lt)

_tst_def_array_cmp_and_assert(
    _tst_def_all_asserts_for_array, char, "'%c'", char, _tst_int_cmp_gt, _tst_int_cmp_lt)

_tst_def_array_cmp_and_assert(
    _tst_def_all_asserts_for_array, long long int, "%lld", long, _tst_int_cmp_gt, _tst_int_cmp_lt)

_tst_def_array_cmp_and_assert(
    _tst_def_all_asserts_for_array, unsigned long long int, "%llu", ulong, _tst_int_cmp_gt, _tst_int_cmp_lt)

_tst_def_array_cmp_and_assert(
    _tst_def_all_asserts_for_array, size_t, "%zu", size, _tst_int_cmp_gt, _tst_int_cmp_lt)

_tst_def_array_cmp_and_assert(
    _tst_def_comparison_asserts_for_array, double, "%f", dbl, _tst_int_cmp_gt, _tst_int_cmp_lt)

// On surface this will cause strcmp to be called twice per comparison in the cmp function,
// so we'll trust the optimizer to bail us out on this one.
_tst_def_array_cmp_and_assert(
    _tst_def_all_asserts_for_array, char * const, "\"%s\"", str, _tst_str_cmp_gt, _tst_str_cmp_lt)
