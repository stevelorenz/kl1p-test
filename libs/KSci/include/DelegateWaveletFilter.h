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

#ifndef KLAB_DELEGATEWAVELETFILTER_H
#define KLAB_DELEGATEWAVELETFILTER_H

#include "WaveletFilter.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARE_EXCEPTION(KDelegateWaveletFilterException, KWaveletFilterException)
KLAB_DECLARE_EXCEPTION(KNullDelegateWaveletFilterException, KDelegateWaveletFilterException)

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter=TWaveletFilter<T> >
class TDelegateWaveletFilter : public TWaveletFilter<T>
{
public:

    TDelegateWaveletFilter();
    TDelegateWaveletFilter(const TFilter* filter);
    TDelegateWaveletFilter(const klab::TSmartPointer<TFilter>& filter);
    TDelegateWaveletFilter(const TDelegateWaveletFilter<T, TFilter>& filter);
    virtual ~TDelegateWaveletFilter();

    TDelegateWaveletFilter<T, TFilter>&     operator=(const TDelegateWaveletFilter<T, TFilter>& filter);

    void                                    setFilter(const TFilter* filter);
    void                                    setFilter(const klab::TSmartPointer<TFilter>& filter);
    const klab::TSmartPointer<TFilter>&     filter() const;

    virtual klab::UInt32                    waveLength() const;
    virtual const T&                        h0(klab::UInt32 i) const;
    virtual const T&                        h1(klab::UInt32 i) const;
    virtual const T&                        rh0(klab::UInt32 i) const;
    virtual const T&                        rh1(klab::UInt32 i) const;

    virtual void                            transformMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);       // Compute filter on every rows of the matrix.
    virtual void                            transformMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);    // Compute filter on every columns of the matrix.
    virtual void                            invertMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);          // Compute inverse filter on every rows of the matrix.
    virtual void                            invertMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);       // Compute inverse filter on every columns of the matrix. 

    virtual void                            forwardOnMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);
    virtual void                            forwardOnMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);
    virtual void                            backwardOnMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);
    virtual void                            backwardOnMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols);


private:

    klab::TSmartPointer<TFilter>            _filter;
};

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TDelegateWaveletFilter<T, TFilter>::TDelegateWaveletFilter() : TWaveletFilter<T>(),
_filter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TDelegateWaveletFilter<T, TFilter>::TDelegateWaveletFilter(const TFilter* filter) : TWaveletFilter<T>(),
_filter(const_cast<TFilter*>(filter))
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TDelegateWaveletFilter<T, TFilter>::TDelegateWaveletFilter(const klab::TSmartPointer<TFilter>& filter) : TWaveletFilter<T>(),
_filter(filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TDelegateWaveletFilter<T, TFilter>::TDelegateWaveletFilter(const TDelegateWaveletFilter<T, TFilter>& filter) : TWaveletFilter<T>(filter),
_filter(filter._filter)
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TDelegateWaveletFilter<T, TFilter>::~TDelegateWaveletFilter()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline TDelegateWaveletFilter<T, TFilter>& TDelegateWaveletFilter<T, TFilter>::operator=(const TDelegateWaveletFilter<T, TFilter>& filter)
{
    if(this != &filter)
    {
        TWaveletFilter<T>::operator=(filter);

        _filter = filter._filter;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TDelegateWaveletFilter<T, TFilter>::setFilter(const TFilter* filter)
{
    _filter = const_cast<TFilter*>(filter);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TDelegateWaveletFilter<T, TFilter>::setFilter(const klab::TSmartPointer<TFilter>& filter)
{
    _filter = filter;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline const klab::TSmartPointer<TFilter>& TDelegateWaveletFilter<T, TFilter>::filter() const
{
    return _filter;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline klab::UInt32 TDelegateWaveletFilter<T, TFilter>::waveLength() const
{
    if(_filter.get() != 0)  return _filter.get()->waveLength();
    else                    return 0;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline const T& TDelegateWaveletFilter<T, TFilter>::h0(klab::UInt32 i) const
{
    if(_filter.get() != 0)  return _filter.get()->h0(i);
    else                    return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline const T& TDelegateWaveletFilter<T, TFilter>::h1(klab::UInt32 i) const
{
    if(_filter.get() != 0)  return _filter.get()->h1(i);
    else                    return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline const T& TDelegateWaveletFilter<T, TFilter>::rh0(klab::UInt32 i) const
{
    if(_filter.get() != 0)  return _filter.get()->rh0(i);
    else                    return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline const T& TDelegateWaveletFilter<T, TFilter>::rh1(klab::UInt32 i) const
{
    if(_filter.get() != 0)  return _filter.get()->rh1(i);
    else                    return klab::TTypeInfo<T>::ZERO;
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TDelegateWaveletFilter<T, TFilter>::transformMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    ThrowTraceExceptionIf(KNullDelegateWaveletFilterException, _filter.get()==0);

    _filter.get()->transformMatrixRows(inout, rows, cols);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TDelegateWaveletFilter<T, TFilter>::transformMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    ThrowTraceExceptionIf(KNullDelegateWaveletFilterException, _filter.get()==0);

    _filter.get()->transformMatrixColumns(inout, rows, cols);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TDelegateWaveletFilter<T, TFilter>::invertMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    ThrowTraceExceptionIf(KNullDelegateWaveletFilterException, _filter.get()==0);

    _filter.get()->invertMatrixRows(inout, rows, cols);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TDelegateWaveletFilter<T, TFilter>::invertMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    ThrowTraceExceptionIf(KNullDelegateWaveletFilterException, _filter.get()==0);

    _filter.get()->invertMatrixColumns(inout, rows, cols);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TDelegateWaveletFilter<T, TFilter>::forwardOnMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    ThrowTraceExceptionIf(KNullDelegateWaveletFilterException, _filter.get()==0);

    _filter.get()->forwardOnMatrixRows(inout, rows, cols);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TDelegateWaveletFilter<T, TFilter>::forwardOnMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    ThrowTraceExceptionIf(KNullDelegateWaveletFilterException, _filter.get()==0);

    _filter.get()->forwardOnMatrixColumns(inout, rows, cols);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TDelegateWaveletFilter<T, TFilter>::backwardOnMatrixRows(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    ThrowTraceExceptionIf(KNullDelegateWaveletFilterException, _filter.get()==0);

    _filter.get()->backwardOnMatrixRows(inout, rows, cols);
}

// ---------------------------------------------------------------------------------------------------- //

template<class T, class TFilter>
inline void TDelegateWaveletFilter<T, TFilter>::backwardOnMatrixColumns(arma::Mat<T>& inout, klab::UInt32 rows, klab::UInt32 cols)
{
    ThrowTraceExceptionIf(KNullDelegateWaveletFilterException, _filter.get()==0);

    _filter.get()->backwardOnMatrixColumns(inout, rows, cols);
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
