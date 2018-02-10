#include <assert.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef CU_TEST_H
#include "cutest.h"
#endif

#include "libbunget.h"

int __alive;
void TestPasses(CuTest* tc)
{
  bunget::BtCtx *ctx = bunget::BtCtx::instance();
  CuAssertTrue(tc, ctx==0);
  delete ctx;
}

CuSuite* CuGetSuite(void)
{
  CuSuite* suite = CuSuiteNew();

  SUITE_ADD_TEST(suite, TestPasses);

  return suite;
}
