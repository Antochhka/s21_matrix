#include "test.h"

test_data *setup_mult_matrix(int i_1, int j_1, int i_2, int j_2,
                             double *input_matrix_1, double *input_matrix_2,
                             double *expected_matrix) {
  test_data *test_data = malloc(sizeof(*test_data));

  s21_create_matrix(i_1, j_1, &test_data->matrix_1);
  s21_create_matrix(i_2, j_2, &test_data->matrix_2);
  s21_create_matrix(i_2, j_2, &test_data->matrix_res);
  s21_create_matrix(i_1, j_2, &test_data->expected_matrix);

  set_matrix(&test_data->matrix_1, input_matrix_1);
  set_matrix(&test_data->matrix_2, input_matrix_2);
  set_matrix(&test_data->expected_matrix, expected_matrix);

  return test_data;
}

START_TEST(test_mult_matrix_valid) {
  double input_matrix_1[] = {1, 2, 3, 4, 5, 6};

  double input_matrix_2[] = {7, 8, 9, 10, 11, 12};

  double expected_matrix[] = {58, 64, 139, 154};

  test_data *test_data = setup_mult_matrix(2, 3, 3, 2, input_matrix_1,
                                           input_matrix_2, expected_matrix);

  s21_mult_matrix(&test_data->matrix_1, &test_data->matrix_2,
                  &test_data->matrix_res);

  ck_assert_int_eq(
      s21_eq_matrix(&test_data->expected_matrix, &test_data->matrix_res), 1);

  teardown(test_data);
}
END_TEST

START_TEST(test_mult_matrix_invalid_size) {
  double input_matrix_1[] = {1};

  double input_matrix_2[] = {7, 8, 9, 10, 11, 12};

  double expected_matrix[] = {58, 64, 139, 154};

  test_data *test_data = setup_mult_matrix(1, 1, 3, 2, input_matrix_1,
                                           input_matrix_2, expected_matrix);

  ck_assert_int_eq(s21_mult_matrix(&test_data->matrix_1, &test_data->matrix_2,
                                   &test_data->matrix_res),
                   CALCULATION_ERROR);

  teardown(test_data);
}
END_TEST

Suite *mult_matrix(void) {
  Suite *s = suite_create("test_mult_matrix");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_mult_matrix_valid);
  tcase_add_test(tc, test_mult_matrix_invalid_size);

  suite_add_tcase(s, tc);

  return s;
}