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

#ifndef KLAB_DEFUTIL_H
#define KLAB_DEFUTIL_H

#include <stdio.h>




// ---------------------------------------------------------------------------------------------------- //

#if defined(_WIN32) || defined(__WIN32__)
    #define KLAB_MSWINDOWS_SYSTEM

    #if !defined(WIN32_LEAN_AND_MEAN)
        #define WIN32_LEAN_AND_MEAN
    #endif

    #if !defined(NOMINMAX)
        #define NOMINMAX
    #endif

    #if !defined(_WIN32_WINNT)
        #define _WIN32_WINNT 0x0500
    #endif

    #include <windows.h>
    #undef DELETE
    #undef min
    #undef max
#elif defined(linux) || defined(__linux)
    #define KLAB_UNIX_SYSTEM
	#include <unistd.h>
#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
    #define KLAB_MACOS_SYSTEM

	// The __ASSERTMACROS__ definition below is to avoid conflicts between Armadillo C++ library and Mac OS X AssertMacros.h header.
	#define __ASSERTMACROS__
    #include <Carbon/Carbon.h>
#else
	#warning This operating system is not known. Considered as a unix system by default...
	#define KLAB_UNIX_SYSTEM
	#include <unistd.h>
#endif

// ---------------------------------------------------------------------------------------------------- //

#if defined(__i386__) || defined(_M_IX86) || defined(_X86_) || defined(__INTEL__) || defined(__i386)
    #define KLAB_X86_PLATFORM
    #define KLAB_32BITS_PLATFORM
#elif defined(__amd64__) || defined(__x86_64) || defined(__x86_64__) || defined(_M_AMD64)
    #define KLAB_AMD64_PLATFORM
    #define KLAB_64BITS_PLATFORM
#elif defined(__IA64__) || defined(_M_IA64)
    #define KLAB_IA64_PLATFORM
    #define KLAB_64BITS_PLATFORM
#elif defined(__powerpc__) || defined(_M_PPC) || defined(_ARCH_PPC)
    #define KLAB_POWERPC_PLATFORM
    #define KLAB_32BITS_PLATFORM
#else
    // #error This platform is not supported.
    #define KLAB_32BITS_PLATFORM
#endif

// ---------------------------------------------------------------------------------------------------- //

#if defined(KLAB_POWERPC_PLATFORM)
    #define KLAB_BIG_ENDIAN
#else
    #define KLAB_LITTLE_ENDIAN
#endif

// ---------------------------------------------------------------------------------------------------- //

#if !defined(NDEBUG)
    #define KLAB_DEBUG
#endif

// ---------------------------------------------------------------------------------------------------- //

#if defined(KLAB_MSWINDOWS_SYSTEM)
    #define __KLAB_FUNCTION_EXPORT__ extern "C" __declspec(dllexport)
    #define __KLAB_FUNCTION_IMPORT__ extern "C" __declspec(dllimport)
	#define __KLAB_CLASS_EXPORT__ __declspec(dllexport)
    #define __KLAB_CLASS_IMPORT__ __declspec(dllimport)
	#define __KLAB_TEMPLATE_EXPORT__
    #define __KLAB_TEMPLATE_IMPORT__ extern
#else
    #define __KLAB_FUNCTION_EXPORT__
    #define __KLAB_FUNCTION_IMPORT__
	#define __KLAB_CLASS_EXPORT__
    #define __KLAB_CLASS_IMPORT__
	#define __KLAB_TEMPLATE_EXPORT__
    #define __KLAB_TEMPLATE_IMPORT__
#endif

#if defined(KLAB_EXPORT)
	#define KLAB_FUNCTION_EXPORT __KLAB_FUNCTION_EXPORT__
	#define KLAB_CLASS_EXPORT __KLAB_CLASS_EXPORT__
	#define KLAB_TEMPLATE_EXPORT __KLAB_TEMPLATE_EXPORT__
#else
	#define KLAB_FUNCTION_EXPORT __KLAB_FUNCTION_IMPORT__
	#define KLAB_CLASS_EXPORT __KLAB_CLASS_IMPORT__
	#define KLAB_TEMPLATE_EXPORT __KLAB_TEMPLATE_IMPORT__
#endif

// ---------------------------------------------------------------------------------------------------- //

#if defined(_MSC_VER)
    #define KLAB__FILE__    __FILE__
    #define KLAB__LINE__    __LINE__
    #define KLAB__FUNC__    __FUNCTION__
#else
    #define KLAB__FILE__    __FILE__
    #define KLAB__LINE__    __LINE__
    #define KLAB__FUNC__    __func__
#endif

// ---------------------------------------------------------------------------------------------------- //

// Compiler directives.
#if defined(_MSC_VER)
    #pragma warning(disable:4290)   // Throw function exception specifications.
    #pragma warning(disable:4996)   // Function call with parameters that may be unsafe.
#else
#endif

// ---------------------------------------------------------------------------------------------------- //

// Macro expand for debugging purpose.
#define KLAB_QUOTE(str) #str
#define KLAB_EXPAND_AND_QUOTE(str) KLAB_QUOTE(str)

// ---------------------------------------------------------------------------------------------------- //

#define KLAB_DECLARETYPE(TypeName) \
class TypeName \
{ \
public: \
    virtual ~TypeName() {}; \
\
private: \
    TypeName(); \
    TypeName(const TypeName& type); \
    TypeName&   operator=(const TypeName& type); \
};

// ---------------------------------------------------------------------------------------------------- //


#endif
