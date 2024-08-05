#ifndef CONST_VAR
#define CONST_VAR

typedef int Vi;
typedef float Vf;
typedef struct {
  Vi width;
  Vi height;
  Vf *data;
} Matrix;

#define EPSILON 0.00001
#define LADEF static inline
#define PI 3.141592653589793

#endif

#ifndef FQ_UTILS_H
#define FQ_UTILS_H


void test(void);
LADEF Vf min(Vf a, Vf b);
LADEF Vf max(Vf a, Vf b);
LADEF Vi equals(Vf a, Vf b);
LADEF Vi exactEquals(Vi a, Vi b);
LADEF Vf deg2rad(Vf deg);

Matrix *mat_create(Vi width, Vi height, Vf fill);
Vi mat_destroy(Matrix *mat);

#endif