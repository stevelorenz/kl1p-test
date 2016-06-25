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

#include "CircularBufferUnitTest.h"
#include "../include/CircularBuffer.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KCircularBufferUnitTest::KCircularBufferUnitTest() : Test::Suite()
{
    TEST_ADD(KCircularBufferUnitTest::testDefaultConstructor)
    TEST_ADD(KCircularBufferUnitTest::testCapacityConstructor)
    TEST_ADD(KCircularBufferUnitTest::testCopyConstructor)
    TEST_ADD(KCircularBufferUnitTest::testAffectationOperator)

    TEST_ADD(KCircularBufferUnitTest::testBracketOperator)
    TEST_ADD(KCircularBufferUnitTest::testBracketOperator_Const)

    TEST_ADD(KCircularBufferUnitTest::testPush)
    TEST_ADD(KCircularBufferUnitTest::testPush_Array)
    TEST_ADD(KCircularBufferUnitTest::testPush_Vector)
    TEST_ADD(KCircularBufferUnitTest::testPop)
    TEST_ADD(KCircularBufferUnitTest::testClear)
    TEST_ADD(KCircularBufferUnitTest::testReserve)
    TEST_ADD(KCircularBufferUnitTest::testResize)
    TEST_ADD(KCircularBufferUnitTest::testCapacity)
    TEST_ADD(KCircularBufferUnitTest::testSize)
    TEST_ADD(KCircularBufferUnitTest::testAt)
    TEST_ADD(KCircularBufferUnitTest::testAt_Const)
    TEST_ADD(KCircularBufferUnitTest::testFront)
    TEST_ADD(KCircularBufferUnitTest::testFront_Const)
    TEST_ADD(KCircularBufferUnitTest::testBack)
    TEST_ADD(KCircularBufferUnitTest::testBack_Const)
}

// ---------------------------------------------------------------------------------------------------- //

