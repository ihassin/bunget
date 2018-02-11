#ifndef TESTCASES_H
#define TESTCASES_H

#ifndef CU_TEST_H
#include "cutest.h"
#endif

#include "libbunget.h"

void canary(CuTest* tc);
void server_test(CuTest* tc);

void uguid16_test(CuTest *tc);
void uguid32_test(CuTest *tc);
void uguid128_test(CuTest *tc);

#endif
