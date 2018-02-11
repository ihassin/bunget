#ifndef TESTCASES_H
#include "testcases.h"
#endif

#ifndef UGUID_H
#include "uguid.h"
#endif

void uguid16_test(CuTest *tc)
{
  bt_uuid_t btuuid;
  uint16_t value = 0xffff;
  
  bt_uuid16_create(&btuuid, value);
  CuAssertTrue(tc, btuuid.value.u16 == value);
}

void uguid32_test(CuTest *tc)
{
  bt_uuid_t btuuid;
  uint32_t value = 0xffff;
  
  bt_uuid32_create(&btuuid, value);
  CuAssertTrue(tc, btuuid.value.u32 == value);
}

void uguid128_test(CuTest *tc)
{
  bt_uuid_t btuuid;
  uint128_t value;
  
  memset(value.data, 0x0f, sizeof(value.data));
  
  bt_uuid128_create(&btuuid, value);
  CuAssertTrue(tc, btuuid.value.u128.data[0] == 0x0f);
}