KCircularBufferUnitTest::~KCircularBufferUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KCircularBufferUnitTest::testDefaultConstructor()
{
    try
    {
        TCircularBuffer<klab::Int32> buffer1;
        TEST_ASSERT(buffer1.capacity() == 128)
        TEST_ASSERT(buffer1.size() == 0)

        TCircularBuffer<klab::DoubleReal> buffer2;
        TEST_ASSERT(buffer2.capacity() == 128)
        TEST_ASSERT(buffer2.size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCircularBufferUnitTest::testCapacityConstructor()
{
    try
    {
        TCircularBuffer<klab::Int32> buffer1(128);
        TEST_ASSERT(buffer1.capacity() == 128)
        TEST_ASSERT(buffer1.size() == 0)

        TCircularBuffer<klab::Int32> buffer2(64);
        TEST_ASSERT(buffer2.capacity() == 64)
        TEST_ASSERT(buffer2.size() == 0)

        TCircularBuffer<klab::Int32> buffer3(1024);
        TEST_ASSERT(buffer3.capacity() == 1024)
        TEST_ASSERT(buffer3.size() == 0)

        TCircularBuffer<klab::DoubleReal> buffer4(50);
        TEST_ASSERT(buffer4.capacity() == 50)
        TEST_ASSERT(buffer4.size() == 0)


        // Limit cases.
        TCircularBuffer<klab::Int32> buffer0(0);
        TEST_ASSERT(buffer0.capacity() == 0)
        TEST_ASSERT(buffer0.size() == 0)

        TCircularBuffer<klab::DoubleReal> buffer00(0);
        TEST_ASSERT(buffer00.capacity() == 0)
        TEST_ASSERT(buffer00.size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCircularBufferUnitTest::testCopyConstructor()
{
    try
    {
        TCircularBuffer<klab::Int32> buffer(8);
        buffer.push(123);
        buffer.push(234);
        buffer.push(-345);
        buffer.push(456);
        buffer.push(-567);
        buffer.push(-345);
        buffer.push(123);
        buffer.push(678);
        buffer.push(789);
        buffer.push(890);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)        
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 456)
        TEST_ASSERT(buffer.at(2) == -567)
        TEST_ASSERT(buffer.at(3) == -345)
        TEST_ASSERT(buffer.at(4) == 123)
        TEST_ASSERT(buffer.at(5) == 678)
        TEST_ASSERT(buffer.at(6) == 789)
        TEST_ASSERT(buffer.at(7) == 890)

        TCircularBuffer<klab::Int32> bufferCopy(buffer);
        TEST_ASSERT(bufferCopy.capacity() == 8)
        TEST_ASSERT(bufferCopy.size() == 8)        
        TEST_ASSERT(bufferCopy.at(0) == -345)
        TEST_ASSERT(bufferCopy.at(1) == 456)
        TEST_ASSERT(bufferCopy.at(2) == -567)
        TEST_ASSERT(bufferCopy.at(3) == -345)
        TEST_ASSERT(bufferCopy.at(4) == 123)
        TEST_ASSERT(bufferCopy.at(5) == 678)
        TEST_ASSERT(bufferCopy.at(6) == 789)
        TEST_ASSERT(bufferCopy.at(7) == 890)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCircularBufferUnitTest::testAffectationOperator()
{
    try
    {
        TCircularBuffer<klab::Int32> buffer(8);
        buffer.push(123);
        buffer.push(234);
        buffer.push(-345);
        buffer.push(456);
        buffer.push(-567);
        buffer.push(-345);
        buffer.push(123);
        buffer.push(678);
        buffer.push(789);
        buffer.push(890);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)        
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 456)
        TEST_ASSERT(buffer.at(2) == -567)
        TEST_ASSERT(buffer.at(3) == -345)
        TEST_ASSERT(buffer.at(4) == 123)
        TEST_ASSERT(buffer.at(5) == 678)
        TEST_ASSERT(buffer.at(6) == 789)
        TEST_ASSERT(buffer.at(7) == 890)

        TCircularBuffer<klab::Int32> bufferCopy;
        bufferCopy = buffer;
        TEST_ASSERT(bufferCopy.capacity() == 8)
        TEST_ASSERT(bufferCopy.size() == 8)        
        TEST_ASSERT(bufferCopy.at(0) == -345)
        TEST_ASSERT(bufferCopy.at(1) == 456)
        TEST_ASSERT(bufferCopy.at(2) == -567)
        TEST_ASSERT(bufferCopy.at(3) == -345)
        TEST_ASSERT(bufferCopy.at(4) == 123)
        TEST_ASSERT(bufferCopy.at(5) == 678)
        TEST_ASSERT(bufferCopy.at(6) == 789)
        TEST_ASSERT(bufferCopy.at(7) == 890)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCircularBufferUnitTest::testBracketOperator()
{
    try
    {
        TCircularBuffer<klab::Int32> buffer(8);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 0)

        buffer.push(123);
        buffer[0] = 1230;
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 1)
        TEST_ASSERT(buffer[0] == 1230)

        buffer.push(234);
        buffer[1] = 2340;
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 2)
        TEST_ASSERT(buffer[0] == 1230)
        TEST_ASSERT(buffer[1] == 2340)

        buffer.push(-345);
        buffer[2] = -3450;
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 3)
        TEST_ASSERT(buffer[0] == 1230)
        TEST_ASSERT(buffer[1] == 2340)
        TEST_ASSERT(buffer[2] == -3450)

        buffer.push(456);
        buffer[3] = 4560;
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 4)
        TEST_ASSERT(buffer[0] == 1230)
        TEST_ASSERT(buffer[1] == 2340)
        TEST_ASSERT(buffer[2] == -3450)
        TEST_ASSERT(buffer[3] == 4560)     


        // Limit cases.
        try                                 {buffer[4]=0; TEST_ASSERT(false)}
        catch(klab::KOutOfBoundException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        TCircularBuffer<klab::Int32> buffer2(8);
        buffer.push(123);
        buffer.push(234);
        buffer.push(345);
        try                                 {buffer2[4]=0; TEST_ASSERT(false)}
        catch(klab::KOutOfBoundException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
        

        TCircularBuffer<klab::Int32> buffer0(0);
        try                                 {buffer0[0]=0; TEST_ASSERT(false)}
        catch(klab::KOutOfBoundException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCircularBufferUnitTest::testBracketOperator_Const()
{
    try
    {
        TCircularBuffer<klab::Int32> buffer(8);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 0)

        buffer.push(123);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 1)
        TEST_ASSERT(buffer[0] == 123)

        buffer.push(234);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 2)
        TEST_ASSERT(buffer[0] == 123)
        TEST_ASSERT(buffer[1] == 234)

        buffer.push(-345);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 3)
        TEST_ASSERT(buffer[0] == 123)
        TEST_ASSERT(buffer[1] == 234)
        TEST_ASSERT(buffer[2] == -345)

        buffer.push(456);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 4)
        TEST_ASSERT(buffer[0] == 123)
        TEST_ASSERT(buffer[1] == 234)
        TEST_ASSERT(buffer[2] == -345)
        TEST_ASSERT(buffer[3] == 456)

        buffer.push(-567);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 5)
        TEST_ASSERT(buffer[0] == 123)
        TEST_ASSERT(buffer[1] == 234)
        TEST_ASSERT(buffer[2] == -345)
        TEST_ASSERT(buffer[3] == 456)
        TEST_ASSERT(buffer[4] == -567)

        buffer.push(-345);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 6)
        TEST_ASSERT(buffer[0] == 123)
        TEST_ASSERT(buffer[1] == 234)
        TEST_ASSERT(buffer[2] == -345)
        TEST_ASSERT(buffer[3] == 456)
        TEST_ASSERT(buffer[4] == -567)
        TEST_ASSERT(buffer[5] == -345)

        buffer.push(123);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 7)
        TEST_ASSERT(buffer[0] == 123)
        TEST_ASSERT(buffer[1] == 234)
        TEST_ASSERT(buffer[2] == -345)
        TEST_ASSERT(buffer[3] == 456)
        TEST_ASSERT(buffer[4] == -567)
        TEST_ASSERT(buffer[5] == -345)
        TEST_ASSERT(buffer[6] == 123)

        buffer.push(678);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)
        TEST_ASSERT(buffer[0] == 123)
        TEST_ASSERT(buffer[1] == 234)
        TEST_ASSERT(buffer[2] == -345)
        TEST_ASSERT(buffer[3] == 456)
        TEST_ASSERT(buffer[4] == -567)
        TEST_ASSERT(buffer[5] == -345)
        TEST_ASSERT(buffer[6] == 123)
        TEST_ASSERT(buffer[7] == 678)

        buffer.push(789);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)        
        TEST_ASSERT(buffer[0] == 234)
        TEST_ASSERT(buffer[1] == -345)
        TEST_ASSERT(buffer[2] == 456)
        TEST_ASSERT(buffer[3] == -567)
        TEST_ASSERT(buffer[4] == -345)
        TEST_ASSERT(buffer[5] == 123)
        TEST_ASSERT(buffer[6] == 678)
        TEST_ASSERT(buffer[7] == 789)

        buffer.push(890);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)        
        TEST_ASSERT(buffer[0] == -345)
        TEST_ASSERT(buffer[1] == 456)
        TEST_ASSERT(buffer[2] == -567)
        TEST_ASSERT(buffer[3] == -345)
        TEST_ASSERT(buffer[4] == 123)
        TEST_ASSERT(buffer[5] == 678)
        TEST_ASSERT(buffer[6] == 789)
        TEST_ASSERT(buffer[7] == 890)


        // Limit cases.
        try                                 {buffer[9]; TEST_ASSERT(false)}
        catch(klab::KOutOfBoundException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        TCircularBuffer<klab::Int32> buffer2(8);
        buffer.push(123);
        buffer.push(234);
        buffer.push(345);
        try                                 {buffer2[4]; TEST_ASSERT(false)}
        catch(klab::KOutOfBoundException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
        

        TCircularBuffer<klab::Int32> buffer0(0);
        try                                 {buffer0[0]; TEST_ASSERT(false)}
        catch(klab::KOutOfBoundException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCircularBufferUnitTest::testPush()
{
    try
    {
        TCircularBuffer<klab::Int32> buffer(8);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 0)

        buffer.push(123);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 1)
        TEST_ASSERT(buffer.at(0) == 123)

        buffer.push(234);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 2)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)

        buffer.push(-345);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 3)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)

        buffer.push(456);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 4)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)

        buffer.push(-567);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 5)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)
        TEST_ASSERT(buffer.at(4) == -567)

        buffer.push(-345);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 6)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)
        TEST_ASSERT(buffer.at(4) == -567)
        TEST_ASSERT(buffer.at(5) == -345)

        buffer.push(123);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 7)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)
        TEST_ASSERT(buffer.at(4) == -567)
        TEST_ASSERT(buffer.at(5) == -345)
        TEST_ASSERT(buffer.at(6) == 123)

        buffer.push(678);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)
        TEST_ASSERT(buffer.at(4) == -567)
        TEST_ASSERT(buffer.at(5) == -345)
        TEST_ASSERT(buffer.at(6) == 123)
        TEST_ASSERT(buffer.at(7) == 678)

        buffer.push(789);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)        
        TEST_ASSERT(buffer.at(0) == 234)
        TEST_ASSERT(buffer.at(1) == -345)
        TEST_ASSERT(buffer.at(2) == 456)
        TEST_ASSERT(buffer.at(3) == -567)
        TEST_ASSERT(buffer.at(4) == -345)
        TEST_ASSERT(buffer.at(5) == 123)
        TEST_ASSERT(buffer.at(6) == 678)
        TEST_ASSERT(buffer.at(7) == 789)

        buffer.push(890);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)        
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 456)
        TEST_ASSERT(buffer.at(2) == -567)
        TEST_ASSERT(buffer.at(3) == -345)
        TEST_ASSERT(buffer.at(4) == 123)
        TEST_ASSERT(buffer.at(5) == 678)
        TEST_ASSERT(buffer.at(6) == 789)
        TEST_ASSERT(buffer.at(7) == 890)

        buffer.push(901);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)                
        TEST_ASSERT(buffer.at(0) == 456)
        TEST_ASSERT(buffer.at(1) == -567)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 123)
        TEST_ASSERT(buffer.at(4) == 678)
        TEST_ASSERT(buffer.at(5) == 789)
        TEST_ASSERT(buffer.at(6) == 890)
        TEST_ASSERT(buffer.at(7) == 901)

        buffer.push(147);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)                        
        TEST_ASSERT(buffer.at(0) == -567)
        TEST_ASSERT(buffer.at(1) == -345)
        TEST_ASSERT(buffer.at(2) == 123)
        TEST_ASSERT(buffer.at(3) == 678)
        TEST_ASSERT(buffer.at(4) == 789)
        TEST_ASSERT(buffer.at(5) == 890)
        TEST_ASSERT(buffer.at(6) == 901)
        TEST_ASSERT(buffer.at(7) == 147)

        buffer.push(472);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)                                
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 123)
        TEST_ASSERT(buffer.at(2) == 678)
        TEST_ASSERT(buffer.at(3) == 789)
        TEST_ASSERT(buffer.at(4) == 890)
        TEST_ASSERT(buffer.at(5) == 901)
        TEST_ASSERT(buffer.at(6) == 147)
        TEST_ASSERT(buffer.at(7) == 472)

        buffer.push(725);
        buffer.push(258);
        buffer.push(583);
        buffer.push(836);
        buffer.push(369);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)                                
        TEST_ASSERT(buffer.at(0) == 901)
        TEST_ASSERT(buffer.at(1) == 147)
        TEST_ASSERT(buffer.at(2) == 472)
        TEST_ASSERT(buffer.at(3) == 725)
        TEST_ASSERT(buffer.at(4) == 258)
        TEST_ASSERT(buffer.at(5) == 583)
        TEST_ASSERT(buffer.at(6) == 836)
        TEST_ASSERT(buffer.at(7) == 369)

        buffer.push(690);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)                                
        TEST_ASSERT(buffer.at(0) == 147)
        TEST_ASSERT(buffer.at(1) == 472)
        TEST_ASSERT(buffer.at(2) == 725)
        TEST_ASSERT(buffer.at(3) == 258)
        TEST_ASSERT(buffer.at(4) == 583)
        TEST_ASSERT(buffer.at(5) == 836)
        TEST_ASSERT(buffer.at(6) == 369)
        TEST_ASSERT(buffer.at(7) == 690)

        buffer.push(0);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)                                        
        TEST_ASSERT(buffer.at(0) == 472)
        TEST_ASSERT(buffer.at(1) == 725)
        TEST_ASSERT(buffer.at(2) == 258)
        TEST_ASSERT(buffer.at(3) == 583)
        TEST_ASSERT(buffer.at(4) == 836)
        TEST_ASSERT(buffer.at(5) == 369)
        TEST_ASSERT(buffer.at(6) == 690)
        TEST_ASSERT(buffer.at(7) == 0)


        // Limit cases.
        TCircularBuffer<klab::Int32> buffer0(0);
        TEST_ASSERT(buffer0.capacity() == 0)
        TEST_ASSERT(buffer0.size() == 0)

        buffer0.push(123);
        TEST_ASSERT(buffer0.capacity() == 0)
        TEST_ASSERT(buffer0.size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCircularBufferUnitTest::testPush_Array()
{
    try
    {
        klab::Int32 array01[] = {123}; 
        klab::Int32 array02[] = {234, -345, 456}; 
        klab::Int32 array03[] = {-567, -678, 789, 890, 901}; 

        TCircularBuffer<klab::Int32> buffer(8);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 0)

        buffer.push(array01, 1);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 1)
        TEST_ASSERT(buffer.at(0) == 123)

        buffer.push(array02, 3);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 4)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)

        buffer.push(array03, 5);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)
        TEST_ASSERT(buffer.at(0) == 234)
        TEST_ASSERT(buffer.at(1) == -345)
        TEST_ASSERT(buffer.at(2) == 456)
        TEST_ASSERT(buffer.at(3) == -567)
        TEST_ASSERT(buffer.at(4) == -678)
        TEST_ASSERT(buffer.at(5) == 789)
        TEST_ASSERT(buffer.at(6) == 890)
        TEST_ASSERT(buffer.at(7) == 901)


        // Limit cases.
        buffer.push(0, 0);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)
        TEST_ASSERT(buffer.at(0) == 234)
        TEST_ASSERT(buffer.at(1) == -345)
        TEST_ASSERT(buffer.at(2) == 456)
        TEST_ASSERT(buffer.at(3) == -567)
        TEST_ASSERT(buffer.at(4) == -678)
        TEST_ASSERT(buffer.at(5) == 789)
        TEST_ASSERT(buffer.at(6) == 890)
        TEST_ASSERT(buffer.at(7) == 901)

        buffer.push(0, 5);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)
        TEST_ASSERT(buffer.at(0) == 234)
        TEST_ASSERT(buffer.at(1) == -345)
        TEST_ASSERT(buffer.at(2) == 456)
        TEST_ASSERT(buffer.at(3) == -567)
        TEST_ASSERT(buffer.at(4) == -678)
        TEST_ASSERT(buffer.at(5) == 789)
        TEST_ASSERT(buffer.at(6) == 890)
        TEST_ASSERT(buffer.at(7) == 901)

        buffer.push(array02, 0);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)
        TEST_ASSERT(buffer.at(0) == 234)
        TEST_ASSERT(buffer.at(1) == -345)
        TEST_ASSERT(buffer.at(2) == 456)
        TEST_ASSERT(buffer.at(3) == -567)
        TEST_ASSERT(buffer.at(4) == -678)
        TEST_ASSERT(buffer.at(5) == 789)
        TEST_ASSERT(buffer.at(6) == 890)
        TEST_ASSERT(buffer.at(7) == 901)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCircularBufferUnitTest::testPush_Vector()
{
    try
    {
        std::vector<klab::Int32> vec01(1);
        vec01[0] = 123;

        std::vector<klab::Int32> vec02(3);
        vec02[0] = 234;
        vec02[1] = -345;
        vec02[2] = 456;

        std::vector<klab::Int32> vec03(5);
        vec03[0] = -567;
        vec03[1] = -678;
        vec03[2] = 789;
        vec03[3] = 890;
        vec03[4] = 901;


        TCircularBuffer<klab::Int32> buffer(8);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 0)

        buffer.push(vec01);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 1)
        TEST_ASSERT(buffer.at(0) == 123)

        buffer.push(vec02);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 4)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)

        buffer.push(vec03);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)
        TEST_ASSERT(buffer.at(0) == 234)
        TEST_ASSERT(buffer.at(1) == -345)
        TEST_ASSERT(buffer.at(2) == 456)
        TEST_ASSERT(buffer.at(3) == -567)
        TEST_ASSERT(buffer.at(4) == -678)
        TEST_ASSERT(buffer.at(5) == 789)
        TEST_ASSERT(buffer.at(6) == 890)
        TEST_ASSERT(buffer.at(7) == 901)


        // Limit cases.
        buffer.push(std::vector<klab::Int32>());
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)
        TEST_ASSERT(buffer.at(0) == 234)
        TEST_ASSERT(buffer.at(1) == -345)
        TEST_ASSERT(buffer.at(2) == 456)
        TEST_ASSERT(buffer.at(3) == -567)
        TEST_ASSERT(buffer.at(4) == -678)
        TEST_ASSERT(buffer.at(5) == 789)
        TEST_ASSERT(buffer.at(6) == 890)
        TEST_ASSERT(buffer.at(7) == 901)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCircularBufferUnitTest::testPop()
{
    try
    {
        TCircularBuffer<klab::Int32> buffer(8);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 0)

        buffer.push(123);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 1)
        TEST_ASSERT(buffer.at(0) == 123)

        buffer.pop();
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 0)

        buffer.pop();
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 0)

        buffer.push(123);
        buffer.push(234);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 2)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)

        buffer.pop();
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 1)
        TEST_ASSERT(buffer.at(0) == 123)

        buffer.push(-345);
        buffer.push(456);
        buffer.push(-567);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 4)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == -345)
        TEST_ASSERT(buffer.at(2) == 456)
        TEST_ASSERT(buffer.at(3) == -567)

        buffer.pop();
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 3)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == -345)
        TEST_ASSERT(buffer.at(2) == 456)

        buffer.push(-345);
        buffer.push(123);
        buffer.push(678);
        buffer.push(789);
        buffer.push(890);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == -345)
        TEST_ASSERT(buffer.at(2) == 456)
        TEST_ASSERT(buffer.at(3) == -345)
        TEST_ASSERT(buffer.at(4) == 123)
        TEST_ASSERT(buffer.at(5) == 678)
        TEST_ASSERT(buffer.at(6) == 789)
        TEST_ASSERT(buffer.at(7) == 890)

        buffer.pop();
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 7)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == -345)
        TEST_ASSERT(buffer.at(2) == 456)
        TEST_ASSERT(buffer.at(3) == -345)
        TEST_ASSERT(buffer.at(4) == 123)
        TEST_ASSERT(buffer.at(5) == 678)
        TEST_ASSERT(buffer.at(6) == 789)

        buffer.push(890);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == -345)
        TEST_ASSERT(buffer.at(2) == 456)
        TEST_ASSERT(buffer.at(3) == -345)
        TEST_ASSERT(buffer.at(4) == 123)
        TEST_ASSERT(buffer.at(5) == 678)
        TEST_ASSERT(buffer.at(6) == 789)
        TEST_ASSERT(buffer.at(7) == 890)

        buffer.push(901);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)        
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 456)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 123)
        TEST_ASSERT(buffer.at(4) == 678)
        TEST_ASSERT(buffer.at(5) == 789)
        TEST_ASSERT(buffer.at(6) == 890)
        TEST_ASSERT(buffer.at(7) == 901)

        buffer.pop();
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 7)        
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 456)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 123)
        TEST_ASSERT(buffer.at(4) == 678)
        TEST_ASSERT(buffer.at(5) == 789)
        TEST_ASSERT(buffer.at(6) == 890)

        buffer.push(147);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)                              
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 456)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 123)
        TEST_ASSERT(buffer.at(4) == 678)
        TEST_ASSERT(buffer.at(5) == 789)
        TEST_ASSERT(buffer.at(6) == 890)
        TEST_ASSERT(buffer.at(7) == 147)

        buffer.push(472);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)                                        
        TEST_ASSERT(buffer.at(0) == 456)
        TEST_ASSERT(buffer.at(1) == -345)
        TEST_ASSERT(buffer.at(2) == 123)
        TEST_ASSERT(buffer.at(3) == 678)
        TEST_ASSERT(buffer.at(4) == 789)
        TEST_ASSERT(buffer.at(5) == 890)
        TEST_ASSERT(buffer.at(6) == 147)
        TEST_ASSERT(buffer.at(7) == 472)

        buffer.pop();
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 7)        
        TEST_ASSERT(buffer.at(0) == 456)
        TEST_ASSERT(buffer.at(1) == -345)
        TEST_ASSERT(buffer.at(2) == 123)
        TEST_ASSERT(buffer.at(3) == 678)
        TEST_ASSERT(buffer.at(4) == 789)
        TEST_ASSERT(buffer.at(5) == 890)
        TEST_ASSERT(buffer.at(6) == 147)

        buffer.pop();
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 6)        
        TEST_ASSERT(buffer.at(0) == 456)
        TEST_ASSERT(buffer.at(1) == -345)
        TEST_ASSERT(buffer.at(2) == 123)
        TEST_ASSERT(buffer.at(3) == 678)
        TEST_ASSERT(buffer.at(4) == 789)
        TEST_ASSERT(buffer.at(5) == 890)

        buffer.pop();
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 5)        
        TEST_ASSERT(buffer.at(0) == 456)
        TEST_ASSERT(buffer.at(1) == -345)
        TEST_ASSERT(buffer.at(2) == 123)
        TEST_ASSERT(buffer.at(3) == 678)
        TEST_ASSERT(buffer.at(4) == 789)

        buffer.pop();
        buffer.pop();
        buffer.pop();
        buffer.pop();
        buffer.pop();
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 0)

        buffer.pop();
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 0)


        // Limit cases.
        TCircularBuffer<klab::Int32> buffer0(0);
        TEST_ASSERT(buffer0.capacity() == 0)
        TEST_ASSERT(buffer0.size() == 0)

        buffer0.pop();
        TEST_ASSERT(buffer0.capacity() == 0)
        TEST_ASSERT(buffer0.size() == 0)

        buffer0.pop();
        TEST_ASSERT(buffer0.capacity() == 0)
        TEST_ASSERT(buffer0.size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCircularBufferUnitTest::testClear()
{
    try
    {
        TCircularBuffer<klab::Int32> buffer(8);
        buffer.push(123);
        buffer.push(234);
        buffer.push(-345);
        buffer.push(456);
        buffer.push(-567);
        buffer.push(-345);
        buffer.push(123);
        buffer.push(678);
        buffer.push(789);
        buffer.push(890);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)        
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 456)
        TEST_ASSERT(buffer.at(2) == -567)
        TEST_ASSERT(buffer.at(3) == -345)
        TEST_ASSERT(buffer.at(4) == 123)
        TEST_ASSERT(buffer.at(5) == 678)
        TEST_ASSERT(buffer.at(6) == 789)
        TEST_ASSERT(buffer.at(7) == 890)

        buffer.clear();
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 0) 

        buffer.clear();
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 0) 

        buffer.push(123);
        buffer.push(234);
        buffer.push(-345);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 3)        
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)


        // Limit cases.
        TCircularBuffer<klab::Int32> buffer0(0);
        TEST_ASSERT(buffer0.capacity() == 0)
        TEST_ASSERT(buffer0.size() == 0)

        buffer0.clear();
        TEST_ASSERT(buffer0.capacity() == 0)
        TEST_ASSERT(buffer0.size() == 0)

        buffer0.clear();
        TEST_ASSERT(buffer0.capacity() == 0)
        TEST_ASSERT(buffer0.size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCircularBufferUnitTest::testReserve()
{
    try
    {
        TCircularBuffer<klab::Int32> buffer(8);
        buffer.push(123);
        buffer.push(234);
        buffer.push(-345);
        buffer.push(456);
        buffer.push(-567);
        buffer.push(-345);
        buffer.push(123);
        buffer.push(678);
        buffer.push(789);
        buffer.push(890);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)        
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 456)
        TEST_ASSERT(buffer.at(2) == -567)
        TEST_ASSERT(buffer.at(3) == -345)
        TEST_ASSERT(buffer.at(4) == 123)
        TEST_ASSERT(buffer.at(5) == 678)
        TEST_ASSERT(buffer.at(6) == 789)
        TEST_ASSERT(buffer.at(7) == 890)

        buffer.reserve(16);
        TEST_ASSERT(buffer.capacity() == 16)
        TEST_ASSERT(buffer.size() == 0)  
        buffer.push(123);
        buffer.push(234);
        TEST_ASSERT(buffer.capacity() == 16)
        TEST_ASSERT(buffer.size() == 2)  
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)

        buffer.reserve(2);
        TEST_ASSERT(buffer.capacity() == 2)
        TEST_ASSERT(buffer.size() == 0) 
        buffer.push(123);
        buffer.push(234);
        TEST_ASSERT(buffer.capacity() == 2)
        TEST_ASSERT(buffer.size() == 2)  
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)

        buffer.reserve(32);
        TEST_ASSERT(buffer.capacity() == 32)
        TEST_ASSERT(buffer.size() == 0)
        buffer.push(123);
        buffer.push(234);
        TEST_ASSERT(buffer.capacity() == 32)
        TEST_ASSERT(buffer.size() == 2)  
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)


        // Limit cases.
        buffer.reserve(0);
        TEST_ASSERT(buffer.capacity() == 0)
        TEST_ASSERT(buffer.size() == 0)  

        buffer.reserve(8);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 0)  
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCircularBufferUnitTest::testResize()
{
    try
    {
        TCircularBuffer<klab::Int32> buffer(8);
        buffer.push(123);
        buffer.push(234);
        buffer.push(-345);
        buffer.push(456);
        buffer.push(-567);
        buffer.push(-345);
        buffer.push(123);
        buffer.push(678);
        buffer.push(789);
        buffer.push(890);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)        
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 456)
        TEST_ASSERT(buffer.at(2) == -567)
        TEST_ASSERT(buffer.at(3) == -345)
        TEST_ASSERT(buffer.at(4) == 123)
        TEST_ASSERT(buffer.at(5) == 678)
        TEST_ASSERT(buffer.at(6) == 789)
        TEST_ASSERT(buffer.at(7) == 890)

        buffer.resize(4);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 4)   
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 456)
        TEST_ASSERT(buffer.at(2) == -567)
        TEST_ASSERT(buffer.at(3) == -345)

        buffer.push(678);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 5)           
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 456)
        TEST_ASSERT(buffer.at(2) == -567)
        TEST_ASSERT(buffer.at(3) == -345)
        TEST_ASSERT(buffer.at(4) == 678)

        buffer.resize(6);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 6)   
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 456)
        TEST_ASSERT(buffer.at(2) == -567)
        TEST_ASSERT(buffer.at(3) == -345)
        TEST_ASSERT(buffer.at(4) == 678)
        TEST_ASSERT(buffer.at(5) == 0)

        buffer.push(789);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 7)           
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 456)
        TEST_ASSERT(buffer.at(2) == -567)
        TEST_ASSERT(buffer.at(3) == -345)
        TEST_ASSERT(buffer.at(4) == 678)
        TEST_ASSERT(buffer.at(5) == 0)
        TEST_ASSERT(buffer.at(6) == 789)

        buffer.resize(2, 3);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 2)   
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 456)

        buffer.push(890);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 3)           
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 456)
        TEST_ASSERT(buffer.at(2) == 890)

        buffer.resize(8, 3);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)   
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 456)
        TEST_ASSERT(buffer.at(2) == 890)
        TEST_ASSERT(buffer.at(3) == 3)
        TEST_ASSERT(buffer.at(4) == 3)
        TEST_ASSERT(buffer.at(5) == 3)
        TEST_ASSERT(buffer.at(6) == 3)
        TEST_ASSERT(buffer.at(7) == 3)

        buffer.push(901);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)           
        TEST_ASSERT(buffer.at(0) == 456)
        TEST_ASSERT(buffer.at(1) == 890)
        TEST_ASSERT(buffer.at(2) == 3)
        TEST_ASSERT(buffer.at(3) == 3)
        TEST_ASSERT(buffer.at(4) == 3)
        TEST_ASSERT(buffer.at(5) == 3)
        TEST_ASSERT(buffer.at(6) == 3)
        TEST_ASSERT(buffer.at(7) == 901)

        buffer.resize(3);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 3)   
        TEST_ASSERT(buffer.at(0) == 456)
        TEST_ASSERT(buffer.at(1) == 890)
        TEST_ASSERT(buffer.at(2) == 3)

        buffer.resize(11);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)   
        TEST_ASSERT(buffer.at(0) == 456)
        TEST_ASSERT(buffer.at(1) == 890)
        TEST_ASSERT(buffer.at(2) == 3)
        TEST_ASSERT(buffer.at(3) == 0)
        TEST_ASSERT(buffer.at(4) == 0)
        TEST_ASSERT(buffer.at(5) == 0)
        TEST_ASSERT(buffer.at(6) == 0)
        TEST_ASSERT(buffer.at(7) == 0)

        buffer.resize(16);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)   
        TEST_ASSERT(buffer.at(0) == 456)
        TEST_ASSERT(buffer.at(1) == 890)
        TEST_ASSERT(buffer.at(2) == 3)
        TEST_ASSERT(buffer.at(3) == 0)
        TEST_ASSERT(buffer.at(4) == 0)
        TEST_ASSERT(buffer.at(5) == 0)
        TEST_ASSERT(buffer.at(6) == 0)
        TEST_ASSERT(buffer.at(7) == 0)


        // Limit cases.
        buffer.resize(0);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 0)  

        buffer.resize(4);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 4) 
        TEST_ASSERT(buffer.at(0) == 0)
        TEST_ASSERT(buffer.at(1) == 0)
        TEST_ASSERT(buffer.at(2) == 0)
        TEST_ASSERT(buffer.at(3) == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCircularBufferUnitTest::testCapacity()
{
    try
    {
        TCircularBuffer<klab::Int32> buffer(8);
        buffer.push(123);
        buffer.push(234);
        buffer.push(-345);
        buffer.push(456);
        buffer.push(-567);
        buffer.push(-345);
        buffer.push(123);
        buffer.push(678);
        buffer.push(789);
        buffer.push(890);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)        
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 456)
        TEST_ASSERT(buffer.at(2) == -567)
        TEST_ASSERT(buffer.at(3) == -345)
        TEST_ASSERT(buffer.at(4) == 123)
        TEST_ASSERT(buffer.at(5) == 678)
        TEST_ASSERT(buffer.at(6) == 789)
        TEST_ASSERT(buffer.at(7) == 890)

        buffer.push(901);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)                
        TEST_ASSERT(buffer.at(0) == 456)
        TEST_ASSERT(buffer.at(1) == -567)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 123)
        TEST_ASSERT(buffer.at(4) == 678)
        TEST_ASSERT(buffer.at(5) == 789)
        TEST_ASSERT(buffer.at(6) == 890)
        TEST_ASSERT(buffer.at(7) == 901)


        // Limit cases.
        TCircularBuffer<klab::Int32> buffer0(0);
        TEST_ASSERT(buffer0.capacity() == 0)
        TEST_ASSERT(buffer0.size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCircularBufferUnitTest::testSize()
{
    try
    {
        TCircularBuffer<klab::Int32> buffer(8);
        buffer.push(123);
        buffer.push(234);
        buffer.push(-345);
        buffer.push(456);
        buffer.push(-567);
        buffer.push(-345);
        buffer.push(123);
        buffer.push(678);
        buffer.push(789);
        buffer.push(890);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)        
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 456)
        TEST_ASSERT(buffer.at(2) == -567)
        TEST_ASSERT(buffer.at(3) == -345)
        TEST_ASSERT(buffer.at(4) == 123)
        TEST_ASSERT(buffer.at(5) == 678)
        TEST_ASSERT(buffer.at(6) == 789)
        TEST_ASSERT(buffer.at(7) == 890)

        buffer.push(901);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)                
        TEST_ASSERT(buffer.at(0) == 456)
        TEST_ASSERT(buffer.at(1) == -567)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 123)
        TEST_ASSERT(buffer.at(4) == 678)
        TEST_ASSERT(buffer.at(5) == 789)
        TEST_ASSERT(buffer.at(6) == 890)
        TEST_ASSERT(buffer.at(7) == 901)


        // Limit cases.
        TCircularBuffer<klab::Int32> buffer0(0);
        TEST_ASSERT(buffer0.capacity() == 0)
        TEST_ASSERT(buffer0.size() == 0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCircularBufferUnitTest::testAt()
{
    try
    {
        TCircularBuffer<klab::Int32> buffer(8);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 0)

        buffer.push(123);
        buffer.at(0) = 1230;
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 1)
        TEST_ASSERT(buffer.at(0) == 1230)

        buffer.push(234);
        buffer.at(1) = 2340;
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 2)
        TEST_ASSERT(buffer.at(0) == 1230)
        TEST_ASSERT(buffer.at(1) == 2340)

        buffer.push(-345);
        buffer.at(2) = -3450;
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 3)
        TEST_ASSERT(buffer.at(0) == 1230)
        TEST_ASSERT(buffer.at(1) == 2340)
        TEST_ASSERT(buffer.at(2) == -3450)

        buffer.push(456);
        buffer.at(3) = 4560;
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 4)
        TEST_ASSERT(buffer.at(0) == 1230)
        TEST_ASSERT(buffer.at(1) == 2340)
        TEST_ASSERT(buffer.at(2) == -3450)
        TEST_ASSERT(buffer.at(3) == 4560)     


        // Limit cases.
        try                                 {buffer.at(4)=0; TEST_ASSERT(false)}
        catch(klab::KOutOfBoundException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        TCircularBuffer<klab::Int32> buffer2(8);
        buffer.push(123);
        buffer.push(234);
        buffer.push(345);
        try                                 {buffer2.at(4)=0; TEST_ASSERT(false)}
        catch(klab::KOutOfBoundException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
        

        TCircularBuffer<klab::Int32> buffer0(0);
        try                                 {buffer0.at(0)=0; TEST_ASSERT(false)}
        catch(klab::KOutOfBoundException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCircularBufferUnitTest::testAt_Const()
{
    try
    {
        TCircularBuffer<klab::Int32> buffer(8);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 0)

        buffer.push(123);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 1)
        TEST_ASSERT(buffer.at(0) == 123)

        buffer.push(234);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 2)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)

        buffer.push(-345);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 3)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)

        buffer.push(456);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 4)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)

        buffer.push(-567);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 5)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)
        TEST_ASSERT(buffer.at(4) == -567)

        buffer.push(-345);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 6)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)
        TEST_ASSERT(buffer.at(4) == -567)
        TEST_ASSERT(buffer.at(5) == -345)

        buffer.push(123);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 7)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)
        TEST_ASSERT(buffer.at(4) == -567)
        TEST_ASSERT(buffer.at(5) == -345)
        TEST_ASSERT(buffer.at(6) == 123)

        buffer.push(678);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)
        TEST_ASSERT(buffer.at(4) == -567)
        TEST_ASSERT(buffer.at(5) == -345)
        TEST_ASSERT(buffer.at(6) == 123)
        TEST_ASSERT(buffer.at(7) == 678)

        buffer.push(789);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)        
        TEST_ASSERT(buffer.at(0) == 234)
        TEST_ASSERT(buffer.at(1) == -345)
        TEST_ASSERT(buffer.at(2) == 456)
        TEST_ASSERT(buffer.at(3) == -567)
        TEST_ASSERT(buffer.at(4) == -345)
        TEST_ASSERT(buffer.at(5) == 123)
        TEST_ASSERT(buffer.at(6) == 678)
        TEST_ASSERT(buffer.at(7) == 789)

        buffer.push(890);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)        
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 456)
        TEST_ASSERT(buffer.at(2) == -567)
        TEST_ASSERT(buffer.at(3) == -345)
        TEST_ASSERT(buffer.at(4) == 123)
        TEST_ASSERT(buffer.at(5) == 678)
        TEST_ASSERT(buffer.at(6) == 789)
        TEST_ASSERT(buffer.at(7) == 890)


        // Limit cases.
        try                                 {buffer.at(9); TEST_ASSERT(false)}
        catch(klab::KOutOfBoundException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}

        TCircularBuffer<klab::Int32> buffer2(8);
        buffer.push(123);
        buffer.push(234);
        buffer.push(345);
        try                                 {buffer2.at(4); TEST_ASSERT(false)}
        catch(klab::KOutOfBoundException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
        

        TCircularBuffer<klab::Int32> buffer0(0);
        try                                 {buffer0.at(0); TEST_ASSERT(false)}
        catch(klab::KOutOfBoundException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCircularBufferUnitTest::testFront()
{
    try
    {
        TCircularBuffer<klab::Int32> buffer(8);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 0)

        buffer.push(123);
        buffer.front() = 1230;
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 1)
        TEST_ASSERT(buffer.at(0) == 1230)

        buffer.push(234);
        buffer.front() = 2340;
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 2)
        TEST_ASSERT(buffer.at(0) == 2340)
        TEST_ASSERT(buffer.at(1) == 234)

        buffer.push(-345);
        buffer.front() = -3450;
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 3)
        TEST_ASSERT(buffer.at(0) == -3450)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)

        buffer.push(456);
        buffer.front() = 4560;
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 4)
        TEST_ASSERT(buffer.at(0) == 4560)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)     


        // Limit cases.
        TCircularBuffer<klab::Int32> buffer0;
        try                                 {buffer0.front()=0; TEST_ASSERT(false)}
        catch(klab::KOutOfBoundException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCircularBufferUnitTest::testFront_Const()
{
    try
    {
        TCircularBuffer<klab::Int32> buffer(8);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 0)        

        buffer.push(123);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 1)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.front() == 123)
        TEST_ASSERT(buffer.back() == 123)

        buffer.push(234);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 2)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.front() == 123)
        TEST_ASSERT(buffer.back() == 234)

        buffer.push(-345);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 3)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.front() == 123)
        TEST_ASSERT(buffer.back() == -345)

        buffer.push(456);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 4)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)
        TEST_ASSERT(buffer.front() == 123)
        TEST_ASSERT(buffer.back() == 456)

        buffer.push(-567);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 5)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)
        TEST_ASSERT(buffer.at(4) == -567)
        TEST_ASSERT(buffer.front() == 123)
        TEST_ASSERT(buffer.back() == -567)

        buffer.push(-345);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 6)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)
        TEST_ASSERT(buffer.at(4) == -567)
        TEST_ASSERT(buffer.at(5) == -345)
        TEST_ASSERT(buffer.front() == 123)
        TEST_ASSERT(buffer.back() == -345)

        buffer.push(123);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 7)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)
        TEST_ASSERT(buffer.at(4) == -567)
        TEST_ASSERT(buffer.at(5) == -345)
        TEST_ASSERT(buffer.at(6) == 123)
        TEST_ASSERT(buffer.front() == 123)
        TEST_ASSERT(buffer.back() == 123)

        buffer.push(678);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)
        TEST_ASSERT(buffer.at(4) == -567)
        TEST_ASSERT(buffer.at(5) == -345)
        TEST_ASSERT(buffer.at(6) == 123)
        TEST_ASSERT(buffer.at(7) == 678)
        TEST_ASSERT(buffer.front() == 123)
        TEST_ASSERT(buffer.back() == 678)

        buffer.push(789);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)        
        TEST_ASSERT(buffer.at(0) == 234)
        TEST_ASSERT(buffer.at(1) == -345)
        TEST_ASSERT(buffer.at(2) == 456)
        TEST_ASSERT(buffer.at(3) == -567)
        TEST_ASSERT(buffer.at(4) == -345)
        TEST_ASSERT(buffer.at(5) == 123)
        TEST_ASSERT(buffer.at(6) == 678)
        TEST_ASSERT(buffer.at(7) == 789)
        TEST_ASSERT(buffer.front() == 234)
        TEST_ASSERT(buffer.back() == 789)

        buffer.push(890);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)        
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 456)
        TEST_ASSERT(buffer.at(2) == -567)
        TEST_ASSERT(buffer.at(3) == -345)
        TEST_ASSERT(buffer.at(4) == 123)
        TEST_ASSERT(buffer.at(5) == 678)
        TEST_ASSERT(buffer.at(6) == 789)
        TEST_ASSERT(buffer.at(7) == 890)
        TEST_ASSERT(buffer.front() == -345)
        TEST_ASSERT(buffer.back() == 890)


        // Limit cases.
        TCircularBuffer<klab::Int32> buffer0;
        try                                 {buffer0.front(); TEST_ASSERT(false)}
        catch(klab::KOutOfBoundException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCircularBufferUnitTest::testBack()
{
    try
    {
        TCircularBuffer<klab::Int32> buffer(8);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 0)

        buffer.push(123);
        buffer.back() = 1230;
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 1)
        TEST_ASSERT(buffer.at(0) == 1230)

        buffer.push(234);
        buffer.back() = 2340;
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 2)
        TEST_ASSERT(buffer.at(0) == 1230)
        TEST_ASSERT(buffer.at(1) == 2340)

        buffer.push(-345);
        buffer.back() = -3450;
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 3)
        TEST_ASSERT(buffer.at(0) == 1230)
        TEST_ASSERT(buffer.at(1) == 2340)
        TEST_ASSERT(buffer.at(2) == -3450)

        buffer.push(456);
        buffer.back() = 4560;
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 4)
        TEST_ASSERT(buffer.at(0) == 1230)
        TEST_ASSERT(buffer.at(1) == 2340)
        TEST_ASSERT(buffer.at(2) == -3450)
        TEST_ASSERT(buffer.at(3) == 4560)     


        // Limit cases.
        TCircularBuffer<klab::Int32> buffer0;
        try                                 {buffer0.back()=0; TEST_ASSERT(false)}
        catch(klab::KOutOfBoundException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KCircularBufferUnitTest::testBack_Const()
{
    try
    {
        TCircularBuffer<klab::Int32> buffer(8);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 0)        

        buffer.push(123);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 1)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.front() == 123)
        TEST_ASSERT(buffer.back() == 123)

        buffer.push(234);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 2)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.front() == 123)
        TEST_ASSERT(buffer.back() == 234)

        buffer.push(-345);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 3)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.front() == 123)
        TEST_ASSERT(buffer.back() == -345)

        buffer.push(456);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 4)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)
        TEST_ASSERT(buffer.front() == 123)
        TEST_ASSERT(buffer.back() == 456)

        buffer.push(-567);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 5)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)
        TEST_ASSERT(buffer.at(4) == -567)
        TEST_ASSERT(buffer.front() == 123)
        TEST_ASSERT(buffer.back() == -567)

        buffer.push(-345);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 6)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)
        TEST_ASSERT(buffer.at(4) == -567)
        TEST_ASSERT(buffer.at(5) == -345)
        TEST_ASSERT(buffer.front() == 123)
        TEST_ASSERT(buffer.back() == -345)

        buffer.push(123);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 7)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)
        TEST_ASSERT(buffer.at(4) == -567)
        TEST_ASSERT(buffer.at(5) == -345)
        TEST_ASSERT(buffer.at(6) == 123)
        TEST_ASSERT(buffer.front() == 123)
        TEST_ASSERT(buffer.back() == 123)

        buffer.push(678);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)
        TEST_ASSERT(buffer.at(0) == 123)
        TEST_ASSERT(buffer.at(1) == 234)
        TEST_ASSERT(buffer.at(2) == -345)
        TEST_ASSERT(buffer.at(3) == 456)
        TEST_ASSERT(buffer.at(4) == -567)
        TEST_ASSERT(buffer.at(5) == -345)
        TEST_ASSERT(buffer.at(6) == 123)
        TEST_ASSERT(buffer.at(7) == 678)
        TEST_ASSERT(buffer.front() == 123)
        TEST_ASSERT(buffer.back() == 678)

        buffer.push(789);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)        
        TEST_ASSERT(buffer.at(0) == 234)
        TEST_ASSERT(buffer.at(1) == -345)
        TEST_ASSERT(buffer.at(2) == 456)
        TEST_ASSERT(buffer.at(3) == -567)
        TEST_ASSERT(buffer.at(4) == -345)
        TEST_ASSERT(buffer.at(5) == 123)
        TEST_ASSERT(buffer.at(6) == 678)
        TEST_ASSERT(buffer.at(7) == 789)
        TEST_ASSERT(buffer.front() == 234)
        TEST_ASSERT(buffer.back() == 789)

        buffer.push(890);
        TEST_ASSERT(buffer.capacity() == 8)
        TEST_ASSERT(buffer.size() == 8)        
        TEST_ASSERT(buffer.at(0) == -345)
        TEST_ASSERT(buffer.at(1) == 456)
        TEST_ASSERT(buffer.at(2) == -567)
        TEST_ASSERT(buffer.at(3) == -345)
        TEST_ASSERT(buffer.at(4) == 123)
        TEST_ASSERT(buffer.at(5) == 678)
        TEST_ASSERT(buffer.at(6) == 789)
        TEST_ASSERT(buffer.at(7) == 890)
        TEST_ASSERT(buffer.front() == -345)
        TEST_ASSERT(buffer.back() == 890)


        // Limit cases.
        TCircularBuffer<klab::Int32> buffer0;
        try                                 {buffer0.back(); TEST_ASSERT(false)}
        catch(klab::KOutOfBoundException&)  {TEST_ASSERT(true)}
        catch(...)                          {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
