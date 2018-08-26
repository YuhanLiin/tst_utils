#include "tst_utils.h"

#define ARR_LEN 3

tst_begin_test(int_array_asserts, void)
{
    int int1[] = {1, 2, 3};
    int int2[] = {-1, 100, 1001};
    int int3[] = {-1, 100, 1005};
    tst_assert_eq_int_arr(int1, int2, 0);
    tst_assert_eq_int_arr(int1, int1, ARR_LEN);
    tst_assert_ne_int_arr(int3, int2, ARR_LEN);
    tst_assert_le_int_arr(int2, int1, ARR_LEN);
    tst_assert_lt_int_arr(int3, int1, ARR_LEN);
    tst_assert_ge_int_arr(int1, int2, ARR_LEN);
    tst_assert_gt_int_arr(int3, int2, ARR_LEN);
    tst_assert_ge_int_arr(int2, int2, ARR_LEN);
    tst_assert_le_int_arr(int3, int3, ARR_LEN);
} tst_end_test

tst_begin_test(long_array_asserts, void)
{
    long long int long1[] = {1, 2, 3};
    long long int long2[] = {-1, 100, 1001};
    long long int long3[] = {-1, 100, 1005};
    tst_assert_eq_long_arr(long1, long2, 0);
    tst_assert_eq_long_arr(long1, long1, ARR_LEN);
    tst_assert_ne_long_arr(long3, long2, ARR_LEN);
    tst_assert_le_long_arr(long2, long1, ARR_LEN);
    tst_assert_lt_long_arr(long3, long1, ARR_LEN);
    tst_assert_ge_long_arr(long1, long2, ARR_LEN);
    tst_assert_gt_long_arr(long3, long2, ARR_LEN);
    tst_assert_ge_long_arr(long2, long2, ARR_LEN);
    tst_assert_le_long_arr(long3, long3, ARR_LEN);
} tst_end_test

tst_begin_test(uint_array_asserts, void)
{
    unsigned uint1[] = {1, 2, 3};
    unsigned uint2[] = {0, 100, 1001};
    unsigned uint3[] = {0, 100, 1005};
    tst_assert_eq_uint_arr(uint1, uint2, 0);
    tst_assert_eq_uint_arr(uint1, uint1, ARR_LEN);
    tst_assert_ne_uint_arr(uint3, uint2, ARR_LEN);
    tst_assert_le_uint_arr(uint2, uint1, ARR_LEN);
    tst_assert_lt_uint_arr(uint3, uint1, ARR_LEN);
    tst_assert_ge_uint_arr(uint1, uint2, ARR_LEN);
    tst_assert_gt_uint_arr(uint3, uint2, ARR_LEN);
    tst_assert_ge_uint_arr(uint2, uint2, ARR_LEN);
    tst_assert_le_uint_arr(uint3, uint3, ARR_LEN);
} tst_end_test

tst_begin_test(ulong_array_asserts, void)
{
    unsigned long long int ulong1[] = {1, 2, 3};
    unsigned long long int ulong2[] = {0, 100, 1001};
    unsigned long long int ulong3[] = {0, 100, 1005};
    tst_assert_eq_ulong_arr(ulong1, ulong2, 0);
    tst_assert_eq_ulong_arr(ulong1, ulong1, ARR_LEN);
    tst_assert_ne_ulong_arr(ulong3, ulong2, ARR_LEN);
    tst_assert_le_ulong_arr(ulong2, ulong1, ARR_LEN);
    tst_assert_lt_ulong_arr(ulong3, ulong1, ARR_LEN);
    tst_assert_ge_ulong_arr(ulong1, ulong2, ARR_LEN);
    tst_assert_gt_ulong_arr(ulong3, ulong2, ARR_LEN);
    tst_assert_ge_ulong_arr(ulong2, ulong2, ARR_LEN);
    tst_assert_le_ulong_arr(ulong3, ulong3, ARR_LEN);
} tst_end_test

tst_begin_test(size_array_asserts, void)
{
    size_t size1[] = {1, 2, 3};
    size_t size2[] = {0, 100, 1001};
    size_t size3[] = {0, 100, 1005};
    tst_assert_eq_size_arr(size1, size2, 0);
    tst_assert_eq_size_arr(size1, size1, ARR_LEN);
    tst_assert_ne_size_arr(size3, size2, ARR_LEN);
    tst_assert_le_size_arr(size2, size1, ARR_LEN);
    tst_assert_lt_size_arr(size3, size1, ARR_LEN);
    tst_assert_ge_size_arr(size1, size2, ARR_LEN);
    tst_assert_gt_size_arr(size3, size2, ARR_LEN);
    tst_assert_ge_size_arr(size2, size2, ARR_LEN);
    tst_assert_le_size_arr(size3, size3, ARR_LEN);
} tst_end_test

