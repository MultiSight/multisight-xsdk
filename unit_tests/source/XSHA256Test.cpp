
#include "XSHA256Test.h"
#include "XSDK/XException.h"
#include "XSDK/XString.h"
#include "XSDK/XSHA256.h"

using namespace XSDK;

REGISTER_TEST_FIXTURE(XSHA256Test);

void XSHA256Test::setup()
{
}

void XSHA256Test::teardown()
{
}

void XSHA256Test::TestHashBasic()
{
    XSHA256 sha256;
    XString msg = "Beneath this mask there is an idea, Mr. Creedy, and ideas are bulletproof.";
    sha256.Update( (uint8_t*)msg.c_str(), msg.length() );
    sha256.Finalize();
    XString output = sha256.GetAsString();
    printf("%s\n",output.c_str());
    UT_ASSERT( output == "d8b3d71ee0e3ea58476835cdf00ad49897c849095d92634bff46abfaa8385198" );
}
