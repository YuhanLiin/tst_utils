#pragma once

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

struct _tst_assertion_stats_t {
    unsigned passed;
    unsigned failed;
};

struct _tst_test_stats_t {
    unsigned passed;
    unsigned failed;
    unsigned skipped;
};

// Global test stat trackers used for final reporting
static struct _tst_assertion_stats_t _tst_assertion_stats = {0};
static struct _tst_test_stats_t _tst_test_stats = {0};
// The pointer is guaranteed to point to global data, since the struct variable may be shadowed
static struct _tst_assertion_stats_t * _g_tst_assertion_stats_ptr = &_tst_assertion_stats;

// Default setup/teardown function, which does nothing and always succeeds
int _tst_do_nothing( void ) { return 0; }

// Function ptrs for setup and teardown
// Takes no args, returns 0 for sucess, fail otherwise
typedef int ( *_tst_hook_func_t )( void );
static _tst_hook_func_t _tst_g_setup_ptr = &_tst_do_nothing;
static _tst_hook_func_t _tst_g_teardown_ptr = &_tst_do_nothing;

// Macros for setting/unsetting setup and teardown functions
#define tst_set_setup( func ) (_tst_g_setup_ptr = &func)
#define tst_set_teardown( func ) (_tst_g_teardown_ptr = &func)
#define tst_unset_setup() (_tst_g_setup_ptr = &_tst_do_nothing)
#define tst_unset_teardown() (_tst_g_teardown_ptr = &_tst_do_nothing)

// Symbols
#define _tst_checkmark "\u2713"
#define _tst_crossmark "\u2717"
#define _tst_circle "\u25CB"
#define _tst_checkmark_line _tst_checkmark _tst_checkmark _tst_checkmark _tst_checkmark
#define _tst_crossmark_line _tst_crossmark _tst_crossmark _tst_crossmark _tst_crossmark

// Generates name of test functions. Used to generate function definitions and calls
#define _tst_gen_name( name ) _tst_func_##name

// Returns whether the test case or the suite is passing based on asserts.
#define tst_passing() (_tst_assertion_stats.failed == 0)

// Convenient if wrappers for determining test/fail
#define tst_if_pass() if( tst_passing() )
#define tst_if_fail() if( !tst_passing() )

#define _tst_report_asserts()\
    printf(\
        "- Assertions: %u attempted, %u passed, %u failed\n",\
        _tst_assertion_stats.passed + _tst_assertion_stats.failed,\
        _tst_assertion_stats.passed, _tst_assertion_stats.failed\
    );\

// Only report tests if tests have actually been made and run
#define _tst_report_tests() do {\
    unsigned _tst_total_tests =\
        _tst_test_stats.passed + _tst_test_stats.failed + _tst_test_stats.skipped;\
    if( _tst_total_tests > 0 ) printf(\
        "- Test cases: %u attemped, %u passed, %u failed, %u skipped\n",\
        _tst_total_tests,\
        _tst_test_stats.passed, _tst_test_stats.failed, _tst_test_stats.skipped\
    );\
} while( 0 )

// Final reporting called from main to print all test results and return success code
#define tst_report_results() do {\
    printf( "\n" );\
    if( tst_passing() ){\
        printf( _tst_checkmark_line " Module %s PASSED! " _tst_checkmark_line "\n", __FILE__ );\
    } else {\
        printf( _tst_crossmark_line " Module %s FAILED! " _tst_crossmark_line "\n", __FILE__ );\
    }\
    _tst_report_tests();\
    _tst_report_asserts();\
    /* Since we're returning to shell, we return 0 if the tests are passing, 1 otherwise */\
    return !tst_passing();\
} while( 0 )

// Sync the assert stats from within a test case to the global assert stats.
// Should be updated for new assert stats. DON'T USE OUTSIDE TEST CASES
#define _tst_sync() do {\
    _g_tst_assertion_stats_ptr->passed += _tst_assertion_stats.passed;\
    _g_tst_assertion_stats_ptr->failed += _tst_assertion_stats.failed;\
} while( 0 )

// Calls teardown, checks for failures, then updates the test counter before returning.
// Called whenever we need to exit from the test
#define _tst_exit( test_stat_field ) do {\
    _tst_test_stats.test_stat_field += 1;\
    int _tst_teardown_ret = (*_tst_g_teardown_ptr)();\
    if( _tst_teardown_ret != 0 ){\
        printf(\
            _tst_crossmark " Warning: TEARDOWN FAILED with code %d, carrying on.\n",\
            _tst_teardown_ret\
        );\
    }\
    printf("\n");\
    return;\
} while( 0 )

