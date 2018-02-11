#include <stdio.h>

#ifndef CU_TEST_H
#include "cutest.h"
#endif

CuSuite* CuGetSuite();

void RunAllTests(void)
{
  CuString *output = CuStringNew();
  CuSuite* suite = CuSuiteNew();

  CuSuiteAddSuite(suite, CuGetSuite());

  CuSuiteRun(suite);
  
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);

  printf("%s\n", output->buffer);
}

int main(void)
{
    RunAllTests();
}

