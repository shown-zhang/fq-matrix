#ifndef CONST_VAR
#define CONST_VAR

typedef short Vi;
typedef float Vf;
typedef struct {
  Vi col;
  Vi row;
  Vf *data;
} Matrix;

#define EPSILON 0.00001
#define LADEF 
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

#endif