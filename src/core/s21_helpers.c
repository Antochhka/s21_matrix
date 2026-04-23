#include "../s21_matrix.h"

void set_matrix(matrix_t *set_matrix, double *input_matrix) {
  for (int i = 0; i < set_matrix->rows; i++) {
    for (int j = 0; j < set_matrix->columns; j++) {
      set_matrix->matrix[i][j] = input_matrix[i * set_matrix->columns + j];
    }
  }
}

int validate_matrix(matrix_t *A) {
  int result = OK;

  if (A == NULL || A->matrix == NULL || A->rows < 1 || A->columns < 1) {
    result = ERROR;
  }

  return result;
}
