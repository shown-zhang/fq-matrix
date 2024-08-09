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

void test_mat_find_base(CuTest *tc) {
  for (Vi i = 0; i < 5; i++) {
    for (Vi j = 0; j < 5; j++) {
      Vi length = i * j;
      Vf *data = (Vf *)malloc(length * sizeof(Vf));

      for (Vi k = 0; k < length; k++) {
        data[k] = (Vf)rand() / RAND_MAX;
      }

      Matrix *mat = mat_create(i, j, 0.0);
      setMatrix(mat, data, length);
      for (Vi k = 0; k < i; k++) {
        for (Vi l = 0; l < j; l++) {
          CuAssertDblEquals(tc, data[k * j + l], mat_find(mat, k, l), EPSILON);
        }
      }
      mat_destroy(mat);
      free(data);
    }
  }
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
  for (Vi i = 0; i < 5; i++) {
    for (Vi j = 0; j < 5; j++) {
      Vi length = i * j;
      Vf *data = (Vf *)malloc(length * sizeof(Vf));

      for (Vi k = 0; k < length; k++) {
        data[k] = (Vf)rand() / RAND_MAX;
      }

      Matrix *mat = mat_create(i, j, 0.0);
      setMatrix(mat, data, length);
      Matrix *out = transpose(mat);

      if (i * j <= 0) {
        CuAssertPtrEquals(tc, NULL, out);
      } else {
        CuAssertIntEquals(tc, j, out->row);
        CuAssertIntEquals(tc, i, out->col);
        for (Vi k = 0; k < i; k++) {
          for (Vi l = 0; l < j; l++) {
            CuAssertDblEquals(tc, mat_find(mat, k, l), mat_find(out, l, k),
                              EPSILON);
          }
        }
      }
      mat_destroy(out);
      mat_destroy(mat);
      free(data);
    }
  }
}

void test_cofactor_base(CuTest *tc) {
  Matrix *mat;
  Matrix *out;
  Vf *data;
  for (Vi i = 0; i < 5; i++) {
    for (Vi j = 0; j < 5; j++) {
      Vi length = i * j;
      data = (Vf *)malloc(length * sizeof(Vf));

      for (Vi k = 0; k < length; k++) {
        data[k] = (Vf)rand() / RAND_MAX;
      }

      mat = mat_create(i, j, 0.0);
      setMatrix(mat, data, length);
      for (Vi k = 0; k < i; k++) {
        for (Vi l = 0; l < j; l++) {
          out = cofactor(mat, k, l);

          if (i * j <= 0 || out == NULL) {
            CuAssertPtrEquals(tc, NULL, out);
          } else {
            CuAssertIntEquals(tc, i - 1, out->row);
            CuAssertIntEquals(tc, j - 1, out->col);
            for (Vi m = 0; m < i; m++) {
              for (Vi n = 0; n < j; n++) {
                if (m == k || n == l) {
                  continue;
                } else {
                  Vi x = m < k ? m : m - 1;
                  Vi y = n < l ? n : n - 1;
                  CuAssertDblEquals(tc, mat_find(mat, m, n),
                                    mat_find(out, x, y), EPSILON);
                }
              }
            }
          }

          mat_destroy(out);
        }
      }
      mat_destroy(mat);
      free(data);
    }
  }
}

void test_determinant_base(CuTest *tc) {
  // Test 2x2 matrix
  Matrix *mat = mat_create(2, 2, 0.0);
  Vf data[4] = {1, 2, 3, 4};
  setMatrix(mat, data, 4);
  CuAssertDblEquals(tc, -2.0, determinant(mat), EPSILON);
  mat_destroy(mat);

  // Test 3x3 matrix
  mat = mat_create(3, 3, 0.0);
  Vf data2[9] = {0, 3, 1, 2, 5, 9, 3, 6, 7};
  setMatrix(mat, data2, 9);
  CuAssertDblEquals(tc, 36, determinant(mat), EPSILON);
  mat_destroy(mat);

  // Test 4x4 matrix
  mat = mat_create(4, 4, 0.0);
  Vf data3[16] = {1, 2, 3, 4, 52, 6, 72, 8, 9, 11, 11, 12, 13, 14, 15, 16};
  setMatrix(mat, data3, 16);
  CuAssertDblEquals(tc, 1776, determinant(mat), EPSILON);
  mat_destroy(mat);
}

void test_adjoint_base(CuTest *tc) {
  // Test 2x2 matrix
  Matrix *mat = mat_create(2, 2, 0.0);
  Vf data[4] = {1, 2, 3, 4};
  setMatrix(mat, data, 4);
  Matrix *out = adjoint(mat);
  CuAssertIntEquals(tc, 2, out->row);
  CuAssertIntEquals(tc, 2, out->col);
  CuAssertDblEquals(tc, 4, out->data[0], EPSILON);
  CuAssertDblEquals(tc, -2, out->data[1], EPSILON);
  CuAssertDblEquals(tc, -3, out->data[2], EPSILON);
  CuAssertDblEquals(tc, 1, out->data[3], EPSILON);
  mat_destroy(mat);
  mat_destroy(out);

  // Test 3x3 matrix
  mat = mat_create(3, 3, 0.0);
  Vf data2[9] = {0, 1, 1, 2, 2, 1, 0, 0, 1};
  setMatrix(mat, data2, 9);
  out = adjoint(mat);
  CuAssertIntEquals(tc, 3, out->row);
  CuAssertIntEquals(tc, 3, out->col);
  CuAssertDblEquals(tc, 2, out->data[0], EPSILON);
  CuAssertDblEquals(tc, -1, out->data[1], EPSILON);
  CuAssertDblEquals(tc, -1, out->data[2], EPSILON);
  CuAssertDblEquals(tc, -2, out->data[3], EPSILON);
  CuAssertDblEquals(tc, 0, out->data[4], EPSILON);
  CuAssertDblEquals(tc, 2, out->data[5], EPSILON);
  CuAssertDblEquals(tc, 0, out->data[6], EPSILON);
  CuAssertDblEquals(tc, 0, out->data[7], EPSILON);
  CuAssertDblEquals(tc, -2, out->data[8], EPSILON);
  mat_destroy(mat);
  mat_destroy(out);
}

void test_inverse_base(CuTest *tc) {
  // Test 2x2 matrix
  Matrix *mat = mat_create(2, 2, 0.0);
  Vf data[4] = {1, 2, 3, 4};
  setMatrix(mat, data, 4);
  Matrix *out = inverse(mat);
  CuAssertIntEquals(tc, 2, out->row);
  CuAssertIntEquals(tc, 2, out->col);
  CuAssertDblEquals(tc, -2, out->data[0], EPSILON);
  CuAssertDblEquals(tc, 1, out->data[1], EPSILON);
  CuAssertDblEquals(tc, 1.5, out->data[2], EPSILON);
  CuAssertDblEquals(tc, -0.5, out->data[3], EPSILON);
  mat_destroy(mat);
  mat_destroy(out);

  // Test 3x3 matrix
  mat = mat_create(3, 3, 0.0);
  Vf data2[9] = {0, 3, 1, 2, 5, 9, 3, 6, 7};
  setMatrix(mat, data2, 9);
  out = inverse(mat);
  CuAssertIntEquals(tc, 3, out->row);
  CuAssertIntEquals(tc, 3, out->col);
  CuAssertDblEquals(tc, -0.527778, out->data[0], EPSILON);
  CuAssertDblEquals(tc, -0.4166666666666667, out->data[1], EPSILON);
  CuAssertDblEquals(tc, 0.6111111111111112, out->data[2], EPSILON);
  CuAssertDblEquals(tc, 0.3611111111111111, out->data[3], EPSILON);
  CuAssertDblEquals(tc, -0.08333333333333333, out->data[4], EPSILON);
  CuAssertDblEquals(tc, 0.05555555555555555, out->data[5], EPSILON);
  CuAssertDblEquals(tc, -0.08333333333333333, out->data[6], EPSILON);
  CuAssertDblEquals(tc, 0.25, out->data[7], EPSILON);
  CuAssertDblEquals(tc, -0.16666666666666666, out->data[8], EPSILON);
  mat_destroy(mat);
  mat_destroy(out);
}

CuSuite *FqMatrixGetSuite() {
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, test_mat_create_base);
  SUITE_ADD_TEST(suite, test_mat_destroy_base);
  SUITE_ADD_TEST(suite, test_mat_find_base);
  SUITE_ADD_TEST(suite, test_identity_base);
  SUITE_ADD_TEST(suite, test_clone_base);
  SUITE_ADD_TEST(suite, test_copy_base);
  SUITE_ADD_TEST(suite, test_setMatrix_base);
  SUITE_ADD_TEST(suite, test_transpose_base);
  SUITE_ADD_TEST(suite, test_cofactor_base);
  SUITE_ADD_TEST(suite, test_determinant_base);
  SUITE_ADD_TEST(suite, test_adjoint_base);
  SUITE_ADD_TEST(suite, test_inverse_base);
  return suite;
}