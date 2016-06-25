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

#ifndef KLAB_KLABTEST_H
#define KLAB_KLABTEST_H

#include <cpptest.h>




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

class KLabTest
{
public:
    
    KLabTest();
    virtual ~KLabTest();
    
    bool        run();


private:

    KLabTest(const KLabTest& test);
    KLabTest&       operator=(const KLabTest& test);
};

// ---------------------------------------------------------------------------------------------------- //

}


#endif
