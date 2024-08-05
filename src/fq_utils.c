#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/fq_utils.h"

void test() { printf("hello world\n"); }

LADEF Vf min(Vf a, Vf b) { return a < b ? a : b; }

LADEF Vf max(Vf a, Vf b) { return a > b ? a : b; }

LADEF Vi equals(Vf a, Vf b) {
    return fabsf(a - b) < EPSILON * max(1.0, max(fabsf(a), fabsf(b)));
}

LADEF Vf deg2rad(Vf deg) { return deg * PI / 180.0; }

Matrix *mat_create(Vi length, Vf fill) {
    assert(length >= 2 && length <= 16);

    Matrix *mat = (Matrix *)malloc(sizeof(Matrix));

    if (mat == NULL) {
        return NULL;
    }

    mat->length = length;
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