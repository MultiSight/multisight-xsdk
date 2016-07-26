
#ifndef __XSDK_Option_h
#define __XSDK_Option_h

#include "XSDK/XString.h"
#include <list>

namespace XSDK
{

struct XOption
{
    XSDK::XString opt;
    XSDK::XString arg;
};

std::list<struct XOption> ParseOptions( int argc, char* argv[] );

bool CheckOption( const std::list<struct XOption>& options, const XSDK::XString& opt, XSDK::XString& arg );

bool CheckOption( const std::list<struct XOption>& options, const XSDK::XString& opt );

}

#endif
