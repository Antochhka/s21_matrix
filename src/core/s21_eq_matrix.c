#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (validate_matrix(A) == ERROR || validate_matrix(B) == ERROR ||
      A->rows != B->rows || A->columns != B->columns) {
    return FAILURE;
  }

  int result = SUCCESS;

  int rows = A->rows;
  int columns = A->columns;

  double epsilon = 1e-7;

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= epsilon) {
        result = FAILURE;
        break;
      }
    }
  }

  return result;
}
