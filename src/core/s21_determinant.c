#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  if (validate_matrix(A) == ERROR) {
    return ERROR;
  }

  if (A->rows != A->columns) {
    return CALCULATION_ERROR;
  }

  int size = A->rows;

  if (size == 1) {
    *result = A->matrix[0][0];
  } else if (size == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    *result = 0.0;
    for (int j = 0; j < size; j++) {
      matrix_t minor;
      s21_create_matrix(size - 1, size - 1, &minor);

      int m_row = 0;
      for (int i = 1; i < size; i++) {
        int m_col = 0;
        for (int k = 0; k < size; k++) {
          if (k != j) {
            minor.matrix[m_row][m_col++] = A->matrix[i][k];
          }
        }
        m_row++;
      }

      double minor_det = 0.0;
      s21_determinant(&minor, &minor_det);

      *result += pow(-1, j) * A->matrix[0][j] * minor_det;

      s21_remove_matrix(&minor);
    }
  }

  return OK;
}