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

#ifndef KL1P_OMPHISTORYELEMENT_H
#define KL1P_OMPHISTORYELEMENT_H

#include <KSciInclude.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TOMPHistoryElement
{
public:

    TOMPHistoryElement();
    TOMPHistoryElement(const T& residualNorm, klab::UInt32 sparsity);
    TOMPHistoryElement(const TOMPHistoryElement<T>& element);
    virtual ~TOMPHistoryElement();

    TOMPHistoryElement<T>&  operator=(const TOMPHistoryElement<T>& element);

    const T&                residualNorm() const;
    klab::UInt32     sparsity() const;


private:

    T               _residualNorm;
    klab::UInt32    _sparsity;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TOMPHistoryElement<T>::TOMPHistoryElement() :
_residualNorm(klab::TTypeInfo<T>::ZERO), _sparsity(0)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TOMPHistoryElement<T>::TOMPHistoryElement(const T& residualNorm, klab::UInt32 sparsity) : 
_residualNorm(residualNorm), _sparsity(sparsity)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TOMPHistoryElement<T>::TOMPHistoryElement(const TOMPHistoryElement<T>& element) :
_residualNorm(element._residualNorm), _sparsity(element._sparsity)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TOMPHistoryElement<T>::~TOMPHistoryElement()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TOMPHistoryElement<T>& TOMPHistoryElement<T>::operator=(const TOMPHistoryElement<T>& element)
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
inline const T& TOMPHistoryElement<T>::residualNorm() const
{
    return _residualNorm;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 TOMPHistoryElement<T>::sparsity() const
{
    return _sparsity;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
