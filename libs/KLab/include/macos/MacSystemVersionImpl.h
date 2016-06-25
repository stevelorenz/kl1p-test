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

#ifndef KLAB_MACSYSTEMVERSIONIMPL_H
#define KLAB_MACSYSTEMVERSIONIMPL_H

#include "../SystemUtil.h"
#include "../LibUtil.h"
#include "../StringUtil.h"
#include <sys/utsname.h>




namespace klab
{
  
// ---------------------------------------------------------------------------------------------------- //

template<>
class TSystemVersionImpl<MacOSSystem>
{
public:

    TSystemVersionImpl();
    TSystemVersionImpl(const TSystemVersionImpl<MacOSSystem>& system);
    virtual ~TSystemVersionImpl();

    TSystemVersionImpl<MacOSSystem>&	operator=(const TSystemVersionImpl<MacOSSystem>& system);

    KOperatingSystemCode        code();

    bool                        isMSWindows();
    bool                        isUnix();
    bool                        isMacOS();

    klab::UInt8                 wordSize();

    std::string                 name();
    std::string                 fullName();


protected:

    KOperatingSystemCode        readCode();


private:

    KOperatingSystemCode        _code;
};

// ---------------------------------------------------------------------------------------------------- //

inline TSystemVersionImpl<MacOSSystem>::TSystemVersionImpl() : 
_code(0)
{}

// ---------------------------------------------------------------------------------------------------- //

inline TSystemVersionImpl<MacOSSystem>::TSystemVersionImpl(const TSystemVersionImpl<MacOSSystem>& system) : 
_code(system._code)
{}

// ---------------------------------------------------------------------------------------------------- //

inline TSystemVersionImpl<MacOSSystem>::~TSystemVersionImpl()
{}

// ---------------------------------------------------------------------------------------------------- //

inline TSystemVersionImpl<MacOSSystem>& TSystemVersionImpl<MacOSSystem>::operator=(const TSystemVersionImpl<MacOSSystem>& system)
{
    if(this != &system)
    {
        _code = system._code;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

inline KOperatingSystemCode TSystemVersionImpl<MacOSSystem>::code()
{
    if(_code == 0)
        _code = this->readCode();

    return _code;
}

// ---------------------------------------------------------------------------------------------------- //

inline bool TSystemVersionImpl<MacOSSystem>::isMSWindows()
{
    return false;
}

// ---------------------------------------------------------------------------------------------------- //

inline bool TSystemVersionImpl<MacOSSystem>::isUnix()
{
    return false;
}

// ---------------------------------------------------------------------------------------------------- //

inline bool TSystemVersionImpl<MacOSSystem>::isMacOS()
{
    return ((this->code() & KLAB_OPERATINGSYSTEMTYPE_MASK) == KLAB_MACOS_OSTYPE);
}

// ---------------------------------------------------------------------------------------------------- //

inline klab::UInt8 TSystemVersionImpl<MacOSSystem>::wordSize()
{
    klab::UInt8 ret = 0;

    KOperatingSystemCode wordSizeCode = (this->code() & KLAB_WORDSIZEOPERATINGSYSTEM_MASK) >> 12;
    switch(wordSizeCode)
    {
    case KLAB_UNKNOWNWORDSIZE_OPERATINGSYSTEM:  ret = 0;    break;
    case KLAB_16BITS_OPERATINGSYSTEM:           ret = 16;   break;
    case KLAB_32BITS_OPERATINGSYSTEM:           ret = 32;   break;
    case KLAB_64BITS_OPERATINGSYSTEM:           ret = 64;   break;
    default:                                    ret = 0;    break;
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

inline std::string TSystemVersionImpl<MacOSSystem>::name()
{
    std::string ret = "";

    switch(this->code() & KLAB_OPERATINGSYSTEM_MASK)
    {
    case KLAB_MACOS_OPERATINGSYSTEM:				ret = "Mac OS";               	break;    
	case KLAB_MACOSX_OPERATINGSYSTEM:				ret = "Mac OS X";             	break;    
	case KLAB_MACOSXCHEETAH_OPERATINGSYSTEM:		ret = "Mac OS X Cheetah";		break;    
	case KLAB_MACOSXPUMA_OPERATINGSYSTEM:			ret = "Mac OS X Puma";			break;
	case KLAB_MACOSXJAGUAR_OPERATINGSYSTEM:			ret = "Mac OS X Jaguar";		break;
	case KLAB_MACOSXPANTHER_OPERATINGSYSTEM:		ret = "Mac OS X Panther";		break;
	case KLAB_MACOSXTIGER_OPERATINGSYSTEM:			ret = "Mac OS X Tiger";			break;
	case KLAB_MACOSXLEOPARD_OPERATINGSYSTEM:		ret = "Mac OS X Leopard";		break;
	case KLAB_MACOSXSNOWLEOPARD_OPERATINGSYSTEM:	ret = "Mac OS X Snow Leopard";	break;
	case KLAB_MACOSXLION_OPERATINGSYSTEM:			ret = "Mac OS X Lion";			break;
	case KLAB_MACOSXMOUNTAINLION_OPERATINGSYSTEM:	ret = "Mac OS X Mountain Lion";	break;
	case KLAB_HIGHERMACOS_OPERATINGSYSTEM:			ret = "Mac OS X (Other)";		break;
    default:										ret = "Unknown Mac OS System";	break;
    };

    klab::UInt8 wordSize = this->wordSize();
    if(wordSize == 64)      ret += " 64-bits";
    else if(wordSize == 16) ret += " 16-bits";

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

inline std::string TSystemVersionImpl<MacOSSystem>::fullName()
{
    return this->name();
}

// ---------------------------------------------------------------------------------------------------- //

inline KOperatingSystemCode TSystemVersionImpl<MacOSSystem>::readCode()
{
    KOperatingSystemCode ret = KLAB_MACOS_OPERATINGSYSTEM;
	
	SInt32 version = 0;
	Gestalt(gestaltSystemVersion, &version);
	
	if(version>=0x1090)			ret = KLAB_HIGHERMACOS_OPERATINGSYSTEM;
	else if(version>=0x1080)	ret = KLAB_MACOSXMOUNTAINLION_OPERATINGSYSTEM;
	else if(version>=0x1070)	ret = KLAB_MACOSXLION_OPERATINGSYSTEM;
	else if(version>=0x1060)	ret = KLAB_MACOSXSNOWLEOPARD_OPERATINGSYSTEM;
	else if(version>=0x1050)	ret = KLAB_MACOSXLEOPARD_OPERATINGSYSTEM;
	else if(version>=0x1040)	ret = KLAB_MACOSXTIGER_OPERATINGSYSTEM;
	else if(version>=0x1030)	ret = KLAB_MACOSXPANTHER_OPERATINGSYSTEM;
	else if(version>=0x1020)	ret = KLAB_MACOSXJAGUAR_OPERATINGSYSTEM;
	else if(version>=0x1010)	ret = KLAB_MACOSXPUMA_OPERATINGSYSTEM;
	else if(version>=0x1000)	ret = KLAB_MACOSXCHEETAH_OPERATINGSYSTEM;

	bool is64Bits = false;
	
	utsname versionInfo;
	if(uname(&versionInfo) >= 0)
	{
		std::string str(versionInfo.machine);
		
		if(klab::ToLowerCase(str).find("x86_64") != std::string::npos)	// Searching for 64-bits version.
			is64Bits = true;
	}
	
	if(is64Bits)	ret |= 0x00003000;
	else			ret |= 0x00002000;
	
    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
