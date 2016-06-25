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

#ifndef KLAB_INTERPOLATION1DFILTER_H
#define KLAB_INTERPOLATION1DFILTER_H

#include "Vector2D.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
class TInterpolation1DFilter
{
public:

    TInterpolation1DFilter();
    TInterpolation1DFilter(const TInterpolation1DFilter<T, TChild>& filter);
    virtual ~TInterpolation1DFilter();

    TInterpolation1DFilter<T, TChild>&  operator=(const TInterpolation1DFilter<T, TChild>& filter);

    T                   interpolate(const std::vector<TVector2D<T> >& controlPoints, const T& x);


public:

    static klab::Int32  FindLeftNearestControlPointIndex(const std::vector<TVector2D<T> >& controlPoints, const T& x);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline TInterpolation1DFilter<T, TChild>::TInterpolation1DFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline TInterpolation1DFilter<T, TChild>::TInterpolation1DFilter(const TInterpolation1DFilter<T, TChild>& filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline TInterpolation1DFilter<T, TChild>::~TInterpolation1DFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline TInterpolation1DFilter<T, TChild>& TInterpolation1DFilter<T, TChild>::operator=(const TInterpolation1DFilter<T, TChild>& filter)
{
    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline T TInterpolation1DFilter<T, TChild>::interpolate(const std::vector<TVector2D<T> >& controlPoints, const T& x)
{
    return static_cast<TChild*>(this)->interpolate(controlPoints, x);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline klab::Int32 TInterpolation1DFilter<T, TChild>::FindLeftNearestControlPointIndex(const std::vector<TVector2D<T> >& controlPoints, const T& x)
{
    klab::UInt32 n  = static_cast<klab::UInt32>(controlPoints.size());
    klab::UInt32 i  = n>>1;
    klab::UInt32 il = 0;
    klab::UInt32 ir = n;    

    while(ir-il > 1)
    {
        T value = controlPoints[i].x();

        if(klab::Equals(value, x))  il = ir = i;
        else if(x < value)          ir = i;
        else                        il = i;

        i  = il + ((ir-il)>>1);
    }

    return (controlPoints[i].x()<=x ? static_cast<klab::Int32>(i) : -1);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
