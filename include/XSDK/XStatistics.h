
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// XSDK
// Copyright (c) 2015 Schneider Electric
//
// Use, modification, and distribution is subject to the Boost Software License,
// Version 1.0 (See accompanying file LICENSE).
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#ifndef _XStatistics_H_
#define _XStatistics_H_

#include <vector>
#include <algorithm>
#include "XSDK/XSharedLib.h"

namespace XSDK
{
    template<class SampleType>
    struct _Sample
    {
        SampleType value;
        bool operator<(const struct _Sample<SampleType> &other) const
        {
            return value < other.value;
        }
    };

    // Average
    class Average
    {
    public:
        template<class SampleType>
        X_API static SampleType Calculate(std::vector<struct _Sample<SampleType> > &samples, const int count)
        {
            SampleType total = 0;
            typename std::vector<struct _Sample<SampleType> >::iterator it = samples.begin();
            while( it != samples.end() )
            {
                total += it->value;
                it++;
            }
            return total / count;
        }
    };

    // Median
    class Median
    {
    public:
        template<class SampleType>
        X_API static SampleType Calculate(std::vector<struct _Sample<SampleType> > &samples, const int count)
        {
            std::sort(samples.begin(),samples.end());
            typename std::vector<struct _Sample<SampleType> >::iterator it = samples.begin();
            for (int ii=0; ii<count/2; ii++)
                it++;
            return it->value;
        }
    };

template<class T,class SampleType>
class XStatistics
{
public:
    X_API XStatistics() :
      _currentSamples(0), _maxSamples(0) {}
    X_API XStatistics( int maxSamples ) :
      _currentSamples(0), _maxSamples(maxSamples) {}

    X_API void SetMaxSamples( int maxSamples ) { _maxSamples = maxSamples; }
    X_API int GetMaxSamples() const { return _maxSamples; }

    X_API int GetNumSamples() { return _currentSamples; }
    // Returns number of samples, or -1 on error.
    X_API int AddSample( SampleType sample )
    {
        struct _Sample<SampleType> s = { sample };
        if( _maxSamples > 0 && (_currentSamples + 1) > _maxSamples )
        {
            std::rotate( _samples.begin(), _samples.begin()+1, _samples.end() );
            _samples[_currentSamples-1] = s;
        }
        else
        {
            _samples.push_back( s );
            _currentSamples++;
        }
        return _currentSamples;
    }

    // Returns the number of items comprising the result.
    X_API int GetResult( SampleType& result )
    {
        result = 0;
        if( _currentSamples > 0 )
            result = T::Calculate( _samples, _currentSamples );
        return _currentSamples;
    }

    X_API void Clear() { _samples.clear(); _currentSamples = 0; }

private:

    std::vector<struct _Sample<SampleType> > _samples;
    int _currentSamples;
    int _maxSamples; // 0 means disabled
}; // class XStatistics

} // namespace XSDK

#endif // _XStatistics_H_
