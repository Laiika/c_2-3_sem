#include "check_key.h"
#include "elements.h"
#include "errors.h"
#include <stdlib.h>

// тесты для key
START_TEST(test_key_bad_first_array_bptr)
{
    int pe_src[3] = {0};
    int *pb_dst = NULL, *pe_dst = NULL;
    int rc;

    rc = key(NULL, pe_src, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, INVALID_PARAM_ERROR);
}
END_TEST

START_TEST(test_key_bad_first_array_eptr)
{
    int pb_src[3] = {0};
    int *pb_dst = NULL, *pe_dst = NULL;
    int rc;

    rc = key(pb_src, NULL, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, INVALID_PARAM_ERROR);
}
END_TEST

START_TEST(test_key_bad_second_array_bptr)
{
    int pb_src[3] = {0}, *pe_src = pb_src + 3;
    int *pe_dst = NULL;
    int rc;

    rc = key(pb_src, pe_src, NULL, &pe_dst);
    ck_assert_int_eq(rc, INVALID_PARAM_ERROR);
}
END_TEST

START_TEST(test_key_bad_second_array_eptr)
{
    int pb_src[3] = {0}, *pe_src = pb_src + 3;
    int *pb_dst = NULL;
    int rc;

    rc = key(pb_src, pe_src, &pb_dst, NULL);
    ck_assert_int_eq(rc, INVALID_PARAM_ERROR);
}
END_TEST

START_TEST(test_key_bad_first_array_eptr_is_less)
{
    int pe_src[3] = {0}, *pb_src = pe_src + 3;
    int *pb_dst = NULL, *pe_dst = NULL;
    int rc;

    rc = key(pb_src, pe_src, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, INVALID_PARAM_ERROR);
}
END_TEST

START_TEST(test_key_bad_first_array_eptr_is_equal)
{
    int pb_src[3] = {0}, *pe_src = pb_src;
    int *pb_dst = NULL, *pe_dst = NULL;
    int rc;

    rc = key(pb_src, pe_src, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, INVALID_PARAM_ERROR);
}
END_TEST

START_TEST(test_key_first_elem_one_neg)
{
    int pb_src[3] = {-3, 4, 10}, *pe_src = pb_src + 3;
    int *pb_dst = NULL, *pe_dst = NULL;
    int rc;

    rc = key(pb_src, pe_src, &pb_dst, &pe_dst);
    ck_assert_int_eq(rc, FILTER_ERROR);
}
END_TEST

START_TEST(test_key_no_neg_elems)
{
    int pb_src[3] = {3, 4, 10}, *pe_src = pb_src + 3;
    int *pb_dst = NULL, *pe_dst = NULL;
    int rc;

    rc = key(pb_src, pe_src, &pb_dst, &pe_dst);

    if (MEMORY_ERROR != rc)
    {
        ck_assert_int_eq(rc, EXIT_SUCCESS);

        for (size_t i = 0; i < 3; i++)
            ck_assert_int_eq(pb_dst[i], pb_src[i]);

        free(pb_dst);
    }
}
END_TEST

START_TEST(test_key_one_neg_elem)
{
    int pb_src[4] = {3, 4, -10, 0}, *pe_src = pb_src + 4;
    int *pb_dst = NULL, *pe_dst = NULL;
    int rc;

    rc = key(pb_src, pe_src, &pb_dst, &pe_dst);
    
    if (MEMORY_ERROR != rc)
    {
        ck_assert_int_eq(rc, EXIT_SUCCESS);

        for (size_t i = 0; i < 2; i++)
            ck_assert_int_eq(pb_dst[i], pb_src[i]);

        free(pb_dst);
    }
}
END_TEST

START_TEST(test_key_few_neg_elemes)
{
    int pb_src[4] = {3, -4, -10, 0}, *pe_src = pb_src + 4;
    int *pb_dst = NULL, *pe_dst = NULL;
    int rc;

    rc = key(pb_src, pe_src, &pb_dst, &pe_dst);
    
    if (MEMORY_ERROR != rc)
    {
        ck_assert_int_eq(rc, EXIT_SUCCESS);

        for (size_t i = 0; i < 2; i++)
            ck_assert_int_eq(pb_dst[i], pb_src[i]);

        free(pb_dst);
    }
}
END_TEST

Suite* key_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("key");
    
    tc_neg = tcase_create("negatives");
    // Добавим в tc_neg соответствующие функции-тесты
    tcase_add_test(tc_neg, test_key_bad_first_array_bptr);
    tcase_add_test(tc_neg, test_key_bad_first_array_eptr);
    tcase_add_test(tc_neg, test_key_bad_second_array_bptr);
    tcase_add_test(tc_neg, test_key_bad_second_array_eptr);
    tcase_add_test(tc_neg, test_key_bad_first_array_eptr_is_less);
    tcase_add_test(tc_neg, test_key_bad_first_array_eptr_is_equal);
    tcase_add_test(tc_neg, test_key_first_elem_one_neg);

    suite_add_tcase(s, tc_neg);

    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, test_key_no_neg_elems);
    tcase_add_test(tc_pos, test_key_one_neg_elem);
    tcase_add_test(tc_pos, test_key_few_neg_elemes);

    suite_add_tcase(s, tc_pos);

    return s;
}
