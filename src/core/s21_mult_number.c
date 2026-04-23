#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if ((validate_matrix(A) == ERROR) || result == NULL) {
    return ERROR;
  }

  int rows = A->rows;
  int columns = A->columns;

  int res = OK;

  s21_create_matrix(rows, columns, result);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      double temp = A->matrix[i][j] * number;
      if (!isfinite(temp)) {
        res = CALCULATION_ERROR;
      }

      result->matrix[i][j] = temp;
    }
  }

  return res;
}