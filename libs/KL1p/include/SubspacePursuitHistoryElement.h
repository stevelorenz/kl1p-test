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

#ifndef KL1P_BSSPAUCEPURSUITHISTORYELEMENT_H
#define KL1P_BSSPAUCEPURSUITHISTORYELEMENT_H

#include <KSciInclude.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TSubspacePursuitHistoryElement
{
public:

    TSubspacePursuitHistoryElement();
    TSubspacePursuitHistoryElement(const T& residualNorm);
    TSubspacePursuitHistoryElement(const TSubspacePursuitHistoryElement<T>& element);
    virtual ~TSubspacePursuitHistoryElement();

    TSubspacePursuitHistoryElement<T>&  operator=(const TSubspacePursuitHistoryElement<T>& element);

    const T&                residualNorm() const;


private:

    T               _residualNorm;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSubspacePursuitHistoryElement<T>::TSubspacePursuitHistoryElement() :
_residualNorm(klab::TTypeInfo<T>::ZERO)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSubspacePursuitHistoryElement<T>::TSubspacePursuitHistoryElement(const T& residualNorm) : 
_residualNorm(residualNorm)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSubspacePursuitHistoryElement<T>::TSubspacePursuitHistoryElement(const TSubspacePursuitHistoryElement<T>& element) :
_residualNorm(element._residualNorm)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSubspacePursuitHistoryElement<T>::~TSubspacePursuitHistoryElement()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSubspacePursuitHistoryElement<T>& TSubspacePursuitHistoryElement<T>::operator=(const TSubspacePursuitHistoryElement<T>& element)
{
    if(this != &element)
    {
        _residualNorm = element._residualNorm;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& TSubspacePursuitHistoryElement<T>::residualNorm() const
{
    return _residualNorm;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
