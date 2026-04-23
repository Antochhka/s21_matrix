#include "test.h"

test_data *setup(int i_1, int j_1, double *input_matrix_1,
                 double *input_matrix_2, double *expected_matrix) {
  test_data *test_data = malloc(sizeof(*test_data));

  s21_create_matrix(i_1, j_1, &test_data->matrix_1);
  s21_create_matrix(i_1, j_1, &test_data->matrix_2);
  s21_create_matrix(i_1, j_1, &test_data->matrix_res);
  s21_create_matrix(i_1, j_1, &test_data->expected_matrix);

  set_matrix(&test_data->matrix_1, input_matrix_1);
  set_matrix(&test_data->matrix_2, input_matrix_2);
  set_matrix(&test_data->expected_matrix, expected_matrix);

  return test_data;
}

void teardown(test_data *test_data) {
  s21_remove_matrix(&test_data->matrix_1);
  s21_remove_matrix(&test_data->matrix_2);
  s21_remove_matrix(&test_data->matrix_res);
  s21_remove_matrix(&test_data->expected_matrix);

  free(test_data);
}

START_TEST(test_sum_1) {
  double input_matrix_1[] = {1, 2, 3, 4, 5, 6};

  double input_matrix_2[] = {1, 2, 3, 4, 5, 6};

  double expected_matrix[] = {2, 4, 6, 8, 10, 12};

  test_data *test_data =
      setup(2, 3, input_matrix_1, input_matrix_2, expected_matrix);

  s21_sum_matrix(&test_data->matrix_1, &test_data->matrix_2,
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
  s21_remove_matrix(&result);
}
END_TEST

Suite *sum_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("test_sum_matrix");

  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_sum_1);
  tcase_add_test(tc_core, test_sum_invalid_size);

  suite_add_tcase(s, tc_core);

  return s;
}