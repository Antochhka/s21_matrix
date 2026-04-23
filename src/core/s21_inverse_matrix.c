#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if ((validate_matrix(A) == ERROR) || result == NULL) {
    return ERROR;
  }

  double det;

  double eps = 1e-7;

  if (s21_determinant(A, &det) != OK || fabs(det) < eps) {
    return CALCULATION_ERROR;
  }

  s21_create_matrix(A->rows, A->columns, result);

  if (A->rows == 1) {
    result->matrix[0][0] = 1 / A->matrix[0][0];
  } else {
    matrix_t matrix_calc_complements, transpose_matrix;

    s21_calc_complements(A, &matrix_calc_complements);
    s21_transpose(&matrix_calc_complements, &transpose_matrix);

    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = transpose_matrix.matrix[i][j] / det;
      }
    }

    s21_remove_matrix(&matrix_calc_complements);
    s21_remove_matrix(&transpose_matrix);
  }

  return OK;
}
