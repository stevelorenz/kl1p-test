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

#ifndef KLAB_BILINEARINTERPOLATIONFILTER_H
#define KLAB_BILINEARINTERPOLATIONFILTER_H

#include "Interpolation2DFilter.h"
#include "LinearInterpolationFilter.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TBilinearInterpolationFilter : public TInterpolation2DFilter<T, TBilinearInterpolationFilter<T> >
{
public:

    TBilinearInterpolationFilter();
    TBilinearInterpolationFilter(const TBilinearInterpolationFilter<T>& filter);
    virtual ~TBilinearInterpolationFilter();

    TBilinearInterpolationFilter<T>&    operator=(const TBilinearInterpolationFilter<T>& filter);
    
    T                                   interpolate(const T& z00, const T& z01, const T& z10, const T& z11, klab::DoubleReal muX, klab::DoubleReal muY);
    T                                   interpolate(const T& z00, const T& z01, const T& z10, const T& z11);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TBilinearInterpolationFilter<T>::TBilinearInterpolationFilter() : TInterpolation2DFilter<T, TBilinearInterpolationFilter<T> >()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TBilinearInterpolationFilter<T>::TBilinearInterpolationFilter(const TBilinearInterpolationFilter<T>& filter) : TInterpolation2DFilter<T, TBilinearInterpolationFilter<T> >(filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TBilinearInterpolationFilter<T>::~TBilinearInterpolationFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TBilinearInterpolationFilter<T>& TBilinearInterpolationFilter<T>::operator=(const TBilinearInterpolationFilter<T>& filter)
{
    if(this != &filter)
        TInterpolation2DFilter<T, TBilinearInterpolationFilter<T> >::operator=(filter);

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TBilinearInterpolationFilter<T>::interpolate(const T& z00, const T& z01, const T& z10, const T& z11, klab::DoubleReal muX, klab::DoubleReal muY)
{
    TLinearInterpolationFilter<T> filter;
    return filter.interpolate(filter.interpolate(z00, z01, muX), filter.interpolate(z10, z11, muX), muY);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TBilinearInterpolationFilter<T>::interpolate(const T& z00, const T& z01, const T& z10, const T& z11)
{
    TLinearInterpolationFilter<T> filter;
    return filter.interpolate(filter.interpolate(z00, z01), filter.interpolate(z10, z11));
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
