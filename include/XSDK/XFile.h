
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// XSDK
// Copyright (c) 2015 Schneider Electric
//
// Use, modification, and distribution is subject to the Boost Software License,
// Version 1.0 (See accompanying file LICENSE).
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef XSDK_XFile_h
#define XSDK_XFile_h

#include "XSDK/XString.h"
#include <memory>
#include <stdlib.h>

namespace XSDK
{

class XFile final
{
public:
    XFile() :
        _f( nullptr )
    {
    }

    XFile( XFile&& obj ) :
        _f(std::move(obj._f))
    {
        obj._f = nullptr;
    }

    ~XFile() throw()
    {
        if(_f)
            fclose(_f);
    }

    XFile& operator = ( XFile&& obj )
    {
        _f = std::move(obj._f);
        obj._f = nullptr;
        return *this;
    }

    operator FILE*() const { return _f; }

    static XFile Open(const XString& path, const XString& mode)
    {
        XFile obj;
        obj._f = fopen(path.c_str(), mode.c_str());
        if( !obj._f )
            X_THROW(("Unable to open: %s",path.c_str()));
        return obj;
    }

    void Close() { fclose(_f); _f = nullptr; }

private:
    XFile( const XFile& ) = delete;
    XFile& operator = ( const XFile& ) = delete;

    FILE* _f;
};

}

#endif
