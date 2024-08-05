#include "fq_utils.h"
#ifndef FQ_MATRIX_H
#define FQ_MATRIX_H

void identity(Matrix *mat);
Matrix *clone(const Matrix * const mat);
void copy(Matrix *dest, const Matrix *const src);
void setMatrix(Matrix *mat, Vf *data, Vi length);
Matrix *transpose(Matrix mat);

#endif