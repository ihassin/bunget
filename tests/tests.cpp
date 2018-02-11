#ifndef TESTCASES_H
#include "testcases.h"
#endif

int __alive;

CuSuite *CuGetSuite(void)
{
  CuSuite *suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, canary);
  SUITE_ADD_TEST(suite, server_test);
  SUITE_ADD_TEST(suite, uguid16_test);
  SUITE_ADD_TEST(suite, uguid32_test);
  SUITE_ADD_TEST(suite, uguid128_test);

  return suite;
}
