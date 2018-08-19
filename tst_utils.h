#pragma once

#include <stdio.h>
#include <string.h>

// Declares global state variables
extern unsigned _tst_stat_passed = 0;
extern unsigned _tst_stat_failed = 0;
extern const unsigned _tst_indent_level = 0;

// Symbols
#define _tst_checkmark "\u2713"
#define _tst_crossmark "\u2717"
#define _tst_checkmark_line _tst_checkmark _tst_checkmark _tst_checkmark _tst_checkmark
#define _tst_crossmark_line _tst_crossmark _tst_crossmark _tst_crossmark _tst_crossmark

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
    void _tst_suite_name(name) (const unsigned _tst_indent_level)

// Declares a test suite with a tst_teardown label that the code will jump to on assert failure
// Allows cleanup code to run when an assert causes an exit
#define tst_decl_suite_teardown(name, ...)\
tst_suite_header(name)\
{\
    __VA_ARGS__\
    return;\
_tst_test_failed:\
    goto tst_teardown;\
    (void)_tst_indent_level;\
}

// Declares test suite without tst_teardown label, so failed asserts cause the code to just exit
#define tst_decl_suite(name, ...) tst_decl_suite_teardown(name, __VA_ARGS__ tst_teardown:)

#define tst_suite(name) do {\
    _tst_print_line("Suite %s:\n", #name);\
    _tst_suite_name(name)(_tst_indent_level + 1);\
} while(0)

/************************************ Test declaration macros **********************************/

#define tst_test_header(name, params)\
    static int _tst_test_name(name) params

// Declares test case with a tst_teardown label to handle assert failures
#define tst_decl_test_teardown(name, params, ...)\
tst_test_header(name, params)\
{\
    int _result = 1;\
    __VA_ARGS__\
    return _result;\
_tst_test_failed:\
    _result = 0;\
    goto tst_teardown;\
}

// Declares test case without tst_teardown label
#define tst_decl_test(name, params, ...) tst_decl_test_teardown(name, params, __VA_ARGS__ tst_teardown:)

// Runs a test case with a custom message to print with the result
#define tst_test_msg(name, msg, ...) do {\
    if (!_tst_test_name(name)(__VA_ARGS__)) {\
        _tst_print_line(\
            _tst_crossmark"Test %s with args=(%s) failed at %s:%d!\n",\
            msg, #__VA_ARGS__, __FILE__, __LINE__);\
        _tst_stat_failed++;\
    } else {\
        _tst_print_line(\
            _tst_checkmark"Test %s passed at %s:%d!\n", msg, __FILE__, __LINE__);\
        _tst_stat_passed++;\
    }\
} while(0)

// Like the above, but uses the name of the test in place of the custom message
#define tst_test(name, ...) tst_test_msg(name, #name, __VA_ARGS__)

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

// On assert failure, jump to end of test/suite
#define _tst_assert_base(assert_name, expr, expected) do {\
    int _res = assert_name(expr, expected, __FILE__, __LINE__, #expr);\
    if (!_res) goto _tst_test_failed;\
}

#define tst_assert_eq_int(expr, expected) _tst_assert_base(_tst_assert_eq_int, expr, expected)
#define tst_assert_ne_int(expr, expected) _tst_assert_base(_tst_assert_ne_int, expr, expected)
#define tst_assert_gt_int(expr, expected) _tst_assert_base(_tst_assert_gt_int, expr, expected)
#define tst_assert_lt_int(expr, expected) _tst_assert_base(_tst_assert_lt_int, expr, expected)
#define tst_assert_ge_int(expr, expected) _tst_assert_base(_tst_assert_ge_int, expr, expected)
#define tst_assert_lt_int(expr, expected) _tst_assert_base(_tst_assert_lt_int, expr, expected)