// Initializes a new test function. Must be matched by an END_TEST.
// name =  unique identifier name of the test
#define tst_begin_test( name ) void _tst_gen_name( name )( void )\
{\
    static struct _tst_assertion_stats_t _tst_assertion_stats = {0};\
    const char * _tst_name = #name;\
    int _tst_setup_ret = (*_tst_g_setup_ptr)();\
    if( _tst_setup_ret != 0 ){\
        printf(\
            _tst_crossmark " Test case \"%s\" SETUP FAILED with code %d, ABORTING!\n",\
            _tst_name, _tst_setup_ret\
        );\
        _tst_exit( skipped );\
    }

// Version of tst_begin_test that skips the whole test case.
#define tst_begin_test_skip( name ) tst_begin_test( name )\
    printf( _tst_circle " Test case \"%s\" SKIPPED!\n", _tst_name );\
    _tst_exit( skipped );
    
// Prints result message depending on whether the test case passed or failed
// and reports assert stats for this test
#define tst_end_test()\
    _tst_sync();\
    if( tst_passing() ){\
        printf( _tst_checkmark " Test case \"%s\" PASSED!\n", _tst_name );\
        _tst_report_asserts();\
        _tst_exit( passed );\
    } else {\
        printf( _tst_crossmark " Test case \"%s\" FAILED!\n", _tst_name );\
        _tst_report_asserts();\
        _tst_exit( failed );\
    }\
}

// Aborts a test, which marks it as failed
#define tst_abort_test() do {\
    printf( _tst_crossmark " Test case \"%s\" ABORTED!\n", _tst_name );\
    _tst_report_asserts();\
    _tst_sync();\
    _tst_exit( failed );\
} while( 0 )

// Abort test when failing
 #define tst_abort_if_failing() tst_if_fail() tst_abort_test()

// Runs a test runner function of the specified name
#define tst_run_test( name ) _tst_gen_name( name )()

#define _tst_concat(a, b) a##b

#define _tst_perror(...) fprintf(stderr, __VA_ARGS__)

#define _tst_print_assert_err(filename, linenum)\
    _tst_perror("Assert error in %s:%d: ", filename, linenum)

// Generates assertion function definition for the specified type as well as the
// comparison macro and format specifiers used for that type
// The last three args of the function will be passed in via the macro
#define _tst_decl_assert(assert_name, fmt_spec, type, cmp, cmp_text)\
static int assert_name(\
    type expr, type expected, const char * filename, int linenum, const char * expr_str)\
{\
    if(!cmp(expr, expected)){\
        _tst_print_assert_err(filename, linenum);\
        _tst_perror(\
                "Expected %s="fmt_spec" to "cmp_text" "fmt_spec"\n",\
                expr_str, expr, expected);\
        return 0;\
    } else {\
        return 1;\
    }\
}

// Generates unforgiving assert definition for array types. Parameters still refer to scalar type
// The assertion fails if any element fails the comparison.
#define _tst_decl_arr_assert_eq(assert_name, fmt_spec, type, cmp, cmp_text)\
static int assert_name(\
    const type * expr, const type * expected, size_t len,\
    const char * filename, int linenum, const char * expr_str)\
{\
    for (size_t _i = 0; i < len; i++) {\
        if (!cmp(expr[_i], expected[_i])) {\
            _tst_print_assert_err(filename, linenum);\
            _tst_perror(\
                "Expected %s[%zu]="fmt_spec" to "cmp_text" "fmt_spec"\n",\
                expr_str, expr[_i], expected[_i]);\
            return 0;\
        }\
    }\
    return 1;\
}

// Generates forgiving assert definition for array types. Parameters still refer to scalar type
// The assertion fails if all elements fail the comparison.
#define _tst_decl_arr_assert_ne(assert_name, type, cmp, cmp_text)\
static int assert_name(\
    const type * expr, const type * expected, size_t len,\
    const char * filename, int linenum, const char * expr_str, const char * expected_str)\
{\
    for (size_t _i = 0; i < len; i++) {\
        if (cmp(expr[_i], expected[_i])) {\
            return 1;\
        }\
    }\
    _tst_print_assert_err(filename, linenum);\
    _tst_perror("Expected %s to "cmp_text" %s\n", expr_str, expected_str);\
    return 0;\
}

