#include "test.h"

START_TEST(test_create_success) {
  matrix_t matrix;

  ck_assert_int_eq(s21_create_matrix(2, 3, &matrix), OK);
  s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(test_create_error) {
  matrix_t matrix;

  ck_assert_int_eq(s21_create_matrix(0, 3, &matrix), ERROR);
}
END_TEST

START_TEST(eq_matrix_fail) {
  double input_matrix_1[] = {1, 2, 3, 4, 5, 6};

  double input_matrix_2[] = {7, 8, 9, 10, 11, 12};
  matrix_t matrix_1, matrix_2;
  s21_create_matrix(2, 3, &matrix_1);
  s21_create_matrix(2, 3, &matrix_2);

  set_matrix(&matrix_1, input_matrix_1);
  set_matrix(&matrix_2, input_matrix_2);

  ck_assert_int_eq(s21_eq_matrix(&matrix_1, &matrix_2), FAILURE);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

Suite *create_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("test_create_matrix");

  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_create_success);
  tcase_add_test(tc_core, test_create_error);
  tcase_add_test(tc_core, eq_matrix_fail);

  suite_add_tcase(s, tc_core);

  return s;
}