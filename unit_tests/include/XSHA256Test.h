
#ifndef _XSDK_XSHA256Test_h_
#define _XSDK_XSHA256Test_h_

#include "framework.h"
#include "XSDK/XTaskBase.h"

class XSHA256Test : public test_fixture
{
public:
    TEST_SUITE(XSHA256Test);
        TEST(XSHA256Test::TestHashBasic);
    TEST_SUITE_END();

    ~XSHA256Test() throw() {}
    void setup();
    void teardown();

protected:
    void TestHashBasic();
};

#endif
