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

#ifndef KLAB_CUBICINTERPOLATIONFILTER_H
#define KLAB_CUBICINTERPOLATIONFILTER_H

#include "Interpolation1DFilter.h"
#include "LinearInterpolationFilter.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TCubicInterpolationFilter : public TInterpolation1DFilter<T, TCubicInterpolationFilter<T> >
{
public:

    TCubicInterpolationFilter();
    TCubicInterpolationFilter(const TCubicInterpolationFilter<T>& filter);
    virtual ~TCubicInterpolationFilter();

    TCubicInterpolationFilter<T>&   operator=(const TCubicInterpolationFilter<T>& filter);

    T                               interpolate(const std::vector<TVector2D<T> >& controlPoints, const T& x);   // controlPoints array must be sorted on x.
    T                               interpolate(const TVector2D<T>& p0, const TVector2D<T>& p1, const TVector2D<T>& p2, const TVector2D<T>& p3, const T& x);    
    T                               interpolate(const T& y0, const T& y1, const T& y2, const T& y3, klab::DoubleReal mu);   
    T                               interpolate(const T& y0, const T& y1, const T& y2, const T& y3);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TCubicInterpolationFilter<T>::TCubicInterpolationFilter() : TInterpolation1DFilter<T, TCubicInterpolationFilter<T> >()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TCubicInterpolationFilter<T>::TCubicInterpolationFilter(const TCubicInterpolationFilter<T>& filter) : TInterpolation1DFilter<T, TCubicInterpolationFilter<T> >(filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TCubicInterpolationFilter<T>::~TCubicInterpolationFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TCubicInterpolationFilter<T>& TCubicInterpolationFilter<T>::operator=(const TCubicInterpolationFilter<T>& filter)
{
    if(this != &filter)
        TInterpolation1DFilter<T, TCubicInterpolationFilter<T> >::operator=(filter);

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TCubicInterpolationFilter<T>::interpolate(const std::vector<TVector2D<T> >& controlPoints, const T& x)
{
    klab::UInt32 n  = static_cast<klab::UInt32>(controlPoints.size());

    if(n > 3)
    {
        klab::Int32 i = TInterpolation1DFilter<T, TLinearInterpolationFilter<T> >::FindLeftNearestControlPointIndex(controlPoints, x);

        if(i<=0)                                    return this->interpolate(controlPoints[0], controlPoints[1], controlPoints[2], controlPoints[3], x);
        else if(i>=static_cast<klab::Int32>(n-3))   return this->interpolate(controlPoints[n-4], controlPoints[n-3], controlPoints[n-2], controlPoints[n-1], x);
        else                                        return this->interpolate(controlPoints[i-1], controlPoints[i], controlPoints[i+1], controlPoints[i+2], x);
    }
    else if(n == 0)
    {
        return klab::TTypeInfo<T>::ZERO;
    }
    else if(n == 1)
    {
        return controlPoints[0].y();
    }
    else if(n == 2)
    {
        TLinearInterpolationFilter<T> linear;
        return linear.interpolate(controlPoints[0], controlPoints[1], x);
    }
    else
    {
        TLinearInterpolationFilter<T> linear;
        if(x < controlPoints[1].x())    return linear.interpolate(controlPoints[0], controlPoints[1], x);
        else                            return linear.interpolate(controlPoints[1], controlPoints[2], x);
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TCubicInterpolationFilter<T>::interpolate(const TVector2D<T>& p0, const TVector2D<T>& p1, const TVector2D<T>& p2, const TVector2D<T>& p3, const T& x)
{
    if(p0.x()>p1.x() || p1.x()>p2.x() || p2.x()>p3.x())
    {
        std::vector<TVector2D<T> > controlPoints(4);
        controlPoints[0] = p0;
        controlPoints[1] = p1;
        controlPoints[2] = p2;
        controlPoints[3] = p3;

        std::sort(controlPoints.begin(), controlPoints.end(), CompareVector2DOnX_LessThan<T>);

        return this->interpolate(controlPoints[0], controlPoints[1], controlPoints[2], controlPoints[3], x);
    }
    else if(x < p1.x())       
    {
       if(x < p0.x())   return p0.y();
       else             return this->interpolate(TVector2D<T>(static_cast<T>(2)*p0.x()-p1.x(), p0.y()), p0, p1, p2, x);
    }
    else if(x > p2.x())
    {
        if(x > p3.x())   return p3.y();
        else             return this->interpolate(p1, p2, p3, TVector2D<T>(static_cast<T>(2)*p3.x()-p2.x(), p3.y()), x);
    }
    else if(klab::Equals(p1.x(), p2.x()))   
    {
        return p1.y();        
    }
    else
    {
        return this->interpolate(p0.y(), p1.y(), p2.y(), p3.y(), static_cast<klab::DoubleReal>(x-p1.x())/static_cast<klab::DoubleReal>(p2.x()-p1.x()));
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TCubicInterpolationFilter<T>::interpolate(const T& y0, const T& y1, const T& y2, const T& y3, klab::DoubleReal mu)
{
    if(mu < 0.0)
    {
        if(mu < -1.0)   return y0;
        else            return this->interpolate(y0, y0, y1, y2, mu+1.0);
    }
    else if(mu > 1.0)
    {
        if(mu > 2.0)    return y3;
        else            return this->interpolate(y1, y2, y3, y3, mu-1.0);
    }
    else
    {
        return static_cast<T>(static_cast<klab::DoubleReal>(y1) + 0.5*mu*(static_cast<klab::DoubleReal>(y2-y0) + mu*(static_cast<klab::DoubleReal>(static_cast<T>(2)*y0 - static_cast<T>(5)*y1 + static_cast<T>(4)*y2 - y3) + mu*static_cast<klab::DoubleReal>(static_cast<T>(3)*(y1-y2) + y3-y0))));
    }
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T TCubicInterpolationFilter<T>::interpolate(const T& y0, const T& y1, const T& y2, const T& y3)
{
    return static_cast<T>(static_cast<klab::DoubleReal>(y1) + 0.25*(static_cast<klab::DoubleReal>(y2-y0) + 0.5*(static_cast<klab::DoubleReal>(static_cast<T>(2)*y0 - static_cast<T>(5)*y1 + static_cast<T>(4)*y2 - y3) + 0.5*static_cast<klab::DoubleReal>(static_cast<T>(3)*(y1-y2) + y3-y0))));

}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
