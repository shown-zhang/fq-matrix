#ifndef CONST_VAR
#define CONST_VAR

typedef int Vi;
typedef float Vf;

#define EPSILON 0.00001
#define LADEF static inline
#define PI 3.141592653589793

#endif

#ifndef FQ_MATRIX_H
#define FQ_MATRIX_H


void test(void);
LADEF Vf min(Vf a, Vf b);
LADEF Vf max(Vf a, Vf b);
LADEF Vi equals(Vf a, Vf b);
LADEF Vf deg2rad(Vf deg);

#endif