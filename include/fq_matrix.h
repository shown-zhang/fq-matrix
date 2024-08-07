#include "fq_utils.h"
#ifndef FQ_MATRIX_H
#define FQ_MATRIX_H

Matrix *mat_create(Vi row, Vi col, Vf fill);
Vi mat_destroy(Matrix *mat);
void identity(Matrix *mat);
Matrix *clone(const Matrix * const mat);
void copy(Matrix *dest, const Matrix *const src);
void setMatrix(Matrix *mat, Vf *data, Vi length);
Matrix *transpose(Matrix mat);

Matrix *cofactor(const Matrix *const mat, Vi row, Vi col);
Matrix *adjoint(const Matrix *const mat);
Vf determinant(const Matrix *const mat);
Matrix *inverse(const Matrix *const mat);

void printMatrix(const Matrix *const mat);
#endif