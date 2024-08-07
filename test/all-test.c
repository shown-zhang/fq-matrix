#include "CuTest.h"
#include <stdio.h>

CuSuite *FqUtilGetSuite(void);
CuSuite *FqMatrixGetSuite(void);

void RunAllTests(void) {
  CuString *output = CuStringNew();
  CuSuite *suite = CuSuiteNew();

  CuSuiteAddSuite(suite, FqUtilGetSuite());
  CuSuiteAddSuite(suite, FqMatrixGetSuite());

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s", output->buffer);
}

int main(void) {
  RunAllTests();
  return 0;
}