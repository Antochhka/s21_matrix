#include "../s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if ((validate_matrix(A) == ERROR) || (validate_matrix(B) == ERROR) ||
      (result == NULL)) {
    return ERROR;
  }

  if (A->rows != B->rows || A->columns != B->columns) {
    return CALCULATION_ERROR;
  }

  int res = OK;

  int rows = A->rows;
  int columns = A->columns;

  s21_create_matrix(rows, columns, result);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double temp = A->matrix[i][j] - B->matrix[i][j];
      if (!isfinite(temp)) {
        res = CALCULATION_ERROR;
      }

      result->matrix[i][j] = temp;
    }
  }

  return res;
}
