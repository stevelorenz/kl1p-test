// KSci - A portable C++ numerical analysis library.
// Copyright (c) 2011-2012 René Gebel
// 
// This file is part of the KSci C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#ifndef KLAB_THRESHOLDEDCOUNTFILTER2D_H
#define KLAB_THRESHOLDEDCOUNTFILTER2D_H

#include "SignalFilter2D.h"
#include "ThresholdedCountFilter2DComparator.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TComp=TThresholdedCountFilter2DComparator<T> >
class TThresholdedCountFilter2D : public TSignalFilter2D<T, TThresholdedCountFilter2D<T, TComp> >
{
public:

    TThresholdedCountFilter2D(klab::UInt32 count);
    TThresholdedCountFilter2D(klab::UInt32 count, const T& value);
    TThresholdedCountFilter2D(const TThresholdedCountFilter2D<T, TComp>& filter);
    virtual ~TThresholdedCountFilter2D();

    TThresholdedCountFilter2D<T, TComp>&  operator=(const TThresholdedCountFilter2D<T, TComp>& filter);

    klab::UInt32    count() const;
    const T&        value() const;

    void            apply(arma::Mat<T>& signal);                        
    void            apply(const arma::Mat<T>& in, arma::Mat<T>& out);  


private:

    klab::UInt32    _count;
    T               _value;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TComp>
inline TThresholdedCountFilter2D<T, TComp>::TThresholdedCountFilter2D(klab::UInt32 count) : TSignalFilter2D<T, TThresholdedCountFilter2D<T, TComp> >(),
_count(count), _value(klab::TTypeInfo<T>::ZERO)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TComp>
inline TThresholdedCountFilter2D<T, TComp>::TThresholdedCountFilter2D(klab::UInt32 count, const T& value) : TSignalFilter2D<T, TThresholdedCountFilter2D<T, TComp> >(),
_count(count), _value(value)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TComp>
inline TThresholdedCountFilter2D<T, TComp>::TThresholdedCountFilter2D(const TThresholdedCountFilter2D<T, TComp>& filter) : TSignalFilter2D<T, TThresholdedCountFilter2D<T, TComp> >(filter),
_count(filter._count), _value(filter._value)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TComp>
inline TThresholdedCountFilter2D<T, TComp>::~TThresholdedCountFilter2D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TComp>
inline TThresholdedCountFilter2D<T, TComp>& TThresholdedCountFilter2D<T, TComp>::operator=(const TThresholdedCountFilter2D<T, TComp>& filter)
{
    if(this != &filter)
    {
        TSignalFilter2D<T, TThresholdedCountFilter2D<T, TComp> >::operator=(filter);

        _count = filter._count;
        _value = filter._value;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TComp>
inline klab::UInt32 TThresholdedCountFilter2D<T, TComp>::count() const
{
    return _count;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TComp>
inline const T& TThresholdedCountFilter2D<T, TComp>::value() const
{
    return _value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TComp>
inline void TThresholdedCountFilter2D<T, TComp>::apply(arma::Mat<T>& signal)
{
    klab::UInt32 m = signal.n_rows;
    klab::UInt32 n = signal.n_cols;

    if(m>0 && n>0)
    {
        if(_count > 0)
        {
            klab::UInt32 count = klab::Min(_count, m*n);

            std::vector<TComp> elements;
            for(klab::UInt32 i=0; i<n; ++i)
            {
                for(klab::UInt32 j=0; j<n; ++j)
                    elements.push_back(TComp(signal(i, j), i, j));
            }

            std::sort(elements.begin(), elements.end());

            for(klab::Int32 i=(m*n)-1; i>=static_cast<klab::Int32>(count); --i)
                signal(elements[i].i(), elements[i].j()) = _value;
        }
        else
        {
            signal.fill(_value);
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TComp>
inline void TThresholdedCountFilter2D<T, TComp>::apply(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    out = in;
    this->apply(out);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
