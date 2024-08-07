#include "../include/fq_matrix.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

Matrix *mat_create(Vi row, Vi col, Vf fill) {
  Vi length = row * col;
  assert(length >= 2 && length <= 16);

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
  free(mat);
  return 0;
}

void identity(Matrix *mat) {
  assert(mat != NULL);
  assert(mat->data != NULL);
  assert(mat->row == mat->col);
  assert(mat->row >= 2 && mat->row <= 4);

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

  assert(mat->row >= 2 && mat->row <= 4);
  assert(mat->col >= 2 && mat->col <= 4);

  Matrix *out = mat_create(mat->row, mat->col, 0);

  if (out == NULL) {
    return NULL;
  }

  Vi length = mat->col * mat->row;

  for (Vi i = 0; i < length; i++) {
    out->data[i] = mat->data[i];
  }
  return out;
}

void copy(Matrix *dest, const Matrix *const src) {
  assert(src != NULL);
  assert(dest != NULL);
  assert(dest->data != NULL);
  assert(src->data != NULL);
  assert(dest->row == src->row);
  assert(dest->col == src->col);

  Vi length = dest->row * dest->col;

  for (Vi i = 0; i < length; i++) {
    dest->data[i] = src->data[i];
  }
}

void setMatrix(Matrix *mat, Vf *data, Vi length) {
  assert(mat != NULL);
  assert(data != NULL);
  assert(mat->data != NULL);
  assert(mat->row != 0 && mat->row != 0);
  assert(mat->row * mat->row <= length);

  for (Vi i = 0; i < mat->row * mat->row; i++) {
    mat->data[i] = data[i];
  }
}

Matrix *transpose(Matrix mat) {
  assert(mat.data != NULL);
  assert(mat.row >= 2 && mat.row <= 4);
  assert(mat.col >= 2 && mat.col <= 4);

  Matrix *out = mat_create(mat.row, mat.col, 0);

  if (out == NULL) {
    return NULL;
  }

  for (Vi i = 0; i < mat.row; i++) {
    for (Vi j = 0; j < mat.col; j++) {
      out->data[i * mat.row + j] = mat.data[j * mat.row + i];
    }
  }
  return out;
}

Matrix *cofactor(const Matrix *const mat, Vi row, Vi col) {
  assert(mat != NULL);
  assert(mat->data != NULL);
  assert(mat->row >= 2 && mat->row <= 4);
  assert(mat->col >= 2 && mat->col <= 4);
  assert(row >= 0 && row < mat->row);
  assert(col >= 0 && col < mat->col);

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
      out->data[x * mat->row + y] = mat->data[i * mat->row + j];
      y++;
    }
    x++;
  }
  return out;
}

Vf determinant(const Matrix *const mat) {
  assert(mat != NULL);
  assert(mat->data != NULL);
  assert(mat->row >= 2 && mat->row <= 4);
  assert(mat->row == mat->col);

  if (mat->row == 2) {
    return mat->data[0] * mat->data[3] - mat->data[1] * mat->data[2];
  }

  Vf det = 0;
  for (Vi i = 0; i < mat->row; i++) {
    Matrix *cof = cofactor(mat, 0, i);
    det += mat->data[i] * determinant(cof) * (i % 2 == 0 ? 1 : -1);
    mat_destroy(cof);
  }
  return det;
}

Matrix *adjoint(const Matrix *const mat) {
  assert(mat != NULL);
  assert(mat->data != NULL);
  assert(mat->row >= 2 && mat->row <= 4);
  assert(mat->row >= 2 && mat->row <= 4);

  Matrix *out = mat_create(mat->row, mat->col, 0);

  if (out == NULL) {
    return NULL;
  }

  for (Vi i = 0; i < mat->row; i++) {
    for (Vi j = 0; j < mat->col; j++) {
      Matrix *cof = cofactor(mat, i, j);
      out->data[i * out->row + j] =
          determinant(cof) * ((i + j) % 2 == 0 ? 1 : -1);
      mat_destroy(cof);
    }
  }
  return transpose(*out);
}

Matrix *inverse(const Matrix *const mat) {
  assert(mat != NULL);
  assert(mat->data != NULL);
  assert(mat->row == mat->col);
  assert(mat->row >= 2 && mat->row <= 4);

  Vf det = determinant(mat);
  if (det == 0) {
    return NULL;
  }

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
      out->data[i * mat->row + j] = adj->data[i * mat->row + j] / det;
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
  } else if (mat->row < 2 || mat->row > 4) {
    printf("ERROR: Matrix row is invalid\n");
    return;
  } else if (mat->col < 2 || mat->col > 4) {
    printf("ERROR: Matrix col is invalid\n");
    return;
  }

  printf("Matrix: %d x %d\n", mat->row, mat->col);

  printf("[");
  for (Vi i = 0; i < mat->row; i++) {
    for (Vi j = 0; j < mat->col; j++) {
      printf("%f ", mat->data[i * mat->row + j]);
    }
    printf("\n");
  }
  printf("]\n");
}