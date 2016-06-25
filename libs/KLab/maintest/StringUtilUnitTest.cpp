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

#include "StringUtilUnitTest.h"
#include "../include/StringUtil.h"

using namespace klab;




// ---------------------------------------------------------------------------------------------------- //

KStringUtilUnitTest::KStringUtilUnitTest() : Test::Suite()
{
    TEST_ADD(KStringUtilUnitTest::testToLowerCase)
    TEST_ADD(KStringUtilUnitTest::testToUpperCase)
    TEST_ADD(KStringUtilUnitTest::testCompare)
    TEST_ADD(KStringUtilUnitTest::testEquals)
    TEST_ADD(KStringUtilUnitTest::testTrimLeftString)
    TEST_ADD(KStringUtilUnitTest::testTrimRightString)
    TEST_ADD(KStringUtilUnitTest::testTrimString)
    TEST_ADD(KStringUtilUnitTest::testToLeftTrimmedString)
    TEST_ADD(KStringUtilUnitTest::testToRightTrimmedString)
    TEST_ADD(KStringUtilUnitTest::testToTrimmedString)
    TEST_ADD(KStringUtilUnitTest::testToString)
    TEST_ADD(KStringUtilUnitTest::testToWString)
    TEST_ADD(KStringUtilUnitTest::testConvertStringTo)
}

// ---------------------------------------------------------------------------------------------------- //

KStringUtilUnitTest::~KStringUtilUnitTest()
{}

// ---------------------------------------------------------------------------------------------------- //

