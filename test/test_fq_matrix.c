#include "../include/fq_matrix.h"
#include "CuTest.h"
#include "stdio.h"

void test_mat_create(CuTest *tc) {
  for (Vi i = 0; i < 5; i++) {
    for (Vi j = 0; j < 5; j++) {
      Matrix *mat = mat_create(i, j, 0.0);
      if (i * j < 2 || i * j > 16) {
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

CuSuite *FqMatrixGetSuite() {
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, test_mat_create);
  return suite;
}