#include "../include/fq_utils.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void test() { printf("hello world\n"); }

LADEF Vf min(Vf a, Vf b) { return a < b ? a : b; }

LADEF Vf max(Vf a, Vf b) { return a > b ? a : b; }

LADEF Vi equals(Vf a, Vf b) {
  return fabsf(a - b) < EPSILON * max(1.0, max(fabsf(a), fabsf(b)));
}

LADEF Vi exactEquals(Vi a, Vi b) { return a == b; }

LADEF Vf deg2rad(Vf deg) { return deg * PI / 180.0; }
