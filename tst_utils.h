#pragma once

#include <stdio.h>
#include <string.h>

// Declares global state struct and variables
struct _tst_Stats {
    unsigned passed;
    unsigned failed;
    unsigned xpassed;
    unsigned xfailed;
    unsigned ignored;
};

extern struct _tst_Stats _tst_stats;
extern unsigned _tst_indent_level;

// Symbols
#define _tst_checkmark "\u2713"
#define _tst_crossmark "\u2717"
#define _tst_checkmark_line _tst_checkmark _tst_checkmark _tst_checkmark _tst_checkmark
#define _tst_crossmark_line _tst_crossmark _tst_crossmark _tst_crossmark _tst_crossmark

// Turn a string literal into a colour then reset the colour afterwards
#define _tst_red(txt) "\x1b[31m" txt "\x1b[0m"
#define _tst_green(txt) "\x1b[32m" txt "\x1b[0m"
#define _tst_blue(txt) "\x1B[34m" txt "\x1b[0m"
#define _tst_yellow(txt) "\x1B[33m" txt "\x1b[0m"

// Use these when we want the arguments to be macro-expanded
#define _tst_concat(a, b) a##b
#define _tst_stringize(a) #a

// All user-defined test functions are prefixed with _tst_func_.
#define _tst_test_name(name) _tst_concat(_tst_func_test_, name)

// Print macros
#define _tst_perror(...) fprintf(stderr, __VA_ARGS__)
#define _tst_print(...) printf(__VA_ARGS__)

// Prints current number of indents followed by formatted message.
#define _tst_perror_line(...) do {\
    for (unsigned _i = 0; _i < _tst_indent_level; _i++) {\
        _tst_perror("    ");\
    }\
    _tst_perror(__VA_ARGS__);\
} while (0)

#define _tst_print_line(...) do {\
    for (unsigned _i = 0; _i < _tst_indent_level; _i++) {\
        _tst_print("    ");\
    }\
    _tst_print(__VA_ARGS__);\
} while (0)

// Returns 1 if tests fail, 0 if tests succeed. Used to report test results
int tst_results(void);

/************************************ Suite macros **********************************/

// Suites simply cause the wrapped code to print messages at a higher indent level.
// The name should still be an identifier for possible future features
#define tst_begin_suite(name)\
{\
    _tst_print_line("Suite %s:\n", _tst_stringize(name));\
    _tst_indent_level++;\

#define tst_end_suite\
    _tst_indent_level--;\
}

/************************************ Test declaration macros **********************************/

enum _tst_Result { _tst_PASS, _tst_FAIL, _tst_XFAIL, _tst_XPASS, _tst_IGNORE };

#define tst_test_header(name, ...)\
    static enum _tst_Result _tst_test_name(name)(__VA_ARGS__)

// Specifies the _tst_Result returned by the test on pass and on failure
#define _tst_begin_test_base(name, pass_result, fail_result, ...)\
tst_test_header(name, __VA_ARGS__)\
{\
    enum _tst_Result _result = pass_result;\
    goto _tst_test_begin;\
    goto _tst_test_failed;  /* Suppress unused label warning */\
_tst_test_failed:\
    _result = fail_result;\
    goto tst_teardown;  /* This label will be provided by user code or end_test macro */\
_tst_test_begin:

// Defines basic test that returns back PASS or FAIL
#define tst_begin_test(name, ...) _tst_begin_test_base(name, _tst_PASS, _tst_FAIL, __VA_ARGS__)

// Defines test that will be expected to fail
#define tst_begin_test_xfail(name, ...) _tst_begin_test_base(name, _tst_XPASS, _tst_XFAIL, __VA_ARGS__)

// Defines test whose results will be ignored
#define tst_begin_test_ignore(name, ...)\
    _tst_begin_test_base(name, _tst_IGNORE, _tst_IGNORE, __VA_ARGS__)

// Ends a test case. Expect a tst_teardown label in the above code to preceed cleanup code
#define tst_end_test_teardown\
    return _result;\
}

// Ends test case without expecting tst_teardown label 
#define tst_end_test tst_teardown: tst_end_test_teardown

/************************************ Test runner macros **********************************/

// Runs test case and prints message according to the result.
// The ignore and xfail flags modify the result before the message is printed.
#define _tst_test_base(name, msg, ignore, xfail, ...) do {\
    enum _tst_Result _result = _tst_test_name(name)(__VA_ARGS__);\
    if (xfail) {\
        if (_result == _tst_PASS) { _result = _tst_XPASS; }\
        else if (_result == _tst_FAIL) { _result = _tst_XFAIL; }\
    }\
    else if (ignore) { _result = _tst_IGNORE; }\
