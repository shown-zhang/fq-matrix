/**
This file contains basic test cases for the functions in fq_matrix.c.
For details on how to execute/add test cases, please refer to the README
**/

#include "../include/fq_matrix.h"
#include "CuTest.h"
#include "stdio.h"
#include "stdlib.h"

void test_mat_create_base(CuTest *tc) {
  for (Vi i = 0; i < 5; i++) {
    for (Vi j = 0; j < 5; j++) {
      Matrix *mat = mat_create(i, j, 0.0);
      if (i * j <= 0) {
        CuAssertPtrEquals(tc, NULL, mat);
      } else {
        CuAssertIntEquals(tc, i, mat->row);
        CuAssertIntEquals(tc, j, mat->col);
        for (Vi k = 0; k < i * j; k++) {
          CuAssertDblEquals(tc, 0.0, mat->data[k], EPSILON);
        }
        mat_destroy(mat);
      }
    }
  }
}

void test_mat_destroy_base(CuTest *tc) {
  Matrix *mat = mat_create(2, 2, 0.0);
  CuAssertIntEquals(tc, 0, mat_destroy(mat));
}

void test_identity_base(CuTest *tc) {
  for (Vi i = 0; i < 5; i++) {
    for (Vi j = 0; j < 5; j++) {
      Matrix *mat = mat_create(i, j, 0.0);
      identity(mat);
      if (i * j <= 0) {
        CuAssertPtrEquals(tc, NULL, mat);
      } else if (i != j || i < 2 || i > 4) {
        for (Vi k = 0; k < i * j; k++) {
          CuAssertDblEquals(tc, 0.0, mat->data[k], EPSILON);
        }
      } else {
        for (Vi k = 0; k < i * j; k++) {
          if (k % (i + 1) == 0) {
            CuAssertDblEquals(tc, 1.0, mat->data[k], EPSILON);
          } else {
            CuAssertDblEquals(tc, 0.0, mat->data[k], EPSILON);
          }
        }
      }
      mat_destroy(mat);
    }
  }
}

void test_clone_base(CuTest *tc) {
  for (Vi i = 0; i < 5; i++) {
    for (Vi j = 0; j < 5; j++) {
      Vi random = i * j;
      Matrix *mat = mat_create(i, j, random);
      Matrix *out = clone(mat);
      if (i * j <= 0) {
        CuAssertPtrEquals(tc, NULL, out);
      } else {
        CuAssertIntEquals(tc, i, out->row);
        CuAssertIntEquals(tc, j, out->col);
        for (Vi k = 0; k < i * j; k++) {
          CuAssertDblEquals(tc, random, out->data[k], EPSILON);
        }
        mat_destroy(out);
        mat_destroy(mat);
      }
    }
  }
}

void test_copy_base(CuTest *tc) {
  for (Vi i = 0; i < 5; i++) {
    for (Vi j = 0; j < 5; j++) {
      Vi random = i * j;
      Matrix *mat = mat_create(i, j, random);
      Matrix *out = mat_create(i, j, 0.0);
      copy(out, mat);
      if (i * j <= 0) {
        CuAssertPtrEquals(tc, NULL, out);
      } else {
        CuAssertIntEquals(tc, i, out->row);
        CuAssertIntEquals(tc, j, out->col);
        for (Vi k = 0; k < i * j; k++) {
          CuAssertDblEquals(tc, random, out->data[k], EPSILON);
        }
      }
      mat_destroy(out);
      mat_destroy(mat);
    }
  }
}

void test_setMatrix_base(CuTest *tc) {
  for (Vi i = 0; i < 5; i++) {
    for (Vi j = 0; j < 5; j++) {
      Vi length = i * j;
      Vf *data = (Vf *)malloc(length * sizeof(Vf));

      for (Vi k = 0; k < length; k++) {
        data[k] = (Vf)rand() / RAND_MAX;
      }

      Matrix *mat = mat_create(i, j, 0.0);
      setMatrix(mat, data, length);
      if (i * j <= 0) {
        CuAssertPtrEquals(tc, NULL, mat);
      } else {
        CuAssertIntEquals(tc, i, mat->row);
        CuAssertIntEquals(tc, j, mat->col);
        for (Vi k = 0; k < length; k++) {
          CuAssertDblEquals(tc, data[k], mat->data[k], EPSILON);
        }
      }
      mat_destroy(mat);
      free(data);
    }
  }
}

void test_transpose_base(CuTest *tc) {
  Vi length = 12;
  Vf *data = (Vf *)malloc(length * sizeof(Vf));
  for (Vi k = 0; k < length; k++) {
    data[k] = (Vf)rand() / RAND_MAX;
  }

  Matrix *mat = mat_create(3, 4, 0.0);
  setMatrix(mat, data, length);
  Matrix *out = transpose(mat);
  if (length <= 0) {
    CuAssertPtrEquals(tc, NULL, out);
  } else {
    CuAssertIntEquals(tc, 4, out->row);
    CuAssertIntEquals(tc, 3, out->col);
    for (Vi r = 0; r < mat->row; r++) {
      for (Vi l = 0; l < mat->col; l++) {
        CuAssertDblEquals(tc, mat->data[r * mat->row + l],
                          out->data[l * out->row + r], EPSILON);
      }
    }
  }
  mat_destroy(out);
  mat_destroy(mat);
  free(data);
}

CuSuite *FqMatrixGetSuite() {
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, test_mat_create_base);
  SUITE_ADD_TEST(suite, test_mat_destroy_base);
  SUITE_ADD_TEST(suite, test_identity_base);
  SUITE_ADD_TEST(suite, test_clone_base);
  SUITE_ADD_TEST(suite, test_copy_base);
  SUITE_ADD_TEST(suite, test_setMatrix_base);
  SUITE_ADD_TEST(suite, test_transpose_base);
  return suite;
}