/**
This file contains basic test cases for the functions in fq_utils.c.
For details on how to execute/add test cases, please refer to the README.md
And test functions are named in the format of test_XXX_base or test_XXX_edge.
For example, test_mat_create_base is a test case for the function mat_create.

If you find a new test case, you need to create a new function in the form of
test_XXX_YYY. For example, test_mat_create_withzero is a test case for the
function mat_create in fq_matrix.c with fill = 0.0.

Finally, you need to add new test cases to the suite.
For example, you need to add the following code to the FqMatrixGetSuite
function:
        SUITE_ADD_TEST(suite, test_mat_create_withzero);

You can refer to the test cases in test/test_fq_matrix.c for details.
**/

#include "../include/fq_utils.h"
#include "CuTest.h"
#include "stdio.h"

void test_min(CuTest *tc) {
  CuAssertDblEquals(tc, 1.0, min(1.0, 2.0), EPSILON);
  CuAssertDblEquals(tc, 1.0, min(2.0, 1.0), EPSILON);
  CuAssertDblEquals(tc, 0, min(0, 0), EPSILON);
  CuAssertDblEquals(tc, -1.000003, min(-1.000002, -1.000003), EPSILON);
}

void test_max(CuTest *tc) {
  CuAssertDblEquals(tc, 2.0, max(1.0, 2.0), EPSILON);
  CuAssertDblEquals(tc, 2.0, max(2.0, 1.0), EPSILON);
  CuAssertDblEquals(tc, 0, max(0, 0), EPSILON);
  CuAssertDblEquals(tc, -1.000002, max(-1.000003, -1.000002), EPSILON);
}

void test_equals(CuTest *tc) {
  CuAssertIntEquals(tc, 1, equals(1.0, 1.0));
  CuAssertIntEquals(tc, 1, equals(1.0, 1.0000001));
  CuAssertIntEquals(tc, 0, equals(1.0, 1.0001));
  CuAssertIntEquals(tc, 1, equals(0.0, 0.0));
  CuAssertIntEquals(tc, 1, equals(-1.0, -1.0));
  CuAssertIntEquals(tc, 1, equals(-1.0, -1.0000001));
  CuAssertIntEquals(tc, 0, equals(-1.0, -1.0001));
}

void test_exactEquals(CuTest *tc) {
  CuAssertIntEquals(tc, 1, exactEquals(1, 1));
  CuAssertIntEquals(tc, 0, exactEquals(1, 2));
  CuAssertIntEquals(tc, 1, exactEquals(0, 0));
  CuAssertIntEquals(tc, 1, exactEquals(-1, -1));
  CuAssertIntEquals(tc, 0, exactEquals(-1, -2));
}

void test_deg2rad(CuTest *tc) {
  CuAssertDblEquals(tc, 0.0, deg2rad(0.0), EPSILON);
  CuAssertDblEquals(tc, PI / 2.0, deg2rad(90.0), EPSILON);
  CuAssertDblEquals(tc, PI, deg2rad(180.0), EPSILON);
  CuAssertDblEquals(tc, 3 * PI / 2.0, deg2rad(270.0), EPSILON);
  CuAssertDblEquals(tc, 2 * PI, deg2rad(360.0), EPSILON);
}

CuSuite *FqUtilGetSuite() {
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, test_min);
  SUITE_ADD_TEST(suite, test_max);
  SUITE_ADD_TEST(suite, test_equals);
  SUITE_ADD_TEST(suite, test_exactEquals);
  SUITE_ADD_TEST(suite, test_deg2rad);
  return suite;
}