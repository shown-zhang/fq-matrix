#include "../include/fq_matrix.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

Matrix *mat_create(Vi row, Vi col, Vf fill) {
  Vi length = row * col;
  if (length <= 0) {
    return NULL;
  }

  Matrix *mat = (Matrix *)malloc(sizeof(Matrix));

  if (mat == NULL) {
    return NULL;
  }

  mat->row = row;
  mat->col = col;
  mat->data = (Vf *)malloc(sizeof(Vf) * length);

  if (mat->data == NULL) {
    free(mat);
    return NULL;
  }

  for (Vi i = 0; i < length; i++) {
    mat->data[i] = fill;
  }
  return mat;
}

Vi mat_destroy(Matrix *mat) {
  if (mat == NULL) {
    return -1;
  }

  free(mat->data);
  mat->data = NULL;
  free(mat);
  mat = NULL;
  return 0;
}

Vf mat_find(const Matrix *const mat, Vi row, Vi col) {
  if (mat == NULL || mat->data == NULL) {
    return 0;
  }

  if (row < 0 || row >= mat->row) {
    return 0;
  }

  if (col < 0 || col >= mat->col) {
    return 0;
  }

  return mat->data[row * mat->col + col];
}

void identity(Matrix *mat) {
  if (mat == NULL || mat->data == NULL) {
    return;
  }

  if (mat->row != mat->col) {
    return;
  }

  if (mat->row < 2 || mat->row > 4) {
    return;
  }

  for (Vi i = 0; i < mat->row; i++) {
    for (Vi j = 0; j < mat->col; j++) {
      if (i == j) {
        mat->data[i * mat->row + j] = 1;
      }
    }
  }
}

Matrix *clone(const Matrix *const mat) {
  if (mat == NULL || mat->data == NULL) {
    return NULL;
  }

  Vi length = mat->col * mat->row;

  if (length <= 0) {
    return NULL;
  }

  Matrix *out = mat_create(mat->row, mat->col, 0);

  if (out == NULL) {
    return NULL;
  }

  for (Vi i = 0; i < length; i++) {
    out->data[i] = mat->data[i];
  }
  return out;
}

void copy(Matrix *dest, const Matrix *const src) {
  if (dest == NULL || src == NULL) {
    return;
  }

  if (dest->data == NULL || src->data == NULL) {
    return;
  }

  if (dest->row != src->row || dest->col != src->col) {
    return;
  }

  Vi length = dest->row * dest->col;

  for (Vi i = 0; i < length; i++) {
    dest->data[i] = src->data[i];
  }
}

void setMatrix(Matrix *mat, Vf *data, Vi length) {
  if (mat == NULL) {
    return;
  }

  if (mat->data == NULL || data == NULL) {
    return;
  }

  if (length <= 0 || mat->row * mat->col > length) {
    return;
  }

  for (Vi i = 0; i < mat->row * mat->col; i++) {
    mat->data[i] = data[i];
  }
}

Matrix *transpose(Matrix *mat) {
  if (mat == NULL || mat->data == NULL) {
    return NULL;
  }

  if (mat->row <= 0 || mat->row <= 0) {
    return NULL;
  }

  Matrix *out = mat_create(mat->col, mat->row, 0);

  if (out == NULL) {
    return NULL;
  }

  for (Vi i = 0; i < out->row; i++) {
    for (Vi j = 0; j < out->col; j++) {
      out->data[i * out->col + j] = mat_find(mat, j, i);
    }
  }
  return out;
}

Matrix *cofactor(const Matrix *const mat, Vi row, Vi col) {
  if (mat == NULL || mat->data == NULL) {
    return NULL;
  }

  if (mat->row * mat->col <= 0) {
    return NULL;
  }

  if (row < 0 || row >= mat->row || col < 0 || col >= mat->col) {
    return NULL;
  }

  Matrix *out = mat_create(mat->row - 1, mat->col - 1, 0);

  if (out == NULL) {
    return NULL;
  }

  Vi x = 0;
  Vi y = 0;
  for (Vi i = 0; i < mat->row; i++) {
    if (i == row) {
      continue;
    }
    y = 0;
    for (Vi j = 0; j < mat->col; j++) {
      if (j == col) {
        continue;
      }
      out->data[x * out->col + y] = mat_find(mat, i, j);
      y++;
    }
    x++;
  }
  return out;
}

Vf determinant(const Matrix *const mat) {
  if (mat == NULL || mat->data == NULL) {
    return 0;
  }

  if (mat->row != mat->col) {
    return 0;
  }

  if (mat->row < 1) {
    return 0;
  }

  if (mat->row == 1) {
    return mat->data[0];
  }

  if (mat->row == 2) {
    return mat->data[0] * mat->data[3] - mat->data[1] * mat->data[2];
  }

  Vf det = 0;
  for (Vi i = 0; i < mat->col; i++) {
    Matrix *cof = cofactor(mat, 0, i);
    det += mat->data[i] * determinant(cof) * (i % 2 == 0 ? 1 : -1);
    mat_destroy(cof);
  }
  return det;
}

Matrix *adjoint(const Matrix *const mat) {
  if (mat == NULL) {
    return NULL;
  }

  if (mat->data == NULL) {
    return NULL;
  }

  if (mat->row != mat->col) {
    return NULL;
  }

  if (mat->row < 2) {
    return NULL;
  }

  Matrix *out = mat_create(mat->row, mat->col, 0);

  if (out == NULL) {
    return NULL;
  }

  for (Vi i = 0; i < mat->row; i++) {
    for (Vi j = 0; j < mat->col; j++) {
      Matrix *cof = cofactor(mat, i, j);
      out->data[i * out->col + j] =
          determinant(cof) * ((i + j) % 2 == 0 ? 1 : -1);
      mat_destroy(cof);
    }
  }
  return transpose(out);
}

Matrix *inverse(const Matrix *const mat) {
  if (mat == NULL || mat->data == NULL) {
    return NULL;
  }

  if (mat->row != mat->col) {
    return NULL;
  }

  if (mat->row < 2) {
    return NULL;
  }

  Vf det = determinant(mat);
  if (det == 0) {
    return NULL;
  }

  det = 1 / det;

  Matrix *adj = adjoint(mat);
  if (adj == NULL) {
    return NULL;
  }

  Matrix *out = mat_create(mat->row, mat->col, 0);
  if (out == NULL) {
    mat_destroy(adj);
    return NULL;
  }

  for (Vi i = 0; i < mat->row; i++) {
    for (Vi j = 0; j < mat->col; j++) {
      out->data[i * mat->col + j] = mat_find(adj, i, j) * det;
    }
  }

  mat_destroy(adj);
  return out;
}

void printMatrix(const Matrix *const mat) {
  if (mat == NULL) {
    printf("ERROR: Matrix is NULL\n");
    return;
  } else if (mat->data == NULL) {
    printf("ERROR: Matrix data is NULL\n");
    return;
  } else if (mat->row == 0 || mat->col == 0) {
    printf("ERROR: Matrix is empty\n");
    return;
  }

  printf("Matrix: %d x %d\n", mat->row, mat->col);

  printf("[\n");
  for (Vi i = 0; i < mat->row; i++) {
    for (Vi j = 0; j < mat->col; j++) {
      printf("\t%f ", mat->data[i * mat->row + j]);
    }
    printf("\n");
  }
  printf("]\n");
}