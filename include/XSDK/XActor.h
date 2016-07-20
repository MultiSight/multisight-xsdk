
#ifndef XSDK_Actor_h
#define XSDK_Actor_h

#include <mutex>
#include <condition_variable>
#include <future>
#include <list>
#include "XSDK/XLogger.h"

namespace XSDK
{

/// An object that inherits from XActor is an entity with a thread that responds to commands
/// sent to it (in the order they were sent) producing some kind of result. XActor is a template
/// class that parameterizes both the command and result types. In addition, XActor returns a
/// std::future<> from post(), thus allowing clients the freedom to choose whether to block until
/// their command has a response or keep running until it does.

template<class CMD, class RESULT>
class XActor
{
    typedef std::unique_lock<std::mutex> guard;

public:
    XActor() = default;
    XActor( const XActor& ) = delete;

    virtual ~XActor() throw()
    {
        if( Started() )
            Stop();
    }

    XActor& operator = ( const XActor& ) = delete;

    void Start()
    {
        guard g( _lock );
        _started = true;
        _thread = std::thread( &XActor<CMD,RESULT>::_main_loop, this );
    }

    inline bool Started() const
    {
        return _started;
    }

    void Stop()
    {
        if( Started() )
        {
            {
                guard g( _lock );
                _started = false;
                _cond.notify_one();
                _queue.clear();
            }

            _thread.join();
        }
    }

    std::future<RESULT> Post( const CMD& cmd )
    {
        guard g( _lock );

        std::promise<RESULT> p;
        auto waiter = p.get_future();

        _queue.push_front( std::pair<CMD,std::promise<RESULT>>( cmd, std::move( p ) ) );

        _cond.notify_one();

        return waiter;
    }

    virtual RESULT Process( const CMD& cmd ) = 0;

protected:
    void _main_loop()
    {
        while( _started )
        {
            std::pair<CMD,std::promise<RESULT>> item;

            {
                guard g( _lock );

                _cond.wait( g, [this] () { return !this->_queue.empty() || !this->_started; } );

                if( !_started )
                    continue;

                item = std::move( _queue.back() );
                _queue.pop_back();
            }

            try
            {
                item.second.set_value( Process( item.first ) );
            }
            catch( ... )
            {
                try
                {
                    _queue.back().second.set_exception( std::current_exception() );
                }
                catch( ... )
                {
                    X_LOG_NOTICE( "Failed to attach unknown exception to std::promise<>" );
                }
            }
        }
    }

    std::thread _thread;
    std::mutex _lock;
    std::condition_variable _cond;
    std::list<std::pair<CMD,std::promise<RESULT>>> _queue;
    bool _started = false;
};

}

#endif
