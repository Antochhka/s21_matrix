#include "test.h"

test_data *setup_transpose(int i_1, int j_1, int i_2, int j_2,
                           double *input_matrix_1, double *expected_matrix) {
  test_data *test_data = malloc(sizeof(*test_data));

  s21_create_matrix(i_1, j_1, &test_data->matrix_1);
  s21_create_matrix(i_1, j_1, &test_data->matrix_2);
  s21_create_matrix(i_1, j_1, &test_data->matrix_res);
  s21_create_matrix(i_2, j_2, &test_data->expected_matrix);

  set_matrix(&test_data->matrix_1, input_matrix_1);
  set_matrix(&test_data->matrix_2, input_matrix_1);
  set_matrix(&test_data->expected_matrix, expected_matrix);

  return test_data;
}

START_TEST(test_transpose_valid) {
  double input[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

  double expected[] = {1.0, 4.0, 2.0, 5.0, 3.0, 6.0};

  test_data *test_data = setup_transpose(2, 3, 3, 2, input, expected);

  int res_code = s21_transpose(&test_data->matrix_1, &test_data->matrix_res);

  ck_assert_int_eq(res_code, OK);
  ck_assert_int_eq(
      s21_eq_matrix(&test_data->expected_matrix, &test_data->matrix_res), 1);

  teardown(test_data);
}
END_TEST

START_TEST(test_transpose_invalid_matrix) {
  matrix_t A;
  A.rows = 0;
  A.columns = 2;
  A.matrix = NULL;

  matrix_t result;
  result.matrix = NULL;

  int res_code = s21_transpose(&A, &result);

  ck_assert_int_eq(res_code, ERROR);
}
END_TEST

Suite *transpose_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("test_transpose");

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_transpose_valid);
  tcase_add_test(tc_core, test_transpose_invalid_matrix);

  suite_add_tcase(s, tc_core);

  return s;
}
