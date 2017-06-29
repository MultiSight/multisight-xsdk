
#ifndef _XSDK_XFileTest_h_
#define _XSDK_XFileTest_h_

#include "framework.h"
#include "XSDK/XTaskBase.h"

class XFileTest : public test_fixture
{
public:
    TEST_SUITE(XFileTest);
        TEST(XFileTest::TestFileBasic);
    TEST_SUITE_END();

    ~XFileTest() throw() {}
    void setup();
    void teardown();

protected:
    void TestFileBasic();
};

#endif