\
    switch (_result) {\
        case _tst_PASS:\
            _tst_print_line(_tst_green(_tst_checkmark" Test \"%s\" passed\n"), (msg));\
            _tst_stats.passed++; break;\
        case _tst_FAIL:\
            _tst_print_line(\
                _tst_red(_tst_crossmark" Test \"%s\" with args=(%s) failed at %s:%d!\n"),\
                    (msg), #__VA_ARGS__, __FILE__, __LINE__);\
            _tst_stats.failed++; break;\
        case _tst_XPASS:\
            _tst_print_line(\
                _tst_red(_tst_crossmark" Test \"%s\" with args=(%s) unexpectedly passed at %s:%d!\n"),\
                msg, #__VA_ARGS__, __FILE__, __LINE__);\
            _tst_stats.xpassed++; break;\
        case _tst_XFAIL:\
            _tst_print_line(\
                _tst_blue(_tst_checkmark" Test \"%s\" failed as expected at %s:%d!\n"),\
                msg, __FILE__, __LINE__);\
            _tst_stats.xfailed++; break;\
        case _tst_IGNORE:\
            _tst_print_line(\
                _tst_yellow(_tst_checkmark" Test \"%s\" results ignored at %s:%d!\n"),\
                msg, __FILE__, __LINE__);\
            _tst_stats.ignored++; break;\
        default: _tst_perror_line("WTF unrecognized test result\n");\
    }\
} while (0)\

// Run test case with custom message to print with the results.
#define tst_test_msg(name, msg, ...) _tst_test_base(name, msg, 0, 0, __VA_ARGS__)
// Expect the test to fail, so passing in PASS and FAIL are treated like XPASS and XFAIL
#define tst_test_msg_xfail(name, msg, ...) _tst_test_base(name, msg, 0, 1, __VA_ARGS__)
// Run test but ignore results
#define tst_test_msg_ignore(name, msg, ...) _tst_test_base(name, msg, 1, 0, __VA_ARGS__)

// Like the above, but uses the name of the test in place of the custom message
#define tst_test(name, ...) tst_test_msg(name, _tst_stringize(name), __VA_ARGS__)
#define tst_test_xfail(name, ...) tst_test_msg_xfail(name, _tst_stringize(name), __VA_ARGS__)
#define tst_test_ignore(name, ...) tst_test_msg_ignore(name, _tst_stringize(name), __VA_ARGS__)

/************************************ Assert headers **********************************/

// Generates the signature of a assertion function based on its type
// The last four args of the function will be passed in via the macro
#define _tst_assert_header(assert_name, type)\
    int assert_name(type expr, type expected, const char * filename, int linenum, const char * expr_str) 

// Header generation macros mirror the assert definition macros in the source file.
// Use token paste directly so the type_names don't get macro expanded.
// Specifies header_macro so we can generate both scalar and array headers
#define _tst_equality_assert_headers_for_type(header_macro, type_name, type)\
    header_macro(_tst_assert_eq_ ## type_name, type);\
    header_macro(_tst_assert_ne_ ## type_name, type);

#define _tst_comparison_assert_headers_for_type(header_macro, type_name, type)\
    header_macro(_tst_assert_gt_ ## type_name, type);\
    header_macro(_tst_assert_lt_ ## type_name, type);\

#define _tst_cmp_equality_assert_headers_for_type(header_macro, type_name, type)\
    header_macro(_tst_assert_ge_ ## type_name, type);\
    header_macro(_tst_assert_le_ ## type_name, type);

// Define equality and comparison asserts for a specific type.
// To prevent the type_name from being macro expanded, paste an empty argument to it just
// in case the type_name is a macro. As such, the "empty" argument needs to be really empty.
#define _tst_all_assert_headers_for_type(header_macro, type_name, type, empty)\
    _tst_equality_assert_headers_for_type(header_macro, type_name ## empty, type)\
    _tst_comparison_assert_headers_for_type(header_macro, type_name ## empty, type)\
    _tst_cmp_equality_assert_headers_for_type(header_macro, type_name ## empty, type)

// The actual headers
_tst_all_assert_headers_for_type(_tst_assert_header, int, int,)
_tst_all_assert_headers_for_type(_tst_assert_header, uint, unsigned,)
_tst_all_assert_headers_for_type(_tst_assert_header, ptr, const void *,)
_tst_all_assert_headers_for_type(_tst_assert_header, char, char,)
_tst_all_assert_headers_for_type(_tst_assert_header, size, size_t,)
_tst_all_assert_headers_for_type(_tst_assert_header, long, long long int,)
_tst_all_assert_headers_for_type(_tst_assert_header, ulong, unsigned long long int,)
_tst_all_assert_headers_for_type(_tst_assert_header, str, const char *,)
_tst_comparison_assert_headers_for_type(_tst_assert_header, dbl, double)
    
/************************************ Array assert headers **********************************/

// Signature of array assertion function
#define _tst_assert_array_header(assert_name, type)\
    int assert_name(\
        const type * expr, const type * expected, size_t len,\
        const char * filename, int linenum, const char * expr_str, const char * expected_str)

_tst_all_assert_headers_for_type(_tst_assert_array_header, int_arr, int,)
_tst_all_assert_headers_for_type(_tst_assert_array_header, uint_arr, unsigned,)
_tst_all_assert_headers_for_type(_tst_assert_array_header, ptr_arr, void * const,)
_tst_all_assert_headers_for_type(_tst_assert_array_header, char_arr, char,)
_tst_all_assert_headers_for_type(_tst_assert_array_header, size_arr, size_t,)
_tst_all_assert_headers_for_type(_tst_assert_array_header, long_arr, long long int,)
_tst_all_assert_headers_for_type(_tst_assert_array_header, ulong_arr, unsigned long long int,)
_tst_all_assert_headers_for_type(_tst_assert_array_header, str_arr, char * const,)
_tst_comparison_assert_headers_for_type(_tst_assert_array_header, dbl_arr, double)

/************************************ Assert macros **********************************/

// Aborts the test and fails it.
#define tst_abort() goto _tst_test_failed

// On assert failure, jump to end of test
#define _tst_assert_base(assert_name, expr, expected, expr_str) do {\
    int _res = assert_name((expr), (expected), __FILE__, __LINE__, expr_str);\
    if (!_res) tst_abort();\
} while (0)

// All assert macros
#define tst_assert_eq_int(expr, expected) _tst_assert_base(_tst_assert_eq_int, expr, expected, #expr)
#define tst_assert_ne_int(expr, expected) _tst_assert_base(_tst_assert_ne_int, expr, expected, #expr)
#define tst_assert_gt_int(expr, expected) _tst_assert_base(_tst_assert_gt_int, expr, expected, #expr)
#define tst_assert_lt_int(expr, expected) _tst_assert_base(_tst_assert_lt_int, expr, expected, #expr)
#define tst_assert_ge_int(expr, expected) _tst_assert_base(_tst_assert_ge_int, expr, expected, #expr)
#define tst_assert_le_int(expr, expected) _tst_assert_base(_tst_assert_le_int, expr, expected, #expr)

#define tst_assert_eq_uint(expr, expected) _tst_assert_base(_tst_assert_eq_uint, expr, expected, #expr)
#define tst_assert_ne_uint(expr, expected) _tst_assert_base(_tst_assert_ne_uint, expr, expected, #expr)
#define tst_assert_gt_uint(expr, expected) _tst_assert_base(_tst_assert_gt_uint, expr, expected, #expr)
#define tst_assert_lt_uint(expr, expected) _tst_assert_base(_tst_assert_lt_uint, expr, expected, #expr)
#define tst_assert_ge_uint(expr, expected) _tst_assert_base(_tst_assert_ge_uint, expr, expected, #expr)
#define tst_assert_le_uint(expr, expected) _tst_assert_base(_tst_assert_le_uint, expr, expected, #expr)

#define tst_assert_eq_ptr(expr, expected) _tst_assert_base(_tst_assert_eq_ptr, expr, expected, #expr)
#define tst_assert_ne_ptr(expr, expected) _tst_assert_base(_tst_assert_ne_ptr, expr, expected, #expr)
#define tst_assert_gt_ptr(expr, expected) _tst_assert_base(_tst_assert_gt_ptr, expr, expected, #expr)
#define tst_assert_lt_ptr(expr, expected) _tst_assert_base(_tst_assert_lt_ptr, expr, expected, #expr)
#define tst_assert_ge_ptr(expr, expected) _tst_assert_base(_tst_assert_ge_ptr, expr, expected, #expr)
#define tst_assert_le_ptr(expr, expected) _tst_assert_base(_tst_assert_le_ptr, expr, expected, #expr)

#define tst_assert_eq_char(expr, expected) _tst_assert_base(_tst_assert_eq_char, expr, expected, #expr)
#define tst_assert_ne_char(expr, expected) _tst_assert_base(_tst_assert_ne_char, expr, expected, #expr)
#define tst_assert_gt_char(expr, expected) _tst_assert_base(_tst_assert_gt_char, expr, expected, #expr)
#define tst_assert_lt_char(expr, expected) _tst_assert_base(_tst_assert_lt_char, expr, expected, #expr)
#define tst_assert_ge_char(expr, expected) _tst_assert_base(_tst_assert_ge_char, expr, expected, #expr)
#define tst_assert_le_char(expr, expected) _tst_assert_base(_tst_assert_le_char, expr, expected, #expr)

#define tst_assert_eq_size(expr, expected) _tst_assert_base(_tst_assert_eq_size, expr, expected, #expr)
#define tst_assert_ne_size(expr, expected) _tst_assert_base(_tst_assert_ne_size, expr, expected, #expr)
#define tst_assert_gt_size(expr, expected) _tst_assert_base(_tst_assert_gt_size, expr, expected, #expr)
#define tst_assert_lt_size(expr, expected) _tst_assert_base(_tst_assert_lt_size, expr, expected, #expr)
#define tst_assert_ge_size(expr, expected) _tst_assert_base(_tst_assert_ge_size, expr, expected, #expr)
#define tst_assert_le_size(expr, expected) _tst_assert_base(_tst_assert_le_size, expr, expected, #expr)

#define tst_assert_eq_long(expr, expected) _tst_assert_base(_tst_assert_eq_long, expr, expected, #expr)
#define tst_assert_ne_long(expr, expected) _tst_assert_base(_tst_assert_ne_long, expr, expected, #expr)
#define tst_assert_gt_long(expr, expected) _tst_assert_base(_tst_assert_gt_long, expr, expected, #expr)
#define tst_assert_lt_long(expr, expected) _tst_assert_base(_tst_assert_lt_long, expr, expected, #expr)
#define tst_assert_ge_long(expr, expected) _tst_assert_base(_tst_assert_ge_long, expr, expected, #expr)
#define tst_assert_le_long(expr, expected) _tst_assert_base(_tst_assert_le_long, expr, expected, #expr)

#define tst_assert_eq_ulong(expr, expected) _tst_assert_base(_tst_assert_eq_ulong, expr, expected, #expr)
#define tst_assert_ne_ulong(expr, expected) _tst_assert_base(_tst_assert_ne_ulong, expr, expected, #expr)
#define tst_assert_gt_ulong(expr, expected) _tst_assert_base(_tst_assert_gt_ulong, expr, expected, #expr)
#define tst_assert_lt_ulong(expr, expected) _tst_assert_base(_tst_assert_lt_ulong, expr, expected, #expr)
#define tst_assert_ge_ulong(expr, expected) _tst_assert_base(_tst_assert_ge_ulong, expr, expected, #expr)
#define tst_assert_le_ulong(expr, expected) _tst_assert_base(_tst_assert_le_ulong, expr, expected, #expr)

#define tst_assert_gt_dbl(expr, expected) _tst_assert_base(_tst_assert_gt_dbl, expr, expected, #expr)
#define tst_assert_lt_dbl(expr, expected) _tst_assert_base(_tst_assert_lt_dbl, expr, expected, #expr)

#define tst_assert_eq_str(expr, expected) _tst_assert_base(_tst_assert_eq_str, expr, expected, #expr)
#define tst_assert_ne_str(expr, expected) _tst_assert_base(_tst_assert_ne_str, expr, expected, #expr)
#define tst_assert_gt_str(expr, expected) _tst_assert_base(_tst_assert_gt_str, expr, expected, #expr)
#define tst_assert_lt_str(expr, expected) _tst_assert_base(_tst_assert_lt_str, expr, expected, #expr)
#define tst_assert_ge_str(expr, expected) _tst_assert_base(_tst_assert_ge_str, expr, expected, #expr)
#define tst_assert_le_str(expr, expected) _tst_assert_base(_tst_assert_le_str, expr, expected, #expr)

/************************************ Assert macros **********************************/

#define _tst_assert_array_base(assert_name, expr, expected, len, expr_str, expected_str) do {\
    int _res = assert_name((expr), (expected), (len), __FILE__, __LINE__, expr_str, expected_str);\
    if (!_res) tst_abort();\
} while (0)

#define tst_assert_eq_int_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_eq_int_arr, expr, expected, len, #expr, #expected)
#define tst_assert_ne_int_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_ne_int_arr, expr, expected, len, #expr, #expected)
#define tst_assert_gt_int_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_gt_int_arr, expr, expected, len, #expr, #expected)
#define tst_assert_lt_int_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_lt_int_arr, expr, expected, len, #expr, #expected)
#define tst_assert_ge_int_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_ge_int_arr, expr, expected, len, #expr, #expected)
#define tst_assert_le_int_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_le_int_arr, expr, expected, len, #expr, #expected)

#define tst_assert_eq_uint_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_eq_uint_arr, expr, expected, len, #expr, #expected)
#define tst_assert_ne_uint_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_ne_uint_arr, expr, expected, len, #expr, #expected)
#define tst_assert_gt_uint_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_gt_uint_arr, expr, expected, len, #expr, #expected)
#define tst_assert_lt_uint_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_lt_uint_arr, expr, expected, len, #expr, #expected)
#define tst_assert_ge_uint_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_ge_uint_arr, expr, expected, len, #expr, #expected)
#define tst_assert_le_uint_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_le_uint_arr, expr, expected, len, #expr, #expected)

#define tst_assert_eq_ptr_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_eq_ptr_arr, expr, expected, len, #expr, #expected)
#define tst_assert_ne_ptr_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_ne_ptr_arr, expr, expected, len, #expr, #expected)
#define tst_assert_gt_ptr_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_gt_ptr_arr, expr, expected, len, #expr, #expected)
#define tst_assert_lt_ptr_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_lt_ptr_arr, expr, expected, len, #expr, #expected)
#define tst_assert_ge_ptr_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_ge_ptr_arr, expr, expected, len, #expr, #expected)
#define tst_assert_le_ptr_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_le_ptr_arr, expr, expected, len, #expr, #expected)

#define tst_assert_eq_char_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_eq_char_arr, expr, expected, len, #expr, #expected)
#define tst_assert_ne_char_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_ne_char_arr, expr, expected, len, #expr, #expected)
#define tst_assert_gt_char_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_gt_char_arr, expr, expected, len, #expr, #expected)
#define tst_assert_lt_char_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_lt_char_arr, expr, expected, len, #expr, #expected)
#define tst_assert_ge_char_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_ge_char_arr, expr, expected, len, #expr, #expected)
#define tst_assert_le_char_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_le_char_arr, expr, expected, len, #expr, #expected)

#define tst_assert_eq_size_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_eq_size_arr, expr, expected, len, #expr, #expected)
#define tst_assert_ne_size_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_ne_size_arr, expr, expected, len, #expr, #expected)
#define tst_assert_gt_size_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_gt_size_arr, expr, expected, len, #expr, #expected)
#define tst_assert_lt_size_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_lt_size_arr, expr, expected, len, #expr, #expected)
#define tst_assert_ge_size_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_ge_size_arr, expr, expected, len, #expr, #expected)
#define tst_assert_le_size_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_le_size_arr, expr, expected, len, #expr, #expected)

#define tst_assert_eq_long_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_eq_long_arr, expr, expected, len, #expr, #expected)
#define tst_assert_ne_long_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_ne_long_arr, expr, expected, len, #expr, #expected)
#define tst_assert_gt_long_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_gt_long_arr, expr, expected, len, #expr, #expected)
#define tst_assert_lt_long_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_lt_long_arr, expr, expected, len, #expr, #expected)
#define tst_assert_ge_long_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_ge_long_arr, expr, expected, len, #expr, #expected)
#define tst_assert_le_long_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_le_long_arr, expr, expected, len, #expr, #expected)

#define tst_assert_eq_ulong_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_eq_ulong_arr, expr, expected, len, #expr, #expected)
#define tst_assert_ne_ulong_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_ne_ulong_arr, expr, expected, len, #expr, #expected)
#define tst_assert_gt_ulong_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_gt_ulong_arr, expr, expected, len, #expr, #expected)
#define tst_assert_lt_ulong_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_lt_ulong_arr, expr, expected, len, #expr, #expected)
#define tst_assert_ge_ulong_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_ge_ulong_arr, expr, expected, len, #expr, #expected)
#define tst_assert_le_ulong_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_le_ulong_arr, expr, expected, len, #expr, #expected)

#define tst_assert_gt_dbl_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_gt_dbl_arr, expr, expected, len, #expr, #expected)
#define tst_assert_lt_dbl_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_lt_dbl_arr, expr, expected, len, #expr, #expected)

#define tst_assert_eq_str_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_eq_str_arr, expr, expected, len, #expr, #expected)
#define tst_assert_ne_str_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_ne_str_arr, expr, expected, len, #expr, #expected)
#define tst_assert_gt_str_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_gt_str_arr, expr, expected, len, #expr, #expected)
#define tst_assert_lt_str_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_lt_str_arr, expr, expected, len, #expr, #expected)
#define tst_assert_ge_str_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_ge_str_arr, expr, expected, len, #expr, #expected)
#define tst_assert_le_str_arr(expr, expected, len)\
    _tst_assert_base(_tst_assert_le_str_arr, expr, expected, len, #expr, #expected)

