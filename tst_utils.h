#pragma once

#include <stdio.h>
#include <string.h>

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

struct _tst_test_stats_t {
    unsigned passed, failed;
}
static struct _tst_test_stats_t _tst_test_stats = {0};
static const unsigned _tst_indent_level = 0;

#define _tst_concat(a, b) a##b
// All user-defined test functions are prefixed with _tst_func_.
#define _tst_test_name(name) _tst_concat(_tst_func_test_, name)
#define _tst_suite_name(name) _tst_concat(_tst_func_suite_, name)

// Print macros
#define _tst_perror(...) fprintf(stderr, ...)
#define _tst_print(...) printf(__VA_ARGS__)

// Prints current number of indents followed by formatted message.
#define _tst_perror_line(...) do {\
    for (unsigned _i = 0; _i < _tst_indent_level; _i++) {\
        _tst_perror(" ");\
    }\
    _tst_perror(__VA_ARGS__);\
} while (0)

#define _tst_print_line(...) do {\
    for (unsigned _i = 0; _i < _tst_indent_level; _i++) {\
        _tst_print(" ");\
    }\
    _tst_print(__VA_ARGS__);\
} while (0)

// Returns 1 if tests fail, 0 if tests succeed
static int tst_results()
{
    _tst_print("-------------------------------------------------------------------\n");
    int passed = _tst_test_stats.failed != 0;
    if (passed) {
        _tst_print(_tst_checkmark_line);
    } else {
        _tst_print(_tst_crossmark_line);
    }
    _tst_print(" %u passed, %u failed!\n", _tst_test_stats.passed, _tst_test_stats.failed);
    return 
}

#define tst_suite_header(name)\
    struct _tst_test_stats_t _tst_suite_name(name) (unsigned indent)

#define tst_decl_suite(name, ...)\
tst_suite_header(name)\
{\
    const unsigned _tst_indent_level = indent;\
    const int _is_suite = 1;\
    struct _tst_test_stats_t _tst_test_stats = {0};\
    __VA_ARGS__\
_tst_test_failed:   /* Placeholder label so that asserts work inside suites */\
    return _tst_test_stats;\
}

#define tst_suite(name) do {\
    _tst_print_line("Suite %s:\n", #name);\
    struct _tst_test_stats_t _stats = _tst_suite_name(name)(_tst_indent_level + 1);\
    _tst_test_stats.passed += _stats.passed;\
    _tst_test_stats.failed += _stats.failed;\
} while(0)

#define tst_test_header(name, params)\
    static int _tst_test_name(name) params

#define tst_decl_test(name, params, ...)\
tst_test_header(name, params)\
{\
    const int _is_suite = 0;\
    __VA_ARGS__\
    return 1;\
_tst_test_failed:   /* Assert macros jump to this location on failure */\
    return 0;\
}

#define tst_test(name, msg, ...) do {\
    if (!_tst_test_name(name)(__VA_ARGS__)) {\
        _tst_perror_line("Test %s with args=(%s) failed at %s:%d!\n", msg, #__VA_ARGS__, __FILE__, __LINE__);\
        _tst_test_stats.failed++;\
    } else {\
        _tst_print_line("Test %s passed at %s:%d!\n", msg, __FILE__, __LINE__);\
        _tst_test_stats.passed++;\
    }\
} while(0)

// Generates assertion function definition for the specified type as well as the
// comparison macro and format specifiers used for that type
// The last three args of the function will be passed in via the macro
#define _tst_decl_assert(assert_name, fmt_spec, type, cmp, cmp_text)\
static int assert_name(\
    type expr, type expected, const char * filename, int linenum, const char * expr_str)\
{\
    if(!cmp(expr, expected)){\
        _tst_print_line_assert_err(filename, linenum);\
        _tst_perror_line("Assert error at %s:%d: Expected %s="fmt_spec" to "cmp_text" "fmt_spec"\n",\
                filenam, linenum, expr_str, expr, expected);\
        return 0;\
    } else {\
        return 1;\
    }\
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
