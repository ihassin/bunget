#ifndef TESTCASES_H
#include "testcases.h"
#endif

void canary(CuTest* tc)
{
  bunget::BtCtx *ctx = bunget::BtCtx::instance();
  CuAssertTrue(tc, ctx != NULL);
}
