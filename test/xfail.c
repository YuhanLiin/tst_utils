#include "tst_utils.h"

tst_begin_test(int_eq, void)
{
    tst_assert_eq_int(1, 2);
} tst_end_test

tst_begin_test(int_ne, void)
{
    tst_assert_ne_int(1, 1);
} tst_end_test

tst_begin_test(int_gt, void)
{
    tst_assert_gt_int(2, 2);
} tst_end_test

tst_begin_test(int_lt, void)
{
    tst_assert_lt_int(2, 2);
} tst_end_test

tst_begin_test(int_ge, void)
{
    tst_assert_ge_int(1, 2);
} tst_end_test

tst_begin_test(int_le, void)
{
    tst_assert_le_int(5, 2);
} tst_end_test

tst_begin_suite(INT)
{
    tst_test_xfail(int_eq,);
    tst_test_xfail(int_ne,);
    tst_test_xfail(int_lt,);
    tst_test_xfail(int_gt,);
    tst_test_xfail(int_le,);
    tst_test_xfail(int_ge,);
} tst_end_suite


tst_begin_test(uint_eq, void)
{
    tst_assert_eq_uint(1, 2);
} tst_end_test

tst_begin_test(uint_ne, void)
{
    tst_assert_ne_uint(1, 1);
} tst_end_test

tst_begin_test(uint_gt, void)
{
    tst_assert_gt_uint(2, 2);
} tst_end_test

tst_begin_test(uint_lt, void)
{
    tst_assert_lt_uint(2, 2);
} tst_end_test

tst_begin_test(uint_ge, void)
{
    tst_assert_ge_uint(1, 2);
} tst_end_test

tst_begin_test(uint_le, void)
{
    tst_assert_le_uint(5, 2);
} tst_end_test

tst_begin_suite(UINT)
{
    tst_test_xfail(uint_eq,);
    tst_test_xfail(uint_ne,);
    tst_test_xfail(uint_lt,);
    tst_test_xfail(uint_gt,);
    tst_test_xfail(uint_le,);
    tst_test_xfail(uint_ge,);
} tst_end_suite


tst_begin_test(long_eq, void)
{
    tst_assert_eq_long(1, 2);
} tst_end_test

tst_begin_test(long_ne, void)
{
    tst_assert_ne_long(1, 1);
} tst_end_test

tst_begin_test(long_gt, void)
{
    tst_assert_gt_long(2, 2);
} tst_end_test

tst_begin_test(long_lt, void)
{
    tst_assert_lt_long(2, 2);
} tst_end_test

tst_begin_test(long_ge, void)
{
    tst_assert_ge_long(1, 2);
} tst_end_test

tst_begin_test(long_le, void)
{
    tst_assert_le_long(5, 2);
} tst_end_test

tst_begin_suite(LONG)
{
    tst_test_xfail(long_eq,);
    tst_test_xfail(long_ne,);
    tst_test_xfail(long_lt,);
    tst_test_xfail(long_gt,);
    tst_test_xfail(long_le,);
    tst_test_xfail(long_ge,);
} tst_end_suite


tst_begin_test(ulong_eq, void)
{
    tst_assert_eq_ulong(1, 2);
} tst_end_test

tst_begin_test(ulong_ne, void)
{
    tst_assert_ne_ulong(1, 1);
} tst_end_test

tst_begin_test(ulong_gt, void)
{
    tst_assert_gt_ulong(2, 2);
} tst_end_test

tst_begin_test(ulong_lt, void)
{
    tst_assert_lt_ulong(2, 2);
} tst_end_test

tst_begin_test(ulong_ge, void)
{
    tst_assert_ge_ulong(1, 2);
} tst_end_test

tst_begin_test(ulong_le, void)
{
    tst_assert_le_ulong(5, 2);
} tst_end_test

tst_begin_suite(ULONG)
{
    tst_test_xfail(ulong_eq,);
    tst_test_xfail(ulong_ne,);
    tst_test_xfail(ulong_lt,);
    tst_test_xfail(ulong_gt,);
    tst_test_xfail(ulong_le,);
    tst_test_xfail(ulong_ge,);
} tst_end_suite


tst_begin_test(size_eq, void)
{
    tst_assert_eq_size(1, 2);
} tst_end_test

tst_begin_test(size_ne, void)
{
    tst_assert_ne_size(1, 1);
} tst_end_test

tst_begin_test(size_gt, void)
{
    tst_assert_gt_size(2, 2);
} tst_end_test

tst_begin_test(size_lt, void)
{
    tst_assert_lt_size(2, 2);
} tst_end_test

tst_begin_test(size_ge, void)
{
    tst_assert_ge_size(1, 2);
} tst_end_test

tst_begin_test(size_le, void)
{
    tst_assert_le_size(5, 2);
} tst_end_test

