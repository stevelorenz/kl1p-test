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

#ifndef KLAB_INTERPOLATION2DFILTER_H
#define KLAB_INTERPOLATION2DFILTER_H

#include "Vector3D.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KInterpolation2DFilterException, KException)
KLAB_DECLARE_EXCEPTION(KControlPointsSizeInterpolation2DFilterException, KInterpolation2DFilterException)

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
class TInterpolation2DFilter
{
public:

    TInterpolation2DFilter();
    TInterpolation2DFilter(const TInterpolation2DFilter<T, TChild>& filter);
    virtual ~TInterpolation2DFilter();

    TInterpolation2DFilter<T, TChild>&  operator=(const TInterpolation2DFilter<T, TChild>& filter);

//  T           interpolate(const std::vector<TVector3D<T> >& controlPoints, const TVector2D<T>& x);    // Unimplemented! Must use a Delaunay-triangulation to store control-points. 
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline TInterpolation2DFilter<T, TChild>::TInterpolation2DFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline TInterpolation2DFilter<T, TChild>::TInterpolation2DFilter(const TInterpolation2DFilter<T, TChild>& filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline TInterpolation2DFilter<T, TChild>::~TInterpolation2DFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline TInterpolation2DFilter<T, TChild>& TInterpolation2DFilter<T, TChild>::operator=(const TInterpolation2DFilter<T, TChild>& filter)
{
    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

//template<class T, class TChild>
//inline T TInterpolation2DFilter<T, TChild>::interpolate(const std::vector<TVector3D<T> >& controlPoints, const TVector2D<T>& x)
//{
//    return static_cast<TChild*>(this)->interpolate(controlPoints, x);
//}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
