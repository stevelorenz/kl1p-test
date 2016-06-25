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

#ifndef KLAB_BICUBICINTERPOLATIONFILTER_H
#define KLAB_BICUBICINTERPOLATIONFILTER_H

#include "Interpolation2DFilter.h"
#include "CubicInterpolationFilter.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TBicubicInterpolationFilter : public TInterpolation2DFilter<T, TBicubicInterpolationFilter<T> >
{
public:

    TBicubicInterpolationFilter();
    TBicubicInterpolationFilter(const TBicubicInterpolationFilter<T>& filter);
    virtual ~TBicubicInterpolationFilter();

    TBicubicInterpolationFilter<T>&     operator=(const TBicubicInterpolationFilter<T>& filter);
    
    T                                   interpolate(const T& z00, const T& z01, const T& z02, const T& z03, const T& z10, const T& z11, const T& z12, const T& z13, const T& z20, const T& z21, const T& z22, const T& z23, const T& z30, const T& z31, const T& z32, const T& z33, klab::DoubleReal muX, klab::DoubleReal muY);
    T                                   interpolate(const T& z00, const T& z01, const T& z02, const T& z03, const T& z10, const T& z11, const T& z12, const T& z13, const T& z20, const T& z21, const T& z22, const T& z23, const T& z30, const T& z31, const T& z32, const T& z33);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TBicubicInterpolationFilter<T>::TBicubicInterpolationFilter() : TInterpolation2DFilter<T, TBicubicInterpolationFilter<T> >()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TBicubicInterpolationFilter<T>::TBicubicInterpolationFilter(const TBicubicInterpolationFilter<T>& filter) : TInterpolation2DFilter<T, TBicubicInterpolationFilter<T> >(filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TBicubicInterpolationFilter<T>::~TBicubicInterpolationFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TBicubicInterpolationFilter<T>& TBicubicInterpolationFilter<T>::operator=(const TBicubicInterpolationFilter<T>& filter)
{
    if(this != &filter)
        TInterpolation2DFilter<T, TBicubicInterpolationFilter<T> >::operator=(filter);

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TBicubicInterpolationFilter<T>::interpolate(const T& z00, const T& z01, const T& z02, const T& z03, const T& z10, const T& z11, const T& z12, const T& z13, const T& z20, const T& z21, const T& z22, const T& z23, const T& z30, const T& z31, const T& z32, const T& z33, klab::DoubleReal muX, klab::DoubleReal muY)
{
    TCubicInterpolationFilter<T> filter;
    return filter.interpolate(filter.interpolate(z00, z01, z02, z03, muX), filter.interpolate(z10, z11, z12, z13, muX), filter.interpolate(z20, z21, z22, z23, muX), filter.interpolate(z30, z31, z32, z33, muX), muY);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TBicubicInterpolationFilter<T>::interpolate(const T& z00, const T& z01, const T& z02, const T& z03, const T& z10, const T& z11, const T& z12, const T& z13, const T& z20, const T& z21, const T& z22, const T& z23, const T& z30, const T& z31, const T& z32, const T& z33)
{
    TCubicInterpolationFilter<T> filter;
    return filter.interpolate(filter.interpolate(z00, z01, z02, z03), filter.interpolate(z10, z11, z12, z13), filter.interpolate(z20, z21, z22, z23), filter.interpolate(z30, z31, z32, z33));
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
