cmake_minimum_required(VERSION 2.8)
project(XSDK)

set(SOURCES include/XSDK/Assert.h
            include/XSDK/Errors.h
            include/XSDK/IXInterface.h
            include/XSDK/IXIterate.h
            include/XSDK/IXUnknown.h
            include/XSDK/IXWeakReference.h
            include/XSDK/LargeFiles.h
            include/XSDK/MemDebugBegin.h
            include/XSDK/MemDebugEnd.h
            include/XSDK/Module.h
            include/XSDK/Object.h
            include/XSDK/OS.h
            include/XSDK/Platform.h
            include/XSDK/TimeUtils.h
            include/XSDK/Types.h
            include/XSDK/UuidUtils.h
            include/XSDK/XBaseObject.h
            include/XSDK/XBitsy.h
            include/XSDK/XBlockingQueue.h
            include/XSDK/XBytePtr.h
            include/XSDK/XCache.h
            include/XSDK/XCommandQueue.h
            include/XSDK/XCondition.h
            include/XSDK/XDateTuple.h
            include/XSDK/XDomParser.h
            include/XSDK/XDomParserNode.h
            include/XSDK/XDuration.h
            include/XSDK/XDynamicLibrary.h
            include/XSDK/XException.h
            include/XSDK/XFullVariant.h
            include/XSDK/XFunctorFP.h
            include/XSDK/XGuard.h
            include/XSDK/XHash.h
            include/XSDK/XInterface.h
            include/XSDK/XInternalList.h
            include/XSDK/XIRef.h
            include/XSDK/XIWeakRef.h
            include/XSDK/XJSON.h
            include/XSDK/XListBox.h
            include/XSDK/XLogger.h
            include/XSDK/XMD5.h
            include/XSDK/XMemory.h
            include/XSDK/XMemoryMap.h
            include/XSDK/XMonoClock.h
            include/XSDK/XMutex.h
            include/XSDK/XNullable.h
            include/XSDK/XObjCount.h
            include/XSDK/XObjectProxy.h
            include/XSDK/XPath.h
            include/XSDK/XRef.h
            include/XSDK/XSharedLib.h
            include/XSDK/XSharedLibDef.h
            include/XSDK/XSharedLibExp.h
            include/XSDK/XSharedLibImp.h
            include/XSDK/XSocket.h
            include/XSDK/XSocketAddress.h
            include/XSDK/XSSLSocket.h
            include/XSDK/XStackTrace.h
            include/XSDK/XStatistics.h
            include/XSDK/XStopWatch.h
            include/XSDK/XStreamIO.h
            include/XSDK/XString.h
            include/XSDK/XStringSlice.h
            include/XSDK/XSystemStats.h
            include/XSDK/XTaskBase.h
            include/XSDK/XTime.h
            include/XSDK/XTimedCommandQueue.h
            include/XSDK/XTimer.h
            include/XSDK/XTimeZone.h
            include/XSDK/XUDPReceiver.h
            include/XSDK/XUDPSender.h
            include/XSDK/XUuid.h
            include/XSDK/XVariant.h
            include/XSDK/XWeakRef.h
            include/XSDK/OS/Files.h
            include/XSDK/OS/Rand.h
            include/XSDK/OS/Sprintf.h
            include/XSDK/OS/StackTrace.h
            include/XSDK/OS/STL.h
            source/XMD5.cpp
            source/LargeFiles.cpp
            source/OS.cpp
            source/Rand.cpp
            source/StackTrace.cpp
            source/TimeUtils.cpp
            source/UuidUtils.cpp
            source/XBaseObject.cpp
            source/XBlockingQueue.cpp
            source/XCache.cpp
            source/XCommandQueue.cpp
            source/XDateTuple.cpp
            source/XDomParser.cpp
            source/XDomParserNode.cpp
            source/XDuration.cpp
            source/XDynamicLibrary.cpp
            source/XException.cpp
            source/XFullVariant.cpp
            source/XGuard.cpp
            source/XHash.cpp
            source/XInternalList.cpp
            source/XJSON.cpp
            source/XListBox.cpp
            source/XLogger.cpp
            source/XMemory.cpp
            source/XMemoryMap.cpp
            source/XMonoClock.cpp
            source/XObjCount.cpp
            source/XObjectProxy.cpp
            source/XPath.cpp
            source/XSocketAddress.cpp
            source/XSocket.cpp
            source/XSSLSocket.cpp
            source/XStackTrace.cpp
            source/XStopWatch.cpp
            source/XString.cpp
            source/XStringSlice.cpp
            source/XSymbol.cpp
            source/XSystemStats.cpp
            source/XTaskBase.cpp
            source/XTime.cpp
            source/XTimedCommandQueue.cpp
            source/XTimer.cpp
            source/XTimeZone.cpp
            source/XUDPReceiver.cpp
            source/XUDPSender.cpp
            source/XUuid.cpp
            source/XVariant.cpp)

if(CMAKE_SYSTEM MATCHES "Linux-")
set(SOURCES ${SOURCES} source/POSIX/Sprintf.cpp
                       source/POSIX/XCondition.cpp
                       source/POSIX/XMutex.cpp)
elseif(CMAKE_SYSTEM MATCHES "Windows")
set(SOURCES ${SOURCES} source/Win32/XCondition.cpp
                       source/Win32/XMutex.cpp)
endif(CMAKE_SYSTEM MATCHES "Linux-")

set(WINDOWS_LIBS DbgHelp ws2_32 iphlpapi rpcrt4.lib)
set(LINUX_LIBS pthread rt dl uuid ssl crypto)

# This blob is about SSL. Basically, if we're being built on Windows we need
# to add some additional libraries.
if(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)
if(CMAKE_SYSTEM MATCHES "Windows")
  include_directories("${CMAKE_CURRENT_SOURCE_DIR}/OpenSSL-Win64/include")
  link_directories("${CMAKE_CURRENT_SOURCE_DIR}/OpenSSL-Win64")
  if(CMAKE_BUILD_TYPE EQUAL "Debug")
    set(WINDOWS_LIBS ${WINDOWS_LIBS} libeay32MDd.lib ssleay32MDd.lib)
  else()
    set(WINDOWS_LIBS ${WINDOWS_LIBS} libeay32MD.lib ssleay32MD.lib)
  endif()
endif(CMAKE_SYSTEM MATCHES "Windows")

# XSDK is special and has to create ../devel_artifacts for everyone else.
file(MAKE_DIRECTORY ../devel_artifacts)

include(cmake/common.cmake NO_POLICY_SCOPE)
include(cmake/base_lib.cmake NO_POLICY_SCOPE)

install(FILES cmake/common.cmake DESTINATION "${devel_artifacts_path}/build")
install(FILES cmake/base_lib.cmake DESTINATION "${devel_artifacts_path}/build")
install(FILES cmake/base_ut.cmake DESTINATION "${devel_artifacts_path}/build")
install(FILES cmake/base_app.cmake DESTINATION "${devel_artifacts_path}/build")

if(CMAKE_SYSTEM MATCHES "Windows")
install(DIRECTORY OpenSSL-Win64/include/openssl DESTINATION include USE_SOURCE_PERMISSIONS)
endif(CMAKE_SYSTEM MATCHES "Windows")
