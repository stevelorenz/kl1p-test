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

#ifndef KL1P_ROMPHISTORYELEMENT_H
#define KL1P_ROMPHISTORYELEMENT_H

#include <KSciInclude.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TROMPHistoryElement
{
public:

    TROMPHistoryElement();
    TROMPHistoryElement(const T& residualNorm, klab::UInt32 sparsity);
    TROMPHistoryElement(const TROMPHistoryElement<T>& element);
    virtual ~TROMPHistoryElement();

    TROMPHistoryElement<T>& operator=(const TROMPHistoryElement<T>& element);

    const T&                residualNorm() const;
    klab::UInt32     sparsity() const;


private:

    T               _residualNorm;
    klab::UInt32    _sparsity;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TROMPHistoryElement<T>::TROMPHistoryElement() :
_residualNorm(klab::TTypeInfo<T>::ZERO), _sparsity(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TROMPHistoryElement<T>::TROMPHistoryElement(const T& residualNorm, klab::UInt32 sparsity) : 
_residualNorm(residualNorm), _sparsity(sparsity)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TROMPHistoryElement<T>::TROMPHistoryElement(const TROMPHistoryElement<T>& element) :
_residualNorm(element._residualNorm), _sparsity(element._sparsity)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TROMPHistoryElement<T>::~TROMPHistoryElement()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TROMPHistoryElement<T>& TROMPHistoryElement<T>::operator=(const TROMPHistoryElement<T>& element)
{
    if(this != &element)
    {
        _residualNorm = element._residualNorm;
        _sparsity     = element._sparsity;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TROMPHistoryElement<T>::residualNorm() const
{
    return _residualNorm;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TROMPHistoryElement<T>::sparsity() const
{
    return _sparsity;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
