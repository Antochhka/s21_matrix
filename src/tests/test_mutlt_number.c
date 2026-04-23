#include "test.h"

START_TEST(test_mult_number_1) {
  double input_matrix[] = {1.0, -2.0, 3.5, 0.0, 4.2, -1.1};

  double expected_matrix[] = {2.0, -4.0, 7.0, 0.0, 8.4, -2.2};

  double number = 2.0;

  test_data *test_data =
      setup(2, 3, input_matrix, input_matrix, expected_matrix);

  int res_code =
      s21_mult_number(&test_data->matrix_1, number, &test_data->matrix_res);

  ck_assert_int_eq(res_code, OK);
  ck_assert_int_eq(
      s21_eq_matrix(&test_data->expected_matrix, &test_data->matrix_res), 1);

  teardown(test_data);
}
END_TEST

START_TEST(test_mult_number_invalid_matrix) {
  matrix_t A;
  A.rows = 0;
  A.columns = 3;
  A.matrix = NULL;

  matrix_t result;
  result.matrix = NULL;

  int res_code = s21_mult_number(&A, 5.0, &result);

  ck_assert_int_eq(res_code, ERROR);
}
END_TEST

Suite *mult_number(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("test_mult_number");

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_mult_number_1);
  tcase_add_test(tc_core, test_mult_number_invalid_matrix);

  suite_add_tcase(s, tc_core);

  return s;
}