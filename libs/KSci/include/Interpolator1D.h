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

#ifndef KLAB_INTERPOLATOR1D_H
#define KLAB_INTERPOLATOR1D_H

#include "Vector2D.h"
#include "LinearInterpolationFilter.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KInterpolator1DException, KException)
KLAB_DECLARE_EXCEPTION(KOutOfBoundInterpolator1DException, KInterpolator1DException)

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter=TLinearInterpolationFilter<T> >
class TInterpolator1D
{
public:

    TInterpolator1D();
    TInterpolator1D(const std::vector<TVector2D<T> >& controlPoints);
    TInterpolator1D(const TInterpolator1D<T, TFilter>& interpolator);
    virtual ~TInterpolator1D();

    TInterpolator1D<T, TFilter>&    operator=(const TInterpolator1D<T, TFilter>& interpolator);

    void                            insert(const TVector2D<T>& point);
    void                            clear();    

    klab::UInt32                    countControlPoints() const;
    const TVector2D<T>&             controlPoint(klab::UInt32 i) const;

    T                               interpolate(const T& x) const;
    void                            interpolate(const std::vector<T>& in, std::vector<T>& out) const;


private:

    std::vector<TVector2D<T> >      _controlPoints; // This array must be sorted.
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TInterpolator1D<T, TFilter>::TInterpolator1D() : 
_controlPoints()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TInterpolator1D<T, TFilter>::TInterpolator1D(const std::vector<TVector2D<T> >& controlPoints) : 
_controlPoints(controlPoints)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TInterpolator1D<T, TFilter>::TInterpolator1D(const TInterpolator1D<T, TFilter>& interpolator) : 
_controlPoints(interpolator._controlPoints)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TInterpolator1D<T, TFilter>::~TInterpolator1D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TInterpolator1D<T, TFilter>& TInterpolator1D<T, TFilter>::operator=(const TInterpolator1D<T, TFilter>& interpolator)
{
    if(this != &interpolator)
        _controlPoints = interpolator._controlPoints;

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TInterpolator1D<T, TFilter>::insert(const TVector2D<T>& point)
{
    klab::Int32 n = static_cast<klab::Int32>(_controlPoints.size());

    _controlPoints.push_back(TVector2D<T>());

    klab::Int32 i = 0;
    for(i=n-1; i>=0 && point.x()<_controlPoints[i].x(); --i)
        _controlPoints[i+1] = _controlPoints[i];

    _controlPoints[i+1] = point;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TInterpolator1D<T, TFilter>::clear()
{
    _controlPoints.clear();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline klab::UInt32 TInterpolator1D<T, TFilter>::countControlPoints() const
{
    return static_cast<klab::UInt32>(_controlPoints.size());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline const TVector2D<T>& TInterpolator1D<T, TFilter>::controlPoint(klab::UInt32 i) const
{
    ThrowTraceExceptionIf(KOutOfBoundInterpolator1DException, i >= static_cast<klab::UInt32>(_controlPoints.size()));

    return _controlPoints[i];
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline T TInterpolator1D<T, TFilter>::interpolate(const T& x) const
{
    TFilter filter;
    return filter.interpolate(_controlPoints, x);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TInterpolator1D<T, TFilter>::interpolate(const std::vector<T>& in, std::vector<T>& out) const
{
    klab::UInt32 n = static_cast<klab::UInt32>(in.size());
    out.resize(n);

    TFilter filter;
    for(klab::UInt32 i=0; i<n; ++i)
        out[i] = filter.interpolate(_controlPoints, in[i]);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