void KStringUtilUnitTest::testToLowerCase()
{
    try
    {
        std::string str1("std::string Unit-Test !");
        TEST_ASSERT(klab::ToLowerCase(str1) == "std::string unit-test !")

        std::string str2("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890");
        TEST_ASSERT(klab::ToLowerCase(str2) == "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz1234567890")

        std::wstring wstr1(L"std::wstring Unit-Test !");
        TEST_ASSERT(klab::ToLowerCase(wstr1) == L"std::wstring unit-test !")

        std::wstring wstr2(L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890");
        TEST_ASSERT(klab::ToLowerCase(wstr2) == L"abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz1234567890")


        // Limit cases.
        std::string str3("");
        TEST_ASSERT(klab::ToLowerCase(str3) == "")

        std::wstring wstr3(L"");
        TEST_ASSERT(klab::ToLowerCase(wstr3) == L"")
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KStringUtilUnitTest::testToUpperCase()
{
    try
    {
        std::string str1("std::string Unit-Test !");
        TEST_ASSERT(klab::ToUpperCase(str1) == "STD::STRING UNIT-TEST !")

        std::string str2("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890");
        TEST_ASSERT(klab::ToUpperCase(str2) == "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890")

        std::wstring wstr1(L"std::wstring Unit-Test !");
        TEST_ASSERT(klab::ToUpperCase(wstr1) == L"STD::WSTRING UNIT-TEST !")

        std::wstring wstr2(L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890");
        TEST_ASSERT(klab::ToUpperCase(wstr2) == L"ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890")


        // Limit cases.
        std::string str3("");
        TEST_ASSERT(klab::ToUpperCase(str3) == "")

        std::wstring wstr3(L"");
        TEST_ASSERT(klab::ToUpperCase(wstr3) == L"")
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KStringUtilUnitTest::testCompare()
{
    try
    {
        std::string str1("String unit test !");
        std::string str2(str1);
        std::string str3("string unit test !");
        std::string str4("String unit test");

        TEST_ASSERT(klab::Compare(str1, str2)==0 && klab::Compare(str2, str1)==0)
        TEST_ASSERT(klab::Compare("", str1)<0 && klab::Compare(str1, "")>0)
        TEST_ASSERT(klab::Compare(str1, str3)<0 && klab::Compare(str3, str1)>0)
        TEST_ASSERT(klab::Compare(str1, str4)>0 && klab::Compare(str4, str1)<0) 
        TEST_ASSERT(klab::Compare(str1, "String unit test !")==0 && klab::Compare("String unit test !", str1)==0)

        TEST_ASSERT(klab::Compare(str1, str2, false)==0 && klab::Compare(str2, str1, false)==0)
        TEST_ASSERT(klab::Compare("", str1, false)<0 && klab::Compare(str1, "", false)>0)
        TEST_ASSERT(klab::Compare(str1, str3, false)==0 && klab::Compare(str3, str1, false)==0)
        TEST_ASSERT(klab::Compare(str1, str4, false)>0 && klab::Compare(str4, str1, false)<0) 
        TEST_ASSERT(klab::Compare(str1, "String unit test !", false)==0 && klab::Compare("String unit test !", str1, false)==0)


        std::wstring wstr1(L"String unit test !");
        std::wstring wstr2(wstr1);
        std::wstring wstr3(L"string unit test !");
        std::wstring wstr4(L"String unit test");

        TEST_ASSERT(klab::Compare(wstr1, wstr2)==0 && klab::Compare(wstr2, wstr1)==0)
        TEST_ASSERT(klab::Compare(L"", wstr1)<0 && klab::Compare(wstr1, L"")>0)
        TEST_ASSERT(klab::Compare(wstr1, wstr3)<0 && klab::Compare(wstr3, wstr1)>0)
        TEST_ASSERT(klab::Compare(wstr1, wstr4)>0 && klab::Compare(wstr4, wstr1)<0) 
        TEST_ASSERT(klab::Compare(wstr1, L"String unit test !")==0 && klab::Compare(L"String unit test !", wstr1)==0)

        TEST_ASSERT(klab::Compare(wstr1, wstr2, false)==0 && klab::Compare(wstr2, wstr1, false)==0)
        TEST_ASSERT(klab::Compare(L"", wstr1, false)<0 && klab::Compare(wstr1, L"", false)>0)
        TEST_ASSERT(klab::Compare(wstr1, wstr3, false)==0 && klab::Compare(wstr3, wstr1, false)==0)
        TEST_ASSERT(klab::Compare(wstr1, wstr4, false)>0 && klab::Compare(wstr4, wstr1, false)<0) 
        TEST_ASSERT(klab::Compare(wstr1, L"String unit test !", false)==0 && klab::Compare(L"String unit test !", wstr1, false)==0)
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KStringUtilUnitTest::testEquals()
{
    try
    {
        std::string str1("String unit test !");
        std::string str2(str1);
        std::string str3("string unit test !");
        std::string str4("String unit test");

        TEST_ASSERT(klab::Equals(str1, str2) && klab::Equals(str2, str1))
        TEST_ASSERT(klab::Equals("", str1)==false && klab::Equals(str1, "")==false)
        TEST_ASSERT(klab::Equals(str1, str3)==false && klab::Equals(str3, str1)==false)
        TEST_ASSERT(klab::Equals(str1, str4)==false && klab::Equals(str4, str1)==false) 
        TEST_ASSERT(klab::Equals(str1, "String unit test !") && klab::Equals("String unit test !", str1))

        TEST_ASSERT(klab::Equals(str1, str2, false) && klab::Equals(str2, str1, false))
        TEST_ASSERT(klab::Equals("", str1, false)==false && klab::Equals(str1, "", false)==false)
        TEST_ASSERT(klab::Equals(str1, str3, false) && klab::Equals(str3, str1, false))
        TEST_ASSERT(klab::Equals(str1, str4, false)==false && klab::Equals(str4, str1, false)==false) 
        TEST_ASSERT(klab::Equals(str1, "String unit test !", false) && klab::Equals("String unit test !", str1, false))


        std::wstring wstr1(L"String unit test !");
        std::wstring wstr2(wstr1);
        std::wstring wstr3(L"string unit test !");
        std::wstring wstr4(L"String unit test");

        TEST_ASSERT(klab::Equals(wstr1, wstr2) && klab::Equals(wstr2, wstr1))
        TEST_ASSERT(klab::Equals(L"", wstr1)==false && klab::Equals(wstr1, L"")==false)
        TEST_ASSERT(klab::Equals(wstr1, wstr3)==false && klab::Equals(wstr3, wstr1)==false)
        TEST_ASSERT(klab::Equals(wstr1, wstr4)==false && klab::Equals(wstr4, wstr1)==false) 
        TEST_ASSERT(klab::Equals(wstr1, L"String unit test !") && klab::Equals(L"String unit test !", wstr1))

        TEST_ASSERT(klab::Equals(wstr1, wstr2, false) && klab::Equals(wstr2, wstr1, false))
        TEST_ASSERT(klab::Equals(L"", wstr1, false)==false && klab::Equals(wstr1, L"", false)==false)
        TEST_ASSERT(klab::Equals(wstr1, wstr3, false) && klab::Equals(wstr3, wstr1, false))
        TEST_ASSERT(klab::Equals(wstr1, wstr4, false)==false && klab::Equals(wstr4, wstr1, false)==false) 
        TEST_ASSERT(klab::Equals(wstr1, L"String unit test !", false) && klab::Equals(L"String unit test !", wstr1, false))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KStringUtilUnitTest::testTrimLeftString()
{
    try
    {
        std::string str1("   String unit test !   ");
        klab::TrimLeftString(str1);
		TEST_ASSERT(str1 == "String unit test !   ")
        klab::TrimLeftString(str1);
		TEST_ASSERT(str1 == "String unit test !   ")


        std::wstring wstr1(L"   String unit test !   ");
        klab::TrimLeftString(wstr1);
		TEST_ASSERT(wstr1 == L"String unit test !   ")
        klab::TrimLeftString(wstr1);
		TEST_ASSERT(wstr1 == L"String unit test !   ")


        // Limit cases.
        std::string str0("");
        klab::TrimLeftString(str0);
        TEST_ASSERT(str0 == "")


        std::wstring wstr0(L"");
        klab::TrimLeftString(wstr0);
        TEST_ASSERT(wstr0 == L"")
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KStringUtilUnitTest::testTrimRightString()
{
    try
    {
        std::string str1("   String unit test !   ");
        klab::TrimRightString(str1);
		TEST_ASSERT(str1 == "   String unit test !")
        klab::TrimRightString(str1);
		TEST_ASSERT(str1 == "   String unit test !")


        std::wstring wstr1(L"   String unit test !   ");
        klab::TrimRightString(wstr1);
		TEST_ASSERT(wstr1 == L"   String unit test !")
        klab::TrimRightString(wstr1);
		TEST_ASSERT(wstr1 == L"   String unit test !")


        // Limit cases.
        std::string str0("");
        klab::TrimRightString(str0);
        TEST_ASSERT(str0 == "")


        std::wstring wstr0(L"");
        klab::TrimRightString(wstr0);
        TEST_ASSERT(wstr0 == L"")
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KStringUtilUnitTest::testTrimString()
{
    try
    {
        std::string str1("   String unit test !   ");
        klab::TrimString(str1);
		TEST_ASSERT(str1 == "String unit test !")
        klab::TrimString(str1);
		TEST_ASSERT(str1 == "String unit test !")


        std::wstring wstr1(L"   String unit test !   ");
        klab::TrimString(wstr1);
		TEST_ASSERT(wstr1 == L"String unit test !")
        klab::TrimString(wstr1);
		TEST_ASSERT(wstr1 == L"String unit test !")


        // Limit cases.
        std::string str0("");
        klab::TrimString(str0);
        TEST_ASSERT(str0 == "")


        std::wstring wstr0(L"");
        klab::TrimString(wstr0);
        TEST_ASSERT(wstr0 == L"")
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KStringUtilUnitTest::testToLeftTrimmedString()
{
    try
    {
        std::string str1("   String unit test !   ");
		TEST_ASSERT(klab::ToLeftTrimmedString(str1) == "String unit test !   ")

        std::wstring wstr1(L"   String unit test !   ");
		TEST_ASSERT(klab::ToLeftTrimmedString(wstr1) == L"String unit test !   ")


        // Limit cases.
        std::string str0("");
        klab::TrimLeftString(str0);
        TEST_ASSERT(klab::ToLeftTrimmedString(str0) == "")

        std::wstring wstr0(L"");
        TEST_ASSERT(klab::ToLeftTrimmedString(wstr0) == L"")
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KStringUtilUnitTest::testToRightTrimmedString()
{
    try
    {
        std::string str1("   String unit test !   ");
		TEST_ASSERT(klab::ToRightTrimmedString(str1) == "   String unit test !")

        std::wstring wstr1(L"   String unit test !   ");
		TEST_ASSERT(klab::ToRightTrimmedString(wstr1) == L"   String unit test !")


        // Limit cases.
        std::string str0("");
        klab::TrimLeftString(str0);
        TEST_ASSERT(klab::ToRightTrimmedString(str0) == "")

        std::wstring wstr0(L"");
        TEST_ASSERT(klab::ToRightTrimmedString(wstr0) == L"")
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KStringUtilUnitTest::testToTrimmedString()
{
    try
    {
        std::string str1("   String unit test !   ");
		TEST_ASSERT(klab::ToTrimmedString(str1) == "String unit test !")

        std::wstring wstr1(L"   String unit test !   ");
		TEST_ASSERT(klab::ToTrimmedString(wstr1) == L"String unit test !")


        // Limit cases.
        std::string str0("");
        klab::TrimLeftString(str0);
        TEST_ASSERT(klab::ToTrimmedString(str0) == "")

        std::wstring wstr0(L"");
        TEST_ASSERT(klab::ToTrimmedString(wstr0) == L"")
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KStringUtilUnitTest::testToString()
{
    try
    {
        std::wstring str1(L"This is a std::wstring to std::string test.");
        TEST_ASSERT(klab::Equals(klab::ToString(str1), "This is a std::wstring to std::string test."))


        // Limit cases.
        TEST_ASSERT(klab::Equals(klab::ToString(L""), ""))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KStringUtilUnitTest::testToWString()
{
    try
    {
        std::string str1("This is a std::string to std::wstring test.");
        TEST_ASSERT(klab::Equals(klab::ToWString(str1), L"This is a std::string to std::wstring test."))


        // Limit cases.
        TEST_ASSERT(klab::Equals(klab::ToWString(""), L""))
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //

void KStringUtilUnitTest::testConvertStringTo()
{
    try
    {
        TEST_ASSERT(ConvertStringTo<bool>("1") == true)
        TEST_ASSERT(ConvertStringTo<bool>("0") == false)
        TEST_ASSERT(ConvertStringTo<bool>("true") == true)
        TEST_ASSERT(ConvertStringTo<bool>("false") == false)
        TEST_ASSERT(ConvertStringTo<bool>("TRUE") == true)
        TEST_ASSERT(ConvertStringTo<bool>("FALSE") == false)
        TEST_ASSERT(ConvertStringTo<bool>("True") == true)
        TEST_ASSERT(ConvertStringTo<bool>("False") == false)

        TEST_ASSERT(klab::ConvertStringTo<klab::Int8>("0") == 0)
        TEST_ASSERT(klab::ConvertStringTo<klab::Int8>("-1") == -1)
        TEST_ASSERT(klab::ConvertStringTo<klab::Int8>("12") == 12)    
        TEST_ASSERT(klab::ConvertStringTo<klab::Int8>("-12") == -12)

        TEST_ASSERT(klab::ConvertStringTo<klab::UInt8>("0") == 0)
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt8>("255") == 255)
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt8>("12") == 12)    
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt8>("244") == 244) 

        TEST_ASSERT(klab::ConvertStringTo<klab::Int16>("0") == 0)
        TEST_ASSERT(klab::ConvertStringTo<klab::Int16>("-1") == -1)
        TEST_ASSERT(klab::ConvertStringTo<klab::Int16>("12") == 12)    
        TEST_ASSERT(klab::ConvertStringTo<klab::Int16>("-12") == -12)

        TEST_ASSERT(klab::ConvertStringTo<klab::UInt16>("0") == 0)
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt16>("65535") == 65535)
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt16>("12") == 12)    
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt16>("65524") == 65524)

        TEST_ASSERT(klab::ConvertStringTo<klab::Int32>("0") == 0)
        TEST_ASSERT(klab::ConvertStringTo<klab::Int32>("-1") == -1)
        TEST_ASSERT(klab::ConvertStringTo<klab::Int32>("12") == 12)    
        TEST_ASSERT(klab::ConvertStringTo<klab::Int32>("-12") == -12)

        TEST_ASSERT(klab::ConvertStringTo<klab::UInt32>("0") == 0)
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt32>("4294967295") == klab::TTypeInfo<klab::UInt32>::MAX)
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt32>("12") == 12)    
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt32>("4294967284") == klab::TTypeInfo<klab::UInt32>::MAX-11)

        TEST_ASSERT(klab::ConvertStringTo<klab::Int64>("0") == 0)
        TEST_ASSERT(klab::ConvertStringTo<klab::Int64>("-1") == -1)
        TEST_ASSERT(klab::ConvertStringTo<klab::Int64>("12") == 12)    
        TEST_ASSERT(klab::ConvertStringTo<klab::Int64>("-12") == -12)

        TEST_ASSERT(klab::ConvertStringTo<klab::UInt64>("0") == 0)
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt64>("18446744073709551615") == klab::TTypeInfo<klab::UInt64>::MAX)
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt64>("12") == 12)    
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt64>("18446744073709551604") == klab::TTypeInfo<klab::UInt64>::MAX-11)

        TEST_ASSERT(klab::ConvertStringTo<klab::Real>("0") == 0.0f)
        TEST_ASSERT(klab::ConvertStringTo<klab::Real>("0.0") == 0.0f)
        TEST_ASSERT(klab::ConvertStringTo<klab::Real>("0.000") == 0.0f)
        TEST_ASSERT(klab::ConvertStringTo<klab::Real>("-1") == -1.0f)
        TEST_ASSERT(klab::ConvertStringTo<klab::Real>("-123.456789") == -123.456789f)

        TEST_ASSERT(klab::ConvertStringTo<klab::DoubleReal>("0") == 0.0)
        TEST_ASSERT(klab::ConvertStringTo<klab::DoubleReal>("0.0") == 0.0)
        TEST_ASSERT(klab::ConvertStringTo<klab::DoubleReal>("0.000") == 0.0)
        TEST_ASSERT(klab::ConvertStringTo<klab::DoubleReal>("-1") == -1.0)
        TEST_ASSERT(klab::ConvertStringTo<klab::DoubleReal>("-123.456789") == -123.456789)

        TEST_ASSERT(klab::ConvertStringTo<std::string>("AbcDEfg") == "AbcDEfg")
        TEST_ASSERT(klab::ConvertStringTo<std::wstring>("AbcDEfg") == L"AbcDEfg")


        TEST_ASSERT(ConvertStringTo<bool>(L"1") == true)
        TEST_ASSERT(ConvertStringTo<bool>(L"0") == false)
        TEST_ASSERT(ConvertStringTo<bool>(L"true") == true)
        TEST_ASSERT(ConvertStringTo<bool>(L"false") == false)
        TEST_ASSERT(ConvertStringTo<bool>(L"TRUE") == true)
        TEST_ASSERT(ConvertStringTo<bool>(L"FALSE") == false)
        TEST_ASSERT(ConvertStringTo<bool>(L"True") == true)
        TEST_ASSERT(ConvertStringTo<bool>(L"False") == false)

        TEST_ASSERT(klab::ConvertStringTo<klab::Int8>(L"0") == 0)
        TEST_ASSERT(klab::ConvertStringTo<klab::Int8>(L"-1") == -1)
        TEST_ASSERT(klab::ConvertStringTo<klab::Int8>(L"12") == 12)    
        TEST_ASSERT(klab::ConvertStringTo<klab::Int8>(L"-12") == -12)

        TEST_ASSERT(klab::ConvertStringTo<klab::UInt8>(L"0") == 0)
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt8>(L"255") == 255)
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt8>(L"12") == 12)    
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt8>(L"244") == 244) 

        TEST_ASSERT(klab::ConvertStringTo<klab::Int16>(L"0") == 0)
        TEST_ASSERT(klab::ConvertStringTo<klab::Int16>(L"-1") == -1)
        TEST_ASSERT(klab::ConvertStringTo<klab::Int16>(L"12") == 12)    
        TEST_ASSERT(klab::ConvertStringTo<klab::Int16>(L"-12") == -12)

        TEST_ASSERT(klab::ConvertStringTo<klab::UInt16>(L"0") == 0)
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt16>(L"65535") == 65535)
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt16>(L"12") == 12)    
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt16>(L"65524") == 65524)

        TEST_ASSERT(klab::ConvertStringTo<klab::Int32>(L"0") == 0)
        TEST_ASSERT(klab::ConvertStringTo<klab::Int32>(L"-1") == -1)
        TEST_ASSERT(klab::ConvertStringTo<klab::Int32>(L"12") == 12)    
        TEST_ASSERT(klab::ConvertStringTo<klab::Int32>(L"-12") == -12)

        TEST_ASSERT(klab::ConvertStringTo<klab::UInt32>(L"0") == 0)
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt32>(L"4294967295") == klab::TTypeInfo<klab::UInt32>::MAX)
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt32>(L"12") == 12)    
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt32>(L"4294967284") == klab::TTypeInfo<klab::UInt32>::MAX-11)

        TEST_ASSERT(klab::ConvertStringTo<klab::Int64>(L"0") == 0)
        TEST_ASSERT(klab::ConvertStringTo<klab::Int64>(L"-1") == -1)
        TEST_ASSERT(klab::ConvertStringTo<klab::Int64>(L"12") == 12)    
        TEST_ASSERT(klab::ConvertStringTo<klab::Int64>(L"-12") == -12)

        TEST_ASSERT(klab::ConvertStringTo<klab::UInt64>(L"0") == 0)
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt64>(L"18446744073709551615") == klab::TTypeInfo<klab::UInt64>::MAX)
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt64>(L"12") == 12)    
        TEST_ASSERT(klab::ConvertStringTo<klab::UInt64>(L"18446744073709551604") == klab::TTypeInfo<klab::UInt64>::MAX-11)

        TEST_ASSERT(klab::ConvertStringTo<klab::Real>(L"0") == 0.0f)
        TEST_ASSERT(klab::ConvertStringTo<klab::Real>(L"0.0") == 0.0f)
        TEST_ASSERT(klab::ConvertStringTo<klab::Real>(L"0.000") == 0.0f)
        TEST_ASSERT(klab::ConvertStringTo<klab::Real>(L"-1") == -1.0f)
        TEST_ASSERT(klab::ConvertStringTo<klab::Real>(L"-123.456789") == -123.456789f)

        TEST_ASSERT(klab::ConvertStringTo<klab::DoubleReal>(L"0") == 0.0)
        TEST_ASSERT(klab::ConvertStringTo<klab::DoubleReal>(L"0.0") == 0.0)
        TEST_ASSERT(klab::ConvertStringTo<klab::DoubleReal>(L"0.000") == 0.0)
        TEST_ASSERT(klab::ConvertStringTo<klab::DoubleReal>(L"-1") == -1.0)
        TEST_ASSERT(klab::ConvertStringTo<klab::DoubleReal>(L"-123.456789") == -123.456789)

        TEST_ASSERT(klab::ConvertStringTo<std::string>(L"AbcDEfg") == "AbcDEfg")
        TEST_ASSERT(klab::ConvertStringTo<std::wstring>(L"AbcDEfg") == L"AbcDEfg")


        // Limit cases.
        try {bool value = klab::ConvertStringTo<bool>("abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::Int8 value = klab::ConvertStringTo<klab::Int8>("abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::UInt8 value = klab::ConvertStringTo<klab::UInt8>("abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::Int16 value = klab::ConvertStringTo<klab::Int16>("abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::UInt16 value = klab::ConvertStringTo<klab::UInt16>("abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::Int32 value = klab::ConvertStringTo<klab::Int32>("abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::UInt32 value = klab::ConvertStringTo<klab::UInt32>("abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::Int64 value = klab::ConvertStringTo<klab::Int64>("abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::UInt64 value = klab::ConvertStringTo<klab::UInt64>("abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::Real value = klab::ConvertStringTo<klab::Real>("abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::Real value = klab::ConvertStringTo<klab::Real>("abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::DoubleReal value = klab::ConvertStringTo<klab::DoubleReal>("abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::DoubleReal value = klab::ConvertStringTo<klab::DoubleReal>("abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}


        try {bool value = klab::ConvertStringTo<bool>(L"abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::Int8 value = klab::ConvertStringTo<klab::Int8>(L"abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::UInt8 value = klab::ConvertStringTo<klab::UInt8>(L"abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::Int16 value = klab::ConvertStringTo<klab::Int16>(L"abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::UInt16 value = klab::ConvertStringTo<klab::UInt16>(L"abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::Int32 value = klab::ConvertStringTo<klab::Int32>(L"abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::UInt32 value = klab::ConvertStringTo<klab::UInt32>(L"abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::Int64 value = klab::ConvertStringTo<klab::Int64>(L"abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::UInt64 value = klab::ConvertStringTo<klab::UInt64>(L"abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::Real value = klab::ConvertStringTo<klab::Real>(L"abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::Real value = klab::ConvertStringTo<klab::Real>(L"abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::DoubleReal value = klab::ConvertStringTo<klab::DoubleReal>(L"abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}

        try {klab::DoubleReal value = klab::ConvertStringTo<klab::DoubleReal>(L"abcdefg"); TEST_ASSERT(false)}
        catch(KBadConversionStringException&) {TEST_ASSERT(true)}
        catch(...) {TEST_ASSERT(false)}
    }
    catch(...)
    {
        TEST_ASSERT(false)
    }
}

// ---------------------------------------------------------------------------------------------------- //
