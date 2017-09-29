
#include "XSDK/XSHA256.h"

using namespace XSDK;
using namespace std;

XSHA256::XSHA256() :
    _digest(),
    _finalized(false),
    _sha256()
{
    SHA256_Init(&_sha256);
}

XSHA256::~XSHA256() throw()
{
    if(!_finalized)
        SHA256_Final(_digest, &_sha256);
}

void XSHA256::Update( const uint8_t* src, size_t size )
{
    SHA256_Update(&_sha256, src, size);
}

void XSHA256::Finalize()
{
    if(!_finalized)
    {
        _finalized = true;

        SHA256_Final(_digest, &_sha256);
    }
}

void XSHA256::Get( uint8_t* output ) // returns 32 byte sha256
{
    if( !_finalized )
        X_THROW(("Please finalize() your XSHA256 before calling a get() method."));

    memcpy(output, _digest, 32);
}

XString XSHA256::GetAsString()
{
    if( !_finalized )
        X_THROW(("Please finalize() your XSHA256 before calling a get() method."));

    return XString::Format( "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
                              _digest[0], _digest[1],_digest[2], _digest[3],
                              _digest[4], _digest[5], _digest[6], _digest[7],
                              _digest[8], _digest[9], _digest[10], _digest[11],
                              _digest[12], _digest[13], _digest[14], _digest[15],
                              _digest[16], _digest[17],_digest[18], _digest[19],
                              _digest[20], _digest[21], _digest[22], _digest[23],
                              _digest[24], _digest[25], _digest[26], _digest[27],
                              _digest[28], _digest[29], _digest[30], _digest[31] );
}
