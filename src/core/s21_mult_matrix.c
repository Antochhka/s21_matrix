#include "../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (validate_matrix(A) == ERROR || validate_matrix(B) == ERROR ||
      result == NULL) {
    return ERROR;
  }

  if (A->columns != B->rows) {
    return CALCULATION_ERROR;
  }

  int res = OK;

  int rows = A->rows;
  int columns = B->columns;

  s21_create_matrix(rows, columns, result);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
      if (!isfinite(result->matrix[i][j])) {
        res = CALCULATION_ERROR;
      }
    }
  }

  return res;
}
