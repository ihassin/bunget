#include <stdio.h>

#ifndef CU_TEST_H
#include "cutest.h"
#endif

#undef DEBUG
#include <log4cpp/Category.hh>
#include <log4cpp/PropertyConfigurator.hh>

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
  log4cpp::PropertyConfigurator::configure("log4cpp.properties");
  log4cpp::Category& rootLog = log4cpp::Category::getRoot();
  log4cpp::Category& mainLog = log4cpp::Category::getInstance(std::string("main"));

  RunAllTests();
}
