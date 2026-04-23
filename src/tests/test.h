#ifndef TESTS_TEST_H
#define TESTS_TEST_H

#include <check.h>
#include "../s21_matrix.h"
#include "../core/s21_helpers.h"

typedef struct test_data {
    matrix_t matrix_1;
    matrix_t matrix_2;
    matrix_t matrix_res;
    matrix_t expected_matrix;
} test_data;

test_data *setup(int i_1, int j_1, double *input_matrix_1, double *input_matrix_2, double *expected_matrix);

void teardown(test_data *test_data);

#endif
