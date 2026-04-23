#include "test.h"

START_TEST(test_sub_1) {
  double input_matrix_1[] = {1, 2, 3, 4, 5, 6};

  double input_matrix_2[] = {1, 2, 3, 4, 5, 6};

  double expected_matrix[] = {0, 0, 0, 0, 0, 0};

  test_data *test_data =
      setup(2, 3, input_matrix_1, input_matrix_2, expected_matrix);

  s21_sub_matrix(&test_data->matrix_1, &test_data->matrix_2,
                 &test_data->matrix_res);

  ck_assert_int_eq(
      s21_eq_matrix(&test_data->expected_matrix, &test_data->matrix_res), 1);

  teardown(test_data);
}
END_TEST

START_TEST(test_sum_invalid_size) {
  matrix_t A, B, result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);
  s21_create_matrix(3, 2, &result);
  int res = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(res, CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *sub_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("test_sub_matrix");

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_sub_1);
  tcase_add_test(tc_core, test_sum_invalid_size);

  suite_add_tcase(s, tc_core);

  return s;
}