#include "test.h"

START_TEST(test_inverse_basic_3x3) {
  double input[] = {2, 5, 7, 6, 3, 4, 5, -2, -3};

  double expected[] = {1, -1, 1, -38, 41, -34, 27, -29, 24};

  test_data *test_data = setup(3, 3, input, input, expected);

  int code = s21_inverse_matrix(&test_data->matrix_1, &test_data->matrix_res);
  ck_assert_int_eq(code, OK);

  ck_assert_int_eq(
      s21_eq_matrix(&test_data->matrix_res, &test_data->expected_matrix),
      SUCCESS);

  teardown(test_data);
}
END_TEST

START_TEST(test_inverse_not_square) {
  matrix_t A;
  matrix_t *result = NULL;
  s21_create_matrix(2, 3, &A);
  int res = s21_inverse_matrix(&A, result);
  ck_assert_int_eq(res, ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_inverse_zero_determinant) {
  double input[] = {2, 4, 1, 2};

  test_data *test_data = setup(2, 2, input, input, input);

  int code = s21_inverse_matrix(&test_data->matrix_1, &test_data->matrix_res);
  ck_assert_int_eq(code, CALCULATION_ERROR);

  teardown(test_data);
}
END_TEST

Suite *test_inverse(void) {
  Suite *s = suite_create("test_inverse_matrix");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_inverse_basic_3x3);
  tcase_add_test(tc_core, test_inverse_not_square);
  tcase_add_test(tc_core, test_inverse_zero_determinant);

  suite_add_tcase(s, tc_core);

  return s;
}
