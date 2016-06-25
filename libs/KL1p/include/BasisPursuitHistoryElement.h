// KL1p - A portable C++ compressed sensing library.
// Copyright (c) 2011-2012 René Gebel
// 
// This file is part of the KL1p C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#ifndef KL1P_BASISPURSUITHISTORYELEMENT_H
#define KL1P_BASISPURSUITHISTORYELEMENT_H

#include <KSciInclude.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TBasisPursuitHistoryElement
{
public:

    TBasisPursuitHistoryElement();
    TBasisPursuitHistoryElement(const T& residualNorm, const T& dualityGap);
    TBasisPursuitHistoryElement(const TBasisPursuitHistoryElement<T>& element);
    virtual ~TBasisPursuitHistoryElement();

    TBasisPursuitHistoryElement<T>& operator=(const TBasisPursuitHistoryElement<T>& element);

    const T&        residualNorm() const;
    const T&        dualityGap() const;


private:

    T               _residualNorm;
    T               _dualityGap;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TBasisPursuitHistoryElement<T>::TBasisPursuitHistoryElement() :
_residualNorm(klab::TTypeInfo<T>::ZERO), _dualityGap(klab::TTypeInfo<T>::ZERO)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TBasisPursuitHistoryElement<T>::TBasisPursuitHistoryElement(const T& residualNorm, const T& dualityGap) : 
_residualNorm(residualNorm), _dualityGap(dualityGap)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TBasisPursuitHistoryElement<T>::TBasisPursuitHistoryElement(const TBasisPursuitHistoryElement<T>& element) :
_residualNorm(element._residualNorm), _dualityGap(element._dualityGap)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TBasisPursuitHistoryElement<T>::~TBasisPursuitHistoryElement()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TBasisPursuitHistoryElement<T>& TBasisPursuitHistoryElement<T>::operator=(const TBasisPursuitHistoryElement<T>& element)
{
    if(this != &element)
    {
        _residualNorm = element._residualNorm;
        _dualityGap   = element._dualityGap;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TBasisPursuitHistoryElement<T>::residualNorm() const
{
    return _residualNorm;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TBasisPursuitHistoryElement<T>::dualityGap() const
{
    return _dualityGap;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
