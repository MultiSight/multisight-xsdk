
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// XSDK
// Copyright (c) 2015 Schneider Electric
//
// Use, modification, and distribution is subject to the Boost Software License,
// Version 1.0 (See accompanying file LICENSE).
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef _XSDK_ASSERT_H_
#define _XSDK_ASSERT_H_

#include <assert.h>

#define X_ASSERT(exp) \
X_MACRO_BEGIN \
    if( !(exp) )  \
    { \
        X_LOG_CRITICAL("X_ASSERT(" #exp ")"); \
        assert(exp); \
    } \
X_MACRO_END

#ifdef IS_DEBUG
    #define X_VERIFY X_ASSERT
#else
    #define X_VERIFY(exp) (exp) // Release
#endif

#endif

