
#include "XSDK/XOption.h"

using namespace std;
using namespace XSDK;

namespace XSDK
{

list<struct XOption> ParseOptions( int argc, char* argv[] )
{
    list<struct XOption> options;

    struct XOption currentOption;

    int optionIndex = -1;

    for( int i = 0; i < argc; i++ )
    {
        XString token = argv[i];

        if( token.StartsWith( "-" ) )
        {
            if( optionIndex != -1 )
            {
                currentOption.opt = argv[optionIndex];
                options.push_back( currentOption );
                currentOption.arg = "";
            }

            currentOption.opt = token;
            optionIndex = i;
        }
        else
        {
            if( optionIndex != -1 )
            {
                if( currentOption.arg.length() > 0 )
                    currentOption.arg += XString(" ") + token;
                else currentOption.arg = token;
            }
        }

        if( (i + 1) == argc )
        {
            if( optionIndex != -1 )
                options.push_back( currentOption );
        }
    }

    return options;
}

bool CheckOption( const list<struct XOption>& options, const XSDK::XString& opt, XSDK::XString& arg )
{
    list<struct XOption>::const_iterator i;
    for( i = options.begin(); i != options.end(); i++ )
    {
        if( i->opt == opt )
        {
            arg = i->arg;
            return true;
        }
    }

    return false;
}

bool CheckOption( const list<struct XOption>& options, const XSDK::XString& opt )
{
    list<struct XOption>::const_iterator i;
    for( i = options.begin(); i != options.end(); i++ )
    {
        if( i->opt == opt )
            return true;
    }

    return false;
}

}
