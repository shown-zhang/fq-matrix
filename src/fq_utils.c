#include <math.h>
#include <stdio.h>
#include "../include/fq_utils.h"

void test() { printf("hello world\n"); }

LADEF Vf min(Vf a, Vf b) { return a < b ? a : b; }

LADEF Vf max(Vf a, Vf b) { return a > b ? a : b; }

LADEF Vi equals(Vf a, Vf b) {
    return fabsf(a - b) < EPSILON * max(1.0, max(fabsf(a), fabsf(b)));
}

LADEF Vf deg2rad(Vf deg) { return deg * PI / 180.0; }