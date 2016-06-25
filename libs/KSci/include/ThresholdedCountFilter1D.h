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

#ifndef KLAB_THRESHOLDEDCOUNTFILTER1D_H
#define KLAB_THRESHOLDEDCOUNTFILTER1D_H

#include "SignalFilter1D.h"
#include "ThresholdedCountFilter1DComparator.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TComp=TThresholdedCountFilter1DComparator<T> >
class TThresholdedCountFilter1D : public TSignalFilter1D<T, TThresholdedCountFilter1D<T, TComp> >
{
public:

    TThresholdedCountFilter1D(klab::UInt32 count);
    TThresholdedCountFilter1D(klab::UInt32 count, const T& value);
    TThresholdedCountFilter1D(const TThresholdedCountFilter1D<T, TComp>& filter);
    virtual ~TThresholdedCountFilter1D();

    TThresholdedCountFilter1D<T, TComp>&      operator=(const TThresholdedCountFilter1D<T, TComp>& filter);

    klab::UInt32    count() const;
    const T&        value() const;

    void            apply(arma::Col<T>& signal);                        
    void            apply(const arma::Col<T>& in, arma::Col<T>& out);  


private:

    klab::UInt32    _count;
    T               _value;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TComp>
inline TThresholdedCountFilter1D<T, TComp>::TThresholdedCountFilter1D(klab::UInt32 count) : TSignalFilter1D<T, TThresholdedCountFilter1D<T, TComp> >(),
_count(count), _value(klab::TTypeInfo<T>::ZERO)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TComp>
inline TThresholdedCountFilter1D<T, TComp>::TThresholdedCountFilter1D(klab::UInt32 count, const T& value) : TSignalFilter1D<T, TThresholdedCountFilter1D<T, TComp> >(),
_count(count), _value(value)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TComp>
inline TThresholdedCountFilter1D<T, TComp>::TThresholdedCountFilter1D(const TThresholdedCountFilter1D<T, TComp>& filter) : TSignalFilter1D<T, TThresholdedCountFilter1D<T, TComp> >(filter),
_count(filter._count), _value(filter._value)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TComp>
inline TThresholdedCountFilter1D<T, TComp>::~TThresholdedCountFilter1D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TComp>
inline TThresholdedCountFilter1D<T, TComp>& TThresholdedCountFilter1D<T, TComp>::operator=(const TThresholdedCountFilter1D<T, TComp>& filter)
{
    if(this != &filter)
    {
        TSignalFilter1D<T, TThresholdedCountFilter1D<T, TComp> >::operator=(filter);

        _count = filter._count;
        _value = filter._value;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TComp>
inline klab::UInt32 TThresholdedCountFilter1D<T, TComp>::count() const
{
    return _count;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TComp>
inline const T& TThresholdedCountFilter1D<T, TComp>::value() const
{
    return _value;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TComp>
inline void TThresholdedCountFilter1D<T, TComp>::apply(arma::Col<T>& signal)
{
    klab::UInt32 n = signal.n_rows;

    if(n > 0)
    {
        if(_count > 0)
        {
            klab::UInt32 count = klab::Min(_count, n);

            std::vector<TComp> elements;
            for(klab::UInt32 i=0; i<n; ++i)
                elements.push_back(TComp(signal[i], i));

            std::sort(elements.begin(), elements.end());

            for(klab::Int32 i=n-1; i>=static_cast<klab::Int32>(count); --i)
                signal[elements[i].index()] = _value;
        }
        else
        {
            signal.fill(_value);
        }
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TComp>
inline void TThresholdedCountFilter1D<T, TComp>::apply(const arma::Col<T>& in, arma::Col<T>& out)
{
    out = in;
    this->apply(out);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
