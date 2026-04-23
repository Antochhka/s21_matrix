#include "../s21_matrix.h"

/**
 * @brief Функция инициализирует матрицу и выделяет под неё память
 *
 * @param rows Количество строк.
 * @param columns Количество столбцов.
 * @param result Указатель на объект структуры матрицы
 *
 * @return 0 — OK;
 *
 * 1 — ERROR Ошибка, некорректная матрица;
 *
 * 2 — CALCULATION_ERROR Ошибка вычисления (несовпадающие размеры матриц;
 * матрица, для которой нельзя провести вычисления и т. д.).
 */
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows <= 0 || columns <= 0 || result == NULL) {
    return ERROR;
  }

  result->rows = rows;
  result->columns = columns;

  result->matrix = (double **)calloc(rows, sizeof(double *));
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)calloc(columns, sizeof(double));
  }

  return OK;
}
