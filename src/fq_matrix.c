#include "../include/fq_matrix.h"
#include <assert.h>
#include <stdlib.h>

void identity(Matrix *mat) {
  assert(mat != NULL);
  assert(mat->data != NULL);
  assert(mat->width == mat->height);
  assert(mat->width >= 2 && mat->width <= 4);

  for (int i = 0; i < mat->width; i++) {
    for (int j = 0; j < mat->height; j++) {
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

  for (int i = 0; i < mat->width; i++) {
    for (int j = 0; j < mat->height; j++) {
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

  for (int i = 0; i < dest->width; i++) {
    for (int j = 0; j < dest->height; j++) {
      dest->data[j * dest->height + i] = src->data[j * src->height + i];
    }
  }
}

void setMatrix(Matrix *mat, Vf *data, Vi length) {
  assert(mat != NULL);
  assert(data != NULL);
  assert(mat->data != NULL);
  assert(mat->width >= 2 && mat->width <= 4);
  assert(mat->height >= 2 && mat->height <= 4);
  assert(mat->width * mat->height <= length);

  for (int i = 0; i < mat->width; i++) {
    for (int j = 0; j < mat->height; j++) {
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