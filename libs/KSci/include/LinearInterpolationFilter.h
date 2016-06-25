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

#ifndef KLAB_LINEARINTERPOLATIONFILTER_H
#define KLAB_LINEARINTERPOLATIONFILTER_H

#include "Interpolation1DFilter.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TLinearInterpolationFilter : public TInterpolation1DFilter<T, TLinearInterpolationFilter<T> >
{
public:

    TLinearInterpolationFilter();
    TLinearInterpolationFilter(const TLinearInterpolationFilter<T>& filter);
    virtual ~TLinearInterpolationFilter();

    TLinearInterpolationFilter<T>&  operator=(const TLinearInterpolationFilter<T>& filter);

    T                               interpolate(const std::vector<TVector2D<T> >& controlPoints, const T& x);   // controlPoints array must be sorted on x. 
    T                               interpolate(const TVector2D<T>& p0, const TVector2D<T>& p1, const T& x);    
    T                               interpolate(const T& y0, const T& y1, klab::DoubleReal mu);
    T                               interpolate(const T& y0, const T& y1);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TLinearInterpolationFilter<T>::TLinearInterpolationFilter() : TInterpolation1DFilter<T, TLinearInterpolationFilter<T> >()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TLinearInterpolationFilter<T>::TLinearInterpolationFilter(const TLinearInterpolationFilter<T>& filter) : TInterpolation1DFilter<T, TLinearInterpolationFilter<T> >(filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TLinearInterpolationFilter<T>::~TLinearInterpolationFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TLinearInterpolationFilter<T>& TLinearInterpolationFilter<T>::operator=(const TLinearInterpolationFilter<T>& filter)
{
    if(this != &filter)
        TInterpolation1DFilter<T, TLinearInterpolationFilter<T> >::operator=(filter);

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TLinearInterpolationFilter<T>::interpolate(const std::vector<TVector2D<T> >& controlPoints, const T& x)
{
    klab::UInt32 n  = static_cast<klab::UInt32>(controlPoints.size());

    if(n > 1)
    {
        klab::Int32 i = TInterpolation1DFilter<T, TLinearInterpolationFilter<T> >::FindLeftNearestControlPointIndex(controlPoints, x);

        if(i<0)                                     return this->interpolate(TVector2D<T>((controlPoints[0].x()-x)/static_cast<T>(2), controlPoints[0].y()), controlPoints[0], x);
        else if(i>=static_cast<klab::Int32>(n-1))   return this->interpolate(controlPoints[n-1], TVector2D<T>((x-controlPoints[n-1].x())/static_cast<T>(2), controlPoints[n-1].y()), x);
        else                                        return this->interpolate(controlPoints[i], controlPoints[i+1], x);
    }
    else if(n == 0)
    {
        return klab::TTypeInfo<T>::ZERO;
    }
    else
    {
        return controlPoints[0].y();
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TLinearInterpolationFilter<T>::interpolate(const TVector2D<T>& p0, const TVector2D<T>& p1, const T& x)
{
    if(p0.x() > p1.x())                     return this->interpolate(p1, p0, x);
    else if(klab::Equals(p0.x(), p1.x()))   return p0.y();
    else                                    return this->interpolate(p0.y(), p1.y(), static_cast<klab::DoubleReal>(x-p0.x())/static_cast<klab::DoubleReal>(p1.x()-p0.x()));      
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TLinearInterpolationFilter<T>::interpolate(const T& y0, const T& y1, klab::DoubleReal mu)
{
    if(mu < 0.0)        return y0;
    else if(mu > 1.0)   return y1;
    else                return static_cast<T>(static_cast<klab::DoubleReal>(y0)*(1.0-mu) + static_cast<klab::DoubleReal>(y1)*mu);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TLinearInterpolationFilter<T>::interpolate(const T& y0, const T& y1)
{
    return ((y0+y1) / static_cast<T>(2));
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
