#include "../s21_matrix.h"

double get_minor_determinant(matrix_t *matrix, int row, int column) {
  matrix_t minor_matrix;
  s21_create_matrix(matrix->rows - 1, matrix->columns - 1, &minor_matrix);

  int m_row = 0, m_col;
  for (int i = 0; i < matrix->rows; i++) {
    if (i != row) {
      m_col = 0;
      for (int j = 0; j < matrix->columns; j++) {
        if (j != column)
          minor_matrix.matrix[m_row][m_col++] = matrix->matrix[i][j];
      }
    }
    if (i != row) {
      m_row++;
    }
  }

  double result = 0.0;
  s21_determinant(&minor_matrix, &result);
  s21_remove_matrix(&minor_matrix);

  return result;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (validate_matrix(A) == ERROR || result == NULL) {
    return ERROR;
  }

  if (validate_matrix(A) == ERROR || A->rows != A->columns) {
    return CALCULATION_ERROR;
  }

  s21_create_matrix(A->rows, A->columns, result);

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      double minor_det = get_minor_determinant(A, i, j);
      result->matrix[i][j] = pow(-1, i + j) * minor_det;
    }
  }

  return OK;
}