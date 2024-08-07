#include "CuTest.h"
#include <stdio.h>

CuSuite *FqUtilGetSuite();

void RunAllTests(void) {
  CuString *output = CuStringNew();
  CuSuite *suite = CuSuiteNew();

  CuSuiteAddSuite(suite, FqUtilGetSuite());

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s\n", output->buffer);
}

int main(void) {
  RunAllTests();
  return 0;
}