#ifndef TESTCASES_H
#include "testcases.h"
#endif

void server_test(CuTest *tc)
{
  bunget::BtCtx *ctx = bunget::BtCtx::instance();
  CuAssertTrue(tc, ctx != NULL);
}
