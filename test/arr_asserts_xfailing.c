#include "tst_utils.h"

#define ARR_LEN 3

// int array asserts
tst_begin_test(int_arr_eq, const int * a, const int * b)
{
    tst_assert_eq_int_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(int_arr_ne, const int * a, const int * b)
{
    tst_assert_ne_int_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(int_arr_gt, const int * a, const int * b)
{
    tst_assert_gt_int_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(int_arr_ge, const int * a, const int * b)
{
    tst_assert_ge_int_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(int_arr_lt, const int * a, const int * b)
{
    tst_assert_lt_int_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(int_arr_le, const int * a, const int * b)
{
    tst_assert_le_int_arr(a, b, ARR_LEN);
} tst_end_test


// uint array asserts
tst_begin_test(uint_arr_eq, const unsigned * a, const unsigned * b)
{
    tst_assert_eq_uint_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(uint_arr_ne, const unsigned * a, const unsigned * b)
{
    tst_assert_ne_uint_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(uint_arr_gt, const unsigned * a, const unsigned * b)
{
    tst_assert_gt_uint_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(uint_arr_ge, const unsigned * a, const unsigned * b)
{
    tst_assert_ge_uint_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(uint_arr_lt, const unsigned * a, const unsigned * b)
{
    tst_assert_lt_uint_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(uint_arr_le, const unsigned * a, const unsigned * b)
{
    tst_assert_le_uint_arr(a, b, ARR_LEN);
} tst_end_test


// long array asserts
tst_begin_test(long_arr_eq, const long long int * a, const long long int * b)
{
    tst_assert_eq_long_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(long_arr_ne, const long long int * a, const long long int * b)
{
    tst_assert_ne_long_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(long_arr_gt, const long long int * a, const long long int * b)
{
    tst_assert_gt_long_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(long_arr_ge, const long long int * a, const long long int * b)
{
    tst_assert_ge_long_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(long_arr_lt, const long long int * a, const long long int * b)
{
    tst_assert_lt_long_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(long_arr_le, const long long int * a, const long long int * b)
{
    tst_assert_le_long_arr(a, b, ARR_LEN);
} tst_end_test


// ulong array asserts
tst_begin_test(ulong_arr_eq, const unsigned long long * a, const unsigned long long * b)
{
    tst_assert_eq_ulong_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(ulong_arr_ne, const unsigned long long * a, const unsigned long long * b)
{
    tst_assert_ne_ulong_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(ulong_arr_gt, const unsigned long long * a, const unsigned long long * b)
{
    tst_assert_gt_ulong_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(ulong_arr_ge, const unsigned long long * a, const unsigned long long * b)
{
    tst_assert_ge_ulong_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(ulong_arr_lt, const unsigned long long * a, const unsigned long long * b)
{
    tst_assert_lt_ulong_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(ulong_arr_le, const unsigned long long * a, const unsigned long long * b)
{
    tst_assert_le_ulong_arr(a, b, ARR_LEN);
} tst_end_test


// size array asserts
tst_begin_test(size_arr_eq, const size_t * a, const size_t * b)
{
    tst_assert_eq_size_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(size_arr_ne, const size_t * a, const size_t * b)
{
    tst_assert_ne_size_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(size_arr_gt, const size_t * a, const size_t * b)
{
    tst_assert_gt_size_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(size_arr_ge, const size_t * a, const size_t * b)
{
    tst_assert_ge_size_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(size_arr_lt, const size_t * a, const size_t * b)
{
    tst_assert_lt_size_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(size_arr_le, const size_t * a, const size_t * b)
{
    tst_assert_le_size_arr(a, b, ARR_LEN);
} tst_end_test


// char array asserts
tst_begin_test(char_arr_eq, const char * a, const char * b)
{
    tst_assert_eq_char_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(char_arr_ne, const char * a, const char * b)
{
    tst_assert_ne_char_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(char_arr_gt, const char * a, const char * b)
{
    tst_assert_gt_char_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(char_arr_ge, const char * a, const char * b)
{
    tst_assert_ge_char_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(char_arr_lt, const char * a, const char * b)
{
    tst_assert_lt_char_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(char_arr_le, const char * a, const char * b)
{
    tst_assert_le_char_arr(a, b, ARR_LEN);
} tst_end_test


// str array asserts
tst_begin_test(str_arr_eq, const char * const * a, const char * const * b)
{
    tst_assert_eq_str_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(str_arr_ne, const char * const * a, const char * const * b)
{
    tst_assert_ne_str_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(str_arr_gt, const char * const * a, const char * const * b)
{
    tst_assert_gt_str_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(str_arr_ge, const char * const * a, const char * const * b)
{
    tst_assert_ge_str_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(str_arr_lt, const char * const * a, const char * const * b)
{
    tst_assert_lt_str_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(str_arr_le, const char * const * a, const char * const * b)
{
    tst_assert_le_str_arr(a, b, ARR_LEN);
} tst_end_test


// ptr array asserts
tst_begin_test(ptr_arr_eq, const void * const * a, const void * const * b)
{
    tst_assert_eq_ptr_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(ptr_arr_ne, const void * const * a, const void * const * b)
{
    tst_assert_ne_ptr_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(ptr_arr_gt, const void * const * a, const void * const * b)
{
    tst_assert_gt_ptr_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(ptr_arr_ge, const void * const * a, const void * const * b)
{
    tst_assert_ge_ptr_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(ptr_arr_lt, const void * const * a, const void * const * b)
{
    tst_assert_lt_ptr_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(ptr_arr_le, const void * const * a, const void * const * b)
{
    tst_assert_le_ptr_arr(a, b, ARR_LEN);
} tst_end_test


// dbl array asserts
tst_begin_test(dbl_arr_gt, const double * a, const double * b)
{
    tst_assert_gt_dbl_arr(a, b, ARR_LEN);
} tst_end_test

tst_begin_test(dbl_arr_lt, const double * a, const double * b)
{
    tst_assert_lt_dbl_arr(a, b, ARR_LEN);
} tst_end_test


void array_asserts_xfailing_tests(void)
{
    // Test for failure cases of all assertions
    tst_begin_suite(FAILING_ARRAY_ASSERTS)
    {
        tst_begin_suite(INT_ARR)
        {
            int arr1[] = {0, 5, 7};
            int arr2[] = {0, 0, 7};
            tst_test_xfail(int_arr_eq, arr1, arr2);
            tst_test_xfail(int_arr_ne, arr2, arr2);
            tst_test_xfail(int_arr_lt, arr1, arr1);
            tst_test_xfail(int_arr_lt, arr1, arr2);
            tst_test_xfail(int_arr_gt, arr1, arr1);
            tst_test_xfail(int_arr_gt, arr2, arr1);
            tst_test_xfail(int_arr_le, arr1, arr2);
            tst_test_xfail(int_arr_ge, arr2, arr1);
        } tst_end_suite

        tst_begin_suite(UINT_ARR)
        {
            unsigned arr1[] = {0, 5, 7};
            unsigned arr2[] = {0, 0, 7};
            tst_test_xfail(uint_arr_eq, arr1, arr2);
            tst_test_xfail(uint_arr_ne, arr2, arr2);
            tst_test_xfail(uint_arr_lt, arr1, arr1);
            tst_test_xfail(uint_arr_lt, arr1, arr2);
            tst_test_xfail(uint_arr_gt, arr1, arr1);
            tst_test_xfail(uint_arr_gt, arr2, arr1);
            tst_test_xfail(uint_arr_le, arr1, arr2);
            tst_test_xfail(uint_arr_ge, arr2, arr1);
        } tst_end_suite

        tst_begin_suite(LONG_ARR)
        {
            long long int arr1[] = {0, 5, 7};
            long long int arr2[] = {0, 0, 7};
            tst_test_xfail(long_arr_eq, arr1, arr2);
            tst_test_xfail(long_arr_ne, arr2, arr2);
            tst_test_xfail(long_arr_lt, arr1, arr1);
            tst_test_xfail(long_arr_lt, arr1, arr2);
            tst_test_xfail(long_arr_gt, arr1, arr1);
            tst_test_xfail(long_arr_gt, arr2, arr1);
            tst_test_xfail(long_arr_le, arr1, arr2);
            tst_test_xfail(long_arr_ge, arr2, arr1);
        } tst_end_suite

        tst_begin_suite(ULONG_ARR)
        {
            unsigned long long arr1[] = {0, 5, 7};
            unsigned long long arr2[] = {0, 0, 7};
            tst_test_xfail(ulong_arr_eq, arr1, arr2);
            tst_test_xfail(ulong_arr_ne, arr2, arr2);
            tst_test_xfail(ulong_arr_lt, arr1, arr1);
            tst_test_xfail(ulong_arr_lt, arr1, arr2);
            tst_test_xfail(ulong_arr_gt, arr1, arr1);
            tst_test_xfail(ulong_arr_gt, arr2, arr1);
            tst_test_xfail(ulong_arr_le, arr1, arr2);
            tst_test_xfail(ulong_arr_ge, arr2, arr1);
        } tst_end_suite

        tst_begin_suite(SIZE_ARR)
        {
            size_t arr1[] = {0, 5, 7};
            size_t arr2[] = {0, 0, 7};
            tst_test_xfail(size_arr_eq, arr1, arr2);
            tst_test_xfail(size_arr_ne, arr2, arr2);
            tst_test_xfail(size_arr_lt, arr1, arr1);
            tst_test_xfail(size_arr_lt, arr1, arr2);
            tst_test_xfail(size_arr_gt, arr1, arr1);
            tst_test_xfail(size_arr_gt, arr2, arr1);
            tst_test_xfail(size_arr_le, arr1, arr2);
            tst_test_xfail(size_arr_ge, arr2, arr1);
        } tst_end_suite

        tst_begin_suite(CHAR_ARR)
        {
            char arr1[] = {'\0', 'a', 'h'};
            char arr2[] = {'\0', '\0', 'k'};
            tst_test_xfail(char_arr_eq, arr1, arr2);
            tst_test_xfail(char_arr_ne, arr2, arr2);
            tst_test_xfail(char_arr_lt, arr1, arr1);
            tst_test_xfail(char_arr_lt, arr1, arr2);
            tst_test_xfail(char_arr_gt, arr1, arr1);
            tst_test_xfail(char_arr_gt, arr2, arr1);
            tst_test_xfail(char_arr_le, arr1, arr2);
            tst_test_xfail(char_arr_ge, arr2, arr1);
        } tst_end_suite

        tst_begin_suite(STR_ARR)
        {
            const char * arr1[] = {"asdfg", "bbgds", "kcck"};
            const char * arr2[] = {"ER", "ggg", "c"};
            tst_test_xfail(str_arr_eq, arr1, arr2);
            tst_test_xfail(str_arr_ne, arr2, arr2);
            tst_test_xfail(str_arr_lt, arr1, arr1);
            tst_test_xfail(str_arr_lt, arr1, arr2);
            tst_test_xfail(str_arr_gt, arr1, arr1);
            tst_test_xfail(str_arr_gt, arr2, arr1);
            tst_test_xfail(str_arr_le, arr1, arr2);
            tst_test_xfail(str_arr_ge, arr2, arr1);
        } tst_end_suite

        tst_begin_suite(PTR_ARR)
        {
            char c[2];
            const void * arr1[] = {c, c, &c[1]};
            const void * arr2[] = {c, c, c};
            tst_test_xfail(ptr_arr_eq, arr1, arr2);
            tst_test_xfail(ptr_arr_ne, arr2, arr2);
            tst_test_xfail(ptr_arr_lt, arr1, arr1);
            tst_test_xfail(ptr_arr_lt, arr1, arr2);
            tst_test_xfail(ptr_arr_gt, arr1, arr1);
            tst_test_xfail(ptr_arr_gt, arr2, arr1);
            tst_test_xfail(ptr_arr_le, arr1, arr2);
            tst_test_xfail(ptr_arr_ge, arr2, arr1);
        } tst_end_suite

        tst_begin_suite(DBL_ARR)
        {
            double arr1[] = {-8.90, 5, 7};
            double arr2[] = {-9.03, 0, 7};
            tst_test_xfail(dbl_arr_lt, arr1, arr1);
            tst_test_xfail(dbl_arr_lt, arr1, arr2);
            tst_test_xfail(dbl_arr_gt, arr1, arr1);
            tst_test_xfail(dbl_arr_gt, arr2, arr1);
        } tst_end_suite

    } tst_end_suite
}
