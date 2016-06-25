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

#ifndef KL1P_HISTORY_H
#define KL1P_HISTORY_H

#include <KSciInclude.h>




namespace kl1p
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KHistoryException, klab::KException)
KLAB_DECLARE_EXCEPTION(KOutOfBoundHistoryException, KHistoryException)

// ---------------------------------------------------------------------------------------------------- //

template<class T>
class THistory
{
public:

    THistory();
    THistory(const THistory<T>& history);
    virtual ~THistory();

    THistory<T>&    operator=(const THistory<T>& history);

    const T&        operator[](klab::UInt32 i) const; 

    void            clear();
    void            push(const T& element);
   
    klab::UInt32    size() const;
    const T&        element(klab::UInt32 i) const; 


private:

    std::vector<T>      _history;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline THistory<T>::THistory() :
_history()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline THistory<T>::THistory(const THistory<T>& history) :
_history(history._history)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline THistory<T>::~THistory()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline THistory<T>& THistory<T>::operator=(const THistory<T>& history)
{
    if(this != &history)
    {
        _history = history._history;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& THistory<T>::operator[](klab::UInt32 i) const
{
    ThrowTraceExceptionIf(KOutOfBoundHistoryException, i>=static_cast<klab::UInt32>(_history.size()));

    return _history[i];
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void THistory<T>::clear()
{
    _history.clear();
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline void THistory<T>::push(const T& element)
{
    _history.push_back(element);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline klab::UInt32 THistory<T>::size() const
{
    return static_cast<klab::UInt32>(_history.size());
}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline const T& THistory<T>::element(klab::UInt32 i) const
{
    ThrowTraceExceptionIf(KOutOfBoundHistoryException, i>=static_cast<klab::UInt32>(_history.size()));

    return _history[i];
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