tst_begin_suite(SIZE)
{
    tst_test_xfail(size_eq,);
    tst_test_xfail(size_ne,);
    tst_test_xfail(size_lt,);
    tst_test_xfail(size_gt,);
    tst_test_xfail(size_le,);
    tst_test_xfail(size_ge,);
} tst_end_suite


tst_begin_test(char_eq, void)
{
    tst_assert_eq_char('1', '2');
} tst_end_test

tst_begin_test(char_ne, void)
{
    tst_assert_ne_char('1', '1');
} tst_end_test

tst_begin_test(char_gt, void)
{
    tst_assert_gt_char('2', '2');
} tst_end_test

tst_begin_test(char_lt, void)
{
    tst_assert_lt_char('2', '2');
} tst_end_test

tst_begin_test(char_ge, void)
{
    tst_assert_ge_char('1', '2');
} tst_end_test

tst_begin_test(char_le, void)
{
    tst_assert_le_char('5', '2');
} tst_end_test

tst_begin_suite(CHAR)
{
    tst_test_xfail(char_eq,);
    tst_test_xfail(char_ne,);
    tst_test_xfail(char_lt,);
    tst_test_xfail(char_gt,);
    tst_test_xfail(char_le,);
    tst_test_xfail(char_ge,);
} tst_end_suite


tst_begin_test(str_eq, void)
{
    tst_assert_eq_str("we", "you");
} tst_end_test

tst_begin_test(str_ne, void)
{
    tst_assert_ne_str("k", "k");
} tst_end_test

tst_begin_test(str_gt, void)
{
    tst_assert_gt_str("aba", "aba");
} tst_end_test

tst_begin_test(str_lt, void)
{
    tst_assert_lt_str("aba", "aba");
} tst_end_test

tst_begin_test(str_ge, void)
{
    tst_assert_ge_str("aba", "abc");
} tst_end_test

tst_begin_test(str_le, void)
{
    tst_assert_le_str("aba", "ab");
} tst_end_test

tst_begin_suite(STR)
{
    tst_test_xfail(str_eq,);
    tst_test_xfail(str_ne,);
    tst_test_xfail(str_lt,);
    tst_test_xfail(str_gt,);
    tst_test_xfail(str_le,);
    tst_test_xfail(str_ge,);
} tst_end_suite


tst_begin_test(ptr_eq, void)
{
    char arr[2] = {0};
    tst_assert_eq_ptr(&arr[1], &arr[0]);
} tst_end_test

tst_begin_test(ptr_ne, void)
{
    char arr[2] = {0};
    tst_assert_ne_ptr(&arr[1], &arr[1]);
} tst_end_test

tst_begin_test(ptr_gt, void)
{
    char arr[2] = {0};
    tst_assert_gt_ptr(&arr[1], &arr[1]);
} tst_end_test

tst_begin_test(ptr_lt, void)
{
    char arr[2] = {0};
    tst_assert_lt_ptr(&arr[1], &arr[1]);
} tst_end_test

tst_begin_test(ptr_ge, void)
{
    char arr[2] = {0};
    tst_assert_ge_ptr(&arr[0], &arr[1]);
} tst_end_test

tst_begin_test(ptr_le, void)
{
    char arr[2] = {0};
    tst_assert_le_ptr(&arr[1], &arr[0]);
} tst_end_test

tst_begin_suite(PTR)
{
    tst_test_xfail(ptr_eq,);
    tst_test_xfail(ptr_ne,);
    tst_test_xfail(ptr_lt,);
    tst_test_xfail(ptr_gt,);
    tst_test_xfail(ptr_le,);
    tst_test_xfail(ptr_ge,);
} tst_end_suite


tst_begin_test(dbl_gt, void)
{
    tst_assert_gt_dbl(2.5, 2.5);
} tst_end_test

tst_begin_test(dbl_lt, void)
{
    tst_assert_lt_dbl(2.5, 2.5);
} tst_end_test

tst_begin_test(dbl_ge, void)
{
    tst_assert_ge_dbl(1.5, 2.5);
} tst_end_test

tst_begin_test(dbl_le, void)
{
    tst_assert_le_dbl(5.5, 2.5);
} tst_end_test

tst_begin_suite(DBL)
{
    tst_test_xfail(dbl_lt,);
    tst_test_xfail(dbl_gt,);
    tst_test_xfail(dbl_le,);
    tst_test_xfail(dbl_ge,);
} tst_end_suite


tst_begin_test(abort, void)
{
    tst_abort();
} tst_end_test

tst_begin_suite(ALL_XFAIL)
{
    tst_suite(INT);
    tst_suite(UINT);
    tst_suite(LONG);
    tst_suite(ULONG);
    tst_suite(SIZE);
    tst_suite(CHAR);
    tst_suite(STR);
    tst_suite(PTR);
    tst_suite(DBL);

    tst_test_xfail(abort,);
} tst_end_suite

void xfailing_tests(void)
{
    tst_suite(ALL_XFAIL);
}
