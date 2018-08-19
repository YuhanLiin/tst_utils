#pragma once

#include <stdio.h>
#include <string.h>

// Symbols
#define _tst_checkmark "\u2713"
#define _tst_crossmark "\u2717"
#define _tst_checkmark_line _tst_checkmark _tst_checkmark _tst_checkmark _tst_checkmark
#define _tst_crossmark_line _tst_crossmark _tst_crossmark _tst_crossmark _tst_crossmark

struct _tst_test_stats_t {
    unsigned passed, failed;
};

#define _tst_concat(a, b) a##b
// All user-defined test functions are prefixed with _tst_func_.
#define _tst_test_name(name) _tst_concat(_tst_func_test_, name)
#define _tst_suite_name(name) _tst_concat(_tst_func_suite_, name)

// Print macros
#define _tst_perror(...) fprintf(stderr, __VA_ARGS__)
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

// Returns 1 if tests fail, 0 if tests succeed. Used to report test results
int tst_results(void);

/************************************ Suite declaration macros **********************************/

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

/************************************ Test declaration macros **********************************/

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

/************************************ Assert headers **********************************/

// Generates the signature of a assertion function based on its type
// The last three args of the function will be passed in via the macro
#define _tst_assert_header(assert_name, type)\
int assert_name(\
    type expr, type expected, const char * filename, int linenum, const char * expr_str)

// Header generation macros mirror the assert definition macros in the source file
#define _tst_equality_assert_headers_for_type(type_name, type)\
    _tst_assert_header(_tst_concat(_tst_assert_eq_, type_name), type);\
    _tst_assert_header(_tst_concat(_tst_assert_ne_, type_name), type);

#define _tst_comparison_assert_headers_for_type(type_name, type)\
    _tst_assert_header(_tst_concat(_tst_assert_gt_, type_name), type);\
    _tst_assert_header(_tst_concat(_tst_assert_ge_, type_name), type);\
    _tst_assert_header(_tst_concat(_tst_assert_lt_, type_name), type);\
    _tst_assert_header(_tst_concat(_tst_assert_le_, type_name), type);

#define _tst_all_assert_headers_for_type(type_name, type)\
    _tst_equality_assert_headers_for_type(type_name, type)\
    _tst_comparison_assert_headers_for_type(type_name, type)

// The actual headers
_tst_all_assert_headers_for_type(int, int)
_tst_all_assert_headers_for_type(uint, unsigned)
_tst_all_assert_headers_for_type(ptr, const void *)
_tst_all_assert_headers_for_type(char, char)
_tst_all_assert_headers_for_type(size, size_t)
_tst_all_assert_headers_for_type(long, long long int)
_tst_all_assert_headers_for_type(ulong, unsigned long long int)
_tst_comparison_assert_headers_for_type(dbl, double)
_tst_all_assert_headers_for_type(str, const char *)
    
/************************************ Assert macros **********************************/

// The behaviour of assertions differs when it's called from a suite or test case.
// In a suite, a failed assert functions like a failed test
// In a test case, a failed assert causes the code to jump to the end of the test.
#define _tst_assert_base(assert_name, expr, expected) do {\
    int _res = assert_name(expr, expected, __FILE__, __LINE__, #expr);\
    if (_is_suite) {\
        if (_res) _tst_test_stats.passed++;\
        else _tst_test_stats.failed++;\
    } else {\
        if (!_res) goto _tst_test_failed;\
    }\
}

#define tst_assert_eq_int(expr, expected) _tst_assert_base(_tst_assert_eq_int, expr, expected)
#define tst_assert_ne_int(expr, expected) _tst_assert_base(_tst_assert_ne_int, expr, expected)
#define tst_assert_gt_int(expr, expected) _tst_assert_base(_tst_assert_gt_int, expr, expected)
#define tst_assert_lt_int(expr, expected) _tst_assert_base(_tst_assert_lt_int, expr, expected)
#define tst_assert_ge_int(expr, expected) _tst_assert_base(_tst_assert_ge_int, expr, expected)
#define tst_assert_lt_int(expr, expected) _tst_assert_base(_tst_assert_lt_int, expr, expected)