#define tst_assert_eq_uint(expr, expected) _tst_assert_base(_tst_assert_eq_uint, expr, expected)
#define tst_assert_ne_uint(expr, expected) _tst_assert_base(_tst_assert_ne_uint, expr, expected)
#define tst_assert_gt_uint(expr, expected) _tst_assert_base(_tst_assert_gt_uint, expr, expected)
#define tst_assert_lt_uint(expr, expected) _tst_assert_base(_tst_assert_lt_uint, expr, expected)
#define tst_assert_ge_uint(expr, expected) _tst_assert_base(_tst_assert_ge_uint, expr, expected)
#define tst_assert_lt_uint(expr, expected) _tst_assert_base(_tst_assert_lt_uint, expr, expected)

#define tst_assert_eq_ptr(expr, expected) _tst_assert_base(_tst_assert_eq_ptr, expr, expected)
#define tst_assert_ne_ptr(expr, expected) _tst_assert_base(_tst_assert_ne_ptr, expr, expected)
#define tst_assert_gt_ptr(expr, expected) _tst_assert_base(_tst_assert_gt_ptr, expr, expected)
#define tst_assert_lt_ptr(expr, expected) _tst_assert_base(_tst_assert_lt_ptr, expr, expected)
#define tst_assert_ge_ptr(expr, expected) _tst_assert_base(_tst_assert_ge_ptr, expr, expected)
#define tst_assert_lt_ptr(expr, expected) _tst_assert_base(_tst_assert_lt_ptr, expr, expected)

#define tst_assert_eq_char(expr, expected) _tst_assert_base(_tst_assert_eq_char, expr, expected)
#define tst_assert_ne_char(expr, expected) _tst_assert_base(_tst_assert_ne_char, expr, expected)
#define tst_assert_gt_char(expr, expected) _tst_assert_base(_tst_assert_gt_char, expr, expected)
#define tst_assert_lt_char(expr, expected) _tst_assert_base(_tst_assert_lt_char, expr, expected)
#define tst_assert_ge_char(expr, expected) _tst_assert_base(_tst_assert_ge_char, expr, expected)
#define tst_assert_lt_char(expr, expected) _tst_assert_base(_tst_assert_lt_char, expr, expected)

#define tst_assert_eq_size(expr, expected) _tst_assert_base(_tst_assert_eq_size, expr, expected)
#define tst_assert_ne_size(expr, expected) _tst_assert_base(_tst_assert_ne_size, expr, expected)
#define tst_assert_gt_size(expr, expected) _tst_assert_base(_tst_assert_gt_size, expr, expected)
#define tst_assert_lt_size(expr, expected) _tst_assert_base(_tst_assert_lt_size, expr, expected)
#define tst_assert_ge_size(expr, expected) _tst_assert_base(_tst_assert_ge_size, expr, expected)
#define tst_assert_lt_size(expr, expected) _tst_assert_base(_tst_assert_lt_size, expr, expected)

#define tst_assert_eq_long(expr, expected) _tst_assert_base(_tst_assert_eq_long, expr, expected)
#define tst_assert_ne_long(expr, expected) _tst_assert_base(_tst_assert_ne_long, expr, expected)
#define tst_assert_gt_long(expr, expected) _tst_assert_base(_tst_assert_gt_long, expr, expected)
#define tst_assert_lt_long(expr, expected) _tst_assert_base(_tst_assert_lt_long, expr, expected)
#define tst_assert_ge_long(expr, expected) _tst_assert_base(_tst_assert_ge_long, expr, expected)
#define tst_assert_lt_long(expr, expected) _tst_assert_base(_tst_assert_lt_long, expr, expected)

#define tst_assert_eq_ulong(expr, expected) _tst_assert_base(_tst_assert_eq_ulong, expr, expected)
#define tst_assert_ne_ulong(expr, expected) _tst_assert_base(_tst_assert_ne_ulong, expr, expected)
#define tst_assert_gt_ulong(expr, expected) _tst_assert_base(_tst_assert_gt_ulong, expr, expected)
#define tst_assert_lt_ulong(expr, expected) _tst_assert_base(_tst_assert_lt_ulong, expr, expected)
#define tst_assert_ge_ulong(expr, expected) _tst_assert_base(_tst_assert_ge_ulong, expr, expected)
#define tst_assert_lt_ulong(expr, expected) _tst_assert_base(_tst_assert_lt_ulong, expr, expected)

