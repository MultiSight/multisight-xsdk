
#include "XFileTest.h"
#include "XSDK/XFile.h"

using namespace XSDK;

REGISTER_TEST_FIXTURE(XFileTest);

#ifdef WIN32
#define UNLINK(a) _unlink(a)
#else
#define UNLINK(a) unlink(a)
#endif

void XFileTest::setup()
{
    FILE* outFile = fopen("file_data","w+b");
    int64_t value = 42;
    fwrite(&value, 1, 8, outFile);
    fclose(outFile);
}

void XFileTest::teardown()
{
    UNLINK("file_data");
}

void XFileTest::TestFileBasic()
{
    {
        auto f = XFile::Open("file_data", "r+b");
        int64_t value = 0;
        fread(&value, 1, 8, f);
        UT_ASSERT(value == 42);
    }
}
