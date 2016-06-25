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

#ifndef KLAB_UNIXSYSTEMVERSIONIMPL_H
#define KLAB_UNIXSYSTEMVERSIONIMPL_H

#include "../SystemUtil.h"
#include "../LibUtil.h"
#include "../StringUtil.h"
#include <sys/utsname.h>




namespace klab
{
  
// ---------------------------------------------------------------------------------------------------- //

template<>
class TSystemVersionImpl<UnixSystem>
{
public:

    TSystemVersionImpl();
    TSystemVersionImpl(const TSystemVersionImpl<UnixSystem>& system);
    virtual ~TSystemVersionImpl();

    TSystemVersionImpl<UnixSystem>&	operator=(const TSystemVersionImpl<UnixSystem>& system);

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

inline TSystemVersionImpl<UnixSystem>::TSystemVersionImpl() : 
_code(0)
{}

// ---------------------------------------------------------------------------------------------------- //

inline TSystemVersionImpl<UnixSystem>::TSystemVersionImpl(const TSystemVersionImpl<UnixSystem>& system) : 
_code(system._code)
{}

// ---------------------------------------------------------------------------------------------------- //

inline TSystemVersionImpl<UnixSystem>::~TSystemVersionImpl()
{}

// ---------------------------------------------------------------------------------------------------- //

inline TSystemVersionImpl<UnixSystem>& TSystemVersionImpl<UnixSystem>::operator=(const TSystemVersionImpl<UnixSystem>& system)
{
    if(this != &system)
    {
        _code = system._code;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

inline KOperatingSystemCode TSystemVersionImpl<UnixSystem>::code()
{
    if(_code == 0)
        _code = this->readCode();

    return _code;
}

// ---------------------------------------------------------------------------------------------------- //

inline bool TSystemVersionImpl<UnixSystem>::isMSWindows()
{
    return false;
}

// ---------------------------------------------------------------------------------------------------- //

inline bool TSystemVersionImpl<UnixSystem>::isUnix()
{
    return ((this->code() & KLAB_OPERATINGSYSTEMTYPE_MASK) == KLAB_UNIX_OSTYPE);
}

// ---------------------------------------------------------------------------------------------------- //

inline bool TSystemVersionImpl<UnixSystem>::isMacOS()
{
    return false;
}

// ---------------------------------------------------------------------------------------------------- //

inline klab::UInt8 TSystemVersionImpl<UnixSystem>::wordSize()
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

inline std::string TSystemVersionImpl<UnixSystem>::name()
{
    std::string ret = "";

    switch(this->code() & KLAB_OPERATINGSYSTEM_MASK)
    {
    case KLAB_UNIX_OPERATINGSYSTEM:			ret = "Unix";                break;
    case KLAB_SOLARIS_OPERATINGSYSTEM:		ret = "Unix Solaris";		 break;
    case KLAB_LINUX_OPERATINGSYSTEM:        ret = "Linux";				 break;
    case KLAB_DEBIAN_OPERATINGSYSTEM:       ret = "Linux Debian";		 break;
    case KLAB_UBUNTU_OPERATINGSYSTEM:       ret = "Linux Ubuntu";		 break;
    case KLAB_MANDRAKE_OPERATINGSYSTEM:     ret = "Linux Mandrake";		 break;
    case KLAB_MANDRIVA_OPERATINGSYSTEM:     ret = "Linux Mandriva";		 break;
    case KLAB_REDHAT_OPERATINGSYSTEM:       ret = "Linux RedHat";		 break;
    case KLAB_SUSE_OPERATINGSYSTEM:         ret = "Linux Suse";			 break;
    default:								ret = "Unknown Unix System"; break;
    };

    klab::UInt8 wordSize = this->wordSize();
    if(wordSize == 64)      ret += " 64-bits";
    else if(wordSize == 16) ret += " 16-bits";

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

inline std::string TSystemVersionImpl<UnixSystem>::fullName()
{
    return this->name();
}

// ---------------------------------------------------------------------------------------------------- //

inline KOperatingSystemCode TSystemVersionImpl<UnixSystem>::readCode()
{
    KOperatingSystemCode ret = KLAB_UNIX_OPERATINGSYSTEM;

	std::ifstream ifs("/etc/issue");
	if(ifs.is_open())
	{
		std::string line;
		ifs>>line;
		
		if(klab::ToLowerCase(line).find("debian") != std::string::npos)	// Searching for Linux Debian version.
			ret = KLAB_DEBIAN_OPERATINGSYSTEM;
			
		ifs.close();
	}
	
	 // ***** FIXME - Check for other distributions. ***** //
	 
	 
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