// Declares the eq and ne assertions for the specified type.
// The cmp macro should test for equality.
#define _tst_decl_equality_asserts_for_type(type_name, fmt_spec, type, cmp)\
    _tst_decl_assert(_tst_concat(_tst_assert_eq, type_name), fmt_spec, type, cmp, "equal")\
    _tst_decl_assert(_tst_concat(_tst_assert_ne, type_name), fmt_spec, type, !cmp, "not equal")

// Declares the less/greater than assertions for specified type. Only available for numerical types.
// The cmp_gt and cmp_lt macros should test for greater than and less than.
#define _tst_decl_comparison_asserts_for_type(type_name, fmt_spec, type, cmp_gt, cmp_lt)\
    _tst_decl_assert(\
        _tst_concat(_tst_assert_gt, type_name), fmt_spec, type, cmp_gt, "greater than")\
    _tst_decl_assert(\
        _tst_concat(_tst_assert_ge, type_name), fmt_spec, type, !cmp_lt, "greater than or equal")\
    _tst_decl_assert(\
        _tst_concat(_tst_assert_lt, type_name), fmt_spec, type, cmp_lt, "less than")\
    _tst_decl_assert(\
        _tst_concat(_tst_assert_le, type_name), fmt_spec, type, !cmp_gt, "less than or equal")

// Declares all 6 assertions for specified type. Only available for numerical types
#define _tst_decl_all_asserts_for_type(type_name, fmt_spec, type, cmp, cmp_gt, cmp_lt)\
    _tst_decl_equality_asserts_for_type(type_name, fmt_spec, type, cmp)\
    _tst_decl_comparison_asserts_for_type(type_name, fmt_spec, type, cmp_gt, cmp_lt)

#define _tst_decl_arr_asserts_for_type(type_name, type, cmp_eq)\
    _tst_decl_arr_assert_eq(_tst_concat(_tst_assert_eq_arr_, type_name), type, cmp_eq, "equal")\
    _tst_decl_arr_assert_ne(_tst_concat(_tst_assert_ne_arr_, type_name), type, !cmp_eq, "not equal")

// These comparison macros work for all numerical types, except for _eq, which doesn't work with floats
#define _tst_int_cmp_eq(a, b) (a == b)
#define _tst_int_cmp_gt(a, b) (a > b)
#define _tst_int_cmp_lt(a, b) (a < b)

_tst_decl_all_asserts_for_type(int, "%d", int, _tst_int_cmp_eq, _tst_int_cmp_gt, _tst_int_cmp_lt)
_tst_decl_arr_asserts_for_type(int, int, _tst_int_cmp_eq)

_tst_decl_all_asserts_for_type(uint, "%u", unsigned, _tst_int_cmp_eq, _tst_int_cmp_gt, _tst_int_cmp_lt)
_tst_decl_arr_asserts_for_type(uint, uint, _tst_int_cmp_eq)

_tst_decl_all_asserts_for_type(
    ptr, "%p", const void *, _tst_int_cmp_eq, _tst_int_cmp_gt, _tst_int_cmp_lt)
_tst_decl_arr_asserts_for_type(ptr, void *, _tst_int_cmp_eq)

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

// General array comparison macro for testing equality
#define _tst_cmp_arr_base( cmp, a1, a2, len, eq_var ) do {\
    eq_var = true;\
    for( size_t _i = 0; _i < len; _i++ ){\
        if( !cmp( a1[_i], a2[_i] ) ){\
            eq_var = false;\
            break;\
        }\
    }\
} while( 0 )

// Byte array asserts
#define _tst_cmp_arr_bytes( a1, a2, len, eq_var )\
    _tst_cmp_arr_base( _tst_int_cmp, a1, a2, len, eq_var );

#define _tst_cmp_arr_ne_bytes( a1, a2, len, eq_var ) do {\
    _tst_cmp_arr_base( _tst_int_cmp, a1, a2, len, eq_var );\
    eq_var = !eq_var;\
} while( 0 )

#define _tst_assert_bytes( expr, expected, len, cmp, cmp_text )\
    _tst_assert_array_base( expr, expected, len, "0x%02x", const uint8_t *, cmp, cmp_text )

#define tst_assert_eq_bytes( expr, expected, len )\
    _tst_assert_bytes( expr, expected, len, _tst_cmp_arr_bytes, "equal" );

#define tst_assert_ne_bytes( expr, expected, len )\
    _tst_assert_bytes( expr, expected, len, _tst_cmp_arr_ne_bytes "not equal" );
