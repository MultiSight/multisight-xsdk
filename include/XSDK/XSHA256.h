
#ifndef xsdk_sha256_h
#define xsdk_sha256_h

#include "XSDK/XString.h"
#include "XSDK/Types.h"
#include "openssl/sha.h"

namespace XSDK
{

class XSHA256 final
{
public:
    X_API XSHA256();
    X_API virtual ~XSHA256() throw();

    X_API void Update( const uint8_t* src, size_t size );
    X_API void Finalize();

    X_API void Get( uint8_t* output ); // returns 32 byte sha256
    X_API XString GetAsString();

private:
    uint8_t _digest[32];
    bool _finalized;
    SHA256_CTX _sha256;
};

}

#endif