tst_begin_test(char_array_asserts, void)
{
    char char1[] = {'a', 'b', 'c'};
    char char2[] = {'Z', 'l', 'k'};
    char char3[] = {'Z', 'z', 'v'};
    tst_assert_eq_char_arr(char1, char2, 0);
    tst_assert_eq_char_arr(char1, char1, ARR_LEN);
    tst_assert_ne_char_arr(char3, char2, ARR_LEN);
    tst_assert_le_char_arr(char2, char1, ARR_LEN);
    tst_assert_lt_char_arr(char3, char1, ARR_LEN);
    tst_assert_ge_char_arr(char1, char2, ARR_LEN);
    tst_assert_gt_char_arr(char3, char2, ARR_LEN);
    tst_assert_ge_char_arr(char2, char2, ARR_LEN);
    tst_assert_le_char_arr(char3, char3, ARR_LEN);
} tst_end_test

tst_begin_test(ptr_array_asserts, void)
{
    char arr[10] = {0};
    const void * ptr1[] = {&arr[1], &arr[5], &arr[7]};
    const void * ptr2[] = {&arr[0], &arr[6], &arr[7]};
    const void * ptr3[] = {&arr[0], &arr[6], &arr[9]};
    tst_assert_eq_ptr_arr(ptr1, ptr2, 0);
    tst_assert_eq_ptr_arr(ptr1, ptr1, ARR_LEN);
    tst_assert_ne_ptr_arr(ptr3, ptr2, ARR_LEN);
    tst_assert_le_ptr_arr(ptr2, ptr1, ARR_LEN);
    tst_assert_lt_ptr_arr(ptr3, ptr1, ARR_LEN);
    tst_assert_ge_ptr_arr(ptr1, ptr2, ARR_LEN);
    tst_assert_gt_ptr_arr(ptr3, ptr2, ARR_LEN);
    tst_assert_ge_ptr_arr(ptr2, ptr2, ARR_LEN);
    tst_assert_le_ptr_arr(ptr3, ptr3, ARR_LEN);
} tst_end_test

tst_begin_test(str_array_asserts, void)
{
    const char * str1[] = {"abc", "efg", "kcbfgs"};
    const char * str2[] = {"ab", "Z:", "//op"};
    const char * str3[] = {"ab", "Z:", "//po"};
    tst_assert_eq_str_arr(str1, str2, 0);
    tst_assert_eq_str_arr(str1, str1, ARR_LEN);
    tst_assert_ne_str_arr(str3, str2, ARR_LEN);
    tst_assert_le_str_arr(str2, str1, ARR_LEN);
    tst_assert_lt_str_arr(str3, str1, ARR_LEN);
    tst_assert_ge_str_arr(str1, str2, ARR_LEN);
    tst_assert_gt_str_arr(str3, str2, ARR_LEN);
    tst_assert_ge_str_arr(str2, str2, ARR_LEN);
    tst_assert_le_str_arr(str3, str3, ARR_LEN);
} tst_end_test

tst_begin_test(dbl_array_asserts, void)
{
    double dbl1[] = {1.5, 2.4, 3.9};
    double dbl2[] = {0, 100.234, 943};
    double dbl3[] = {0, 100.777, 4.4};
    tst_assert_lt_dbl_arr(dbl2, dbl1, ARR_LEN);
    tst_assert_lt_dbl_arr(dbl3, dbl1, ARR_LEN);
    tst_assert_gt_dbl_arr(dbl1, dbl2, ARR_LEN);
    tst_assert_gt_dbl_arr(dbl3, dbl2, ARR_LEN);
} tst_end_test

void array_asserts_passing_tests(void)
{
    tst_begin_suite(PASSING_ARRAY_ASSERTS)
    {
        tst_test(int_array_asserts,);
        tst_test(long_array_asserts,);
        tst_test(uint_array_asserts,);
        tst_test(ulong_array_asserts,);
        tst_test(size_array_asserts,);
        tst_test(char_array_asserts,);
        tst_test(ptr_array_asserts,);
        tst_test(str_array_asserts,);
        tst_test(dbl_array_asserts,);
    } tst_end_suite
}
