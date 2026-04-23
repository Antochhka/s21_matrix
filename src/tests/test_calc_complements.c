#include "test.h"

START_TEST(test_calc_complements_3x3) {
  double input_matrix[] = {1, 2, 3, 0, 4, 2, 5, 2, 1};

  double expected_matrix[] = {0, 10, -20, 4, -14, 8, -8, -2, 4};

  test_data *test_data =
      setup(3, 3, input_matrix, input_matrix, expected_matrix);

  int res = s21_calc_complements(&test_data->matrix_1, &test_data->matrix_res);

  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(
      s21_eq_matrix(&test_data->expected_matrix, &test_data->matrix_res), 1);

  teardown(test_data);
}
END_TEST

START_TEST(test_calc_complements_non_square) {
  matrix_t A, result;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &result);

  int res = s21_calc_complements(&A, &result);

  ck_assert_int_eq(res, CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_calc_complements_invalid_matrix) {
  matrix_t A = {0};
  A.rows = 0;
  A.columns = 0;
  A.matrix = NULL;

  matrix_t result;
  int res = s21_calc_complements(&A, &result);

  ck_assert_int_eq(res, ERROR);
}
END_TEST

START_TEST(test_calc_complements_from_image) {
  double input_matrix[] = {1, 2, 3, 0, 4, 2, 5, 2, 1};

  double expected_matrix[] = {0, 10, -20, 4, -14, 8, -8, -2, 4};

  test_data *test_data =
      setup(3, 3, input_matrix, input_matrix, expected_matrix);

  int res = s21_calc_complements(&test_data->matrix_1, &test_data->matrix_res);

  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(
      s21_eq_matrix(&test_data->expected_matrix, &test_data->matrix_res), 1);

  teardown(test_data);
}
END_TEST

Suite *complements_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("test_calc_complements");

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_calc_complements_3x3);
  tcase_add_test(tc_core, test_calc_complements_non_square);
  tcase_add_test(tc_core, test_calc_complements_invalid_matrix);
  tcase_add_test(tc_core, test_calc_complements_from_image);

  suite_add_tcase(s, tc_core);

  return s;
}
