// KLab - A portable C++ collection of classes for general purpose.
// Copyright (c) 2011-2012 René Gebel
// 
// This file is part of the KLab C++ library.
// This library is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY of fitness for any purpose. 
//
// This library is free software; You can redistribute it and/or modify it 
// under the terms of the GNU Lesser General Public License (LGPL) 
// as published by the Free Software Foundation, either version 3 of the License,
// or (at your option) any later version.
// See http://www.opensource.org/licenses for more info.

#ifndef KLAB_SINGLETON_H
#define KLAB_SINGLETON_H

#include "TypeUtil.h"
#include "FuncUtil.h"




namespace klab
{
  
// ---------------------------------------------------------------------------------------------------- //

template<class T>
class TSingleton
{
public:

    virtual ~TSingleton();

    static T&       Instance();


protected:

    TSingleton();
	
	
private:

    TSingleton(const TSingleton<T>& singleton);
    TSingleton<T>&  operator=(const TSingleton<T>& singleton);
};

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSingleton<T>::TSingleton()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline TSingleton<T>::~TSingleton()
{}

// ---------------------------------------------------------------------------------------------------- //

template<class T>
inline T& TSingleton<T>::Instance()
{
    static T InstanceOfT;
    return InstanceOfT;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
