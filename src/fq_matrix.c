#include "../include/fq_matrix.h"
#include <assert.h>
#include <stdlib.h>

void identity(Matrix *mat) {
  assert(mat != NULL);
  assert(mat->data != NULL);
  assert(mat->width == mat->height);
  assert(mat->width >= 2 && mat->width <= 4);

  for (Vi i = 0; i < mat->width; i++) {
    for (Vi j = 0; j < mat->height; j++) {
      if (i == j) {
        mat->data[j * mat->height + i] = 1;
      }
    }
  }
}

Matrix *clone(const Matrix *const mat) {
  if (mat == NULL || mat->data == NULL) {
    return NULL;
  }

  assert(mat->width >= 2 && mat->width <= 4);
  assert(mat->height >= 2 && mat->height <= 4);

  Matrix *out = mat_create(mat->width, mat->height, 0);

  if (out == NULL) {
    return NULL;
  }

  for (Vi i = 0; i < mat->width; i++) {
    for (Vi j = 0; j < mat->height; j++) {
      out->data[j * out->height + i] = mat->data[j * mat->height + i];
    }
  }
  return out;
}

void copy(Matrix *dest, const Matrix *const src) {
  assert(src != NULL);
  assert(dest != NULL);
  assert(dest->data != NULL);
  assert(src->data != NULL);
  assert(dest->width == src->width);
  assert(dest->height == src->height);

  for (Vi i = 0; i < dest->width; i++) {
    for (Vi j = 0; j < dest->height; j++) {
      dest->data[j * dest->height + i] = src->data[j * src->height + i];
    }
  }
}

void setMatrix(Matrix *mat, Vf *data, Vi length) {
  assert(mat != NULL);
  assert(data != NULL);
  assert(mat->data != NULL);
  assert(mat->width != 0 && mat->height != 0);
  assert(mat->width * mat->height <= length);

  for (Vi i = 0; i < mat->width; i++) {
    for (Vi j = 0; j < mat->height; j++) {
      mat->data[j * mat->height + i] = data[j * mat->height + i];
    }
  }
}

Matrix *transpose(Matrix mat) {
  assert(mat.data != NULL);
  assert(mat.width >= 2 && mat.width <= 4);
  assert(mat.height >= 2 && mat.height <= 4);

  Matrix *out = mat_create(mat.height, mat.width, 0);

  if (out == NULL) {
    return NULL;
  }

  for (int i = 0; i < mat.width; i++) {
    for (int j = 0; j < mat.height; j++) {
      out->data[i * out->height + j] = mat.data[j * mat.height + i];
    }
  }
  return out;
}

Matrix *cofactor(const Matrix *const mat, Vi row, Vi col) {
  assert(mat != NULL);
  assert(mat->data != NULL);
  assert(mat->width >= 2 && mat->width <= 4);
  assert(mat->height >= 2 && mat->height <= 4);
  assert(row >= 0 && row < mat->height);
  assert(col >= 0 && col < mat->width);

  Matrix *out = mat_create(mat->width - 1, mat->height - 1, 0);

  if (out == NULL) {
    return NULL;
  }

  int x = 0;
  int y = 0;
  for (int i = 0; i < mat->width; i++) {
    if (i == col) {
      continue;
    }
    y = 0;
    for (int j = 0; j < mat->height; j++) {
      if (j == row) {
        continue;
      }
      out->data[y * out->height + x] = mat->data[j * mat->height + i];
      y++;
    }
    x++;
  }
  return out;
}

Vf determinant(const Matrix *const mat) {
  assert(mat != NULL);
  assert(mat->data != NULL);
  assert(mat->width >= 2 && mat->width <= 4);
  assert(mat->height >= 2 && mat->height <= 4);
  assert(mat->width == mat->height);

  if (mat->width == 2) {
    return mat->data[0] * mat->data[3] - mat->data[1] * mat->data[2];
  }

  Vf det = 0;
  for (int i = 0; i < mat->width; i++) {
    Matrix *cof = cofactor(mat, 0, i);
    det += mat->data[i] * determinant(cof) * (i % 2 == 0 ? 1 : -1);
    mat_destroy(cof);
  }
  return det;
}

Matrix *adjoint(const Matrix *const mat) {
  assert(mat != NULL);
  assert(mat->data != NULL);
  assert(mat->width >= 2 && mat->width <= 4);
  assert(mat->height >= 2 && mat->height <= 4);

  Matrix *out = mat_create(mat->width, mat->height, 0);

  if (out == NULL) {
    return NULL;
  }

  for (int i = 0; i < mat->width; i++) {
    for (int j = 0; j < mat->height; j++) {
      Matrix *cof = cofactor(mat, j, i);
      // Transpose the cofactor matrix ?
      out->data[j * out->height + i] =
          determinant(cof) * ((i + j) % 2 == 0 ? 1 : -1);
      mat_destroy(cof);
    }
  }
  return out;
}

Matrix *inverse(const Matrix *const mat) {
  assert(mat != NULL);
  assert(mat->data != NULL);
  assert(mat->width >= 2 && mat->width <= 4);
  assert(mat->height >= 2 && mat->height <= 4);
  assert(mat->width == mat->height);

  Vf det = determinant(mat);
  if (det == 0) {
    return NULL;
  }

  Matrix *adj = adjoint(mat);
  if (adj == NULL) {
    return NULL;
  }

  Matrix *out = mat_create(mat->width, mat->height, 0);
  if (out == NULL) {
    mat_destroy(adj);
    return NULL;
  }

  for (Vi i = 0; i < mat->width; i++) {
    for (Vi j = 0; j < mat->height; j++) {
      out->data[j * out->height + i] = adj->data[j * adj->height + i] / det;
    }
  }

  mat_destroy(adj);
  return out;
}