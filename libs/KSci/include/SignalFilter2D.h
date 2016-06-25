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

#ifndef KLAB_SIGNALFILTER2D_H
#define KLAB_SIGNALFILTER2D_H

#include "SignalFilter.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KSignalFilter2DException, KSignalFilterException)

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
class TSignalFilter2D
{
public:

    TSignalFilter2D();
    TSignalFilter2D(const TSignalFilter2D<T, TChild>& filter);
    virtual ~TSignalFilter2D();

    TSignalFilter2D<T, TChild>&     operator=(const TSignalFilter2D<T, TChild>& filter);

    void        apply(arma::Mat<T>& signal);                        // To override.
    void        apply(const arma::Mat<T>& in, arma::Mat<T>& out);   // To override.
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline TSignalFilter2D<T, TChild>::TSignalFilter2D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline TSignalFilter2D<T, TChild>::TSignalFilter2D(const TSignalFilter2D<T, TChild>& filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline TSignalFilter2D<T, TChild>::~TSignalFilter2D()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline TSignalFilter2D<T, TChild>& TSignalFilter2D<T, TChild>::operator=(const TSignalFilter2D<T, TChild>& filter)
{
    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline void TSignalFilter2D<T, TChild>::apply(arma::Mat<T>& signal)
{
    static_cast<const TChild&>(*this).apply(signal);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TChild>
inline void TSignalFilter2D<T, TChild>::apply(const arma::Mat<T>& in, arma::Mat<T>& out)
{
    static_cast<const TChild&>(*this).apply(in, out);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
