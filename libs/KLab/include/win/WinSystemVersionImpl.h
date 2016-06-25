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

#ifndef KLAB_WINSYSTEMVERSIONIMPL_H
#define KLAB_WINSYSTEMVERSIONIMPL_H

#include "../SystemUtil.h"




namespace klab
{
  
// ---------------------------------------------------------------------------------------------------- //

template<>
class TSystemVersionImpl<MSWindowsSystem>
{
public:

    TSystemVersionImpl();
    TSystemVersionImpl(const TSystemVersionImpl<MSWindowsSystem>& system);
    virtual ~TSystemVersionImpl();

    TSystemVersionImpl<MSWindowsSystem>&    operator=(const TSystemVersionImpl<MSWindowsSystem>& system);

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

inline TSystemVersionImpl<MSWindowsSystem>::TSystemVersionImpl() : 
_code(0)
{}

// ---------------------------------------------------------------------------------------------------- //

inline TSystemVersionImpl<MSWindowsSystem>::TSystemVersionImpl(const TSystemVersionImpl<MSWindowsSystem>& system) : 
_code(system._code)
{}

// ---------------------------------------------------------------------------------------------------- //

inline TSystemVersionImpl<MSWindowsSystem>::~TSystemVersionImpl()
{}

// ---------------------------------------------------------------------------------------------------- //

inline TSystemVersionImpl<MSWindowsSystem>& TSystemVersionImpl<MSWindowsSystem>::operator=(const TSystemVersionImpl<MSWindowsSystem>& system)
{
    if(this != &system)
    {
        _code = system._code;
    }

    return *this;
}

// ---------------------------------------------------------------------------------------------------- //

inline KOperatingSystemCode TSystemVersionImpl<MSWindowsSystem>::code()
{
    if(_code == 0)
        _code = this->readCode();

    return _code;
}

// ---------------------------------------------------------------------------------------------------- //

inline bool TSystemVersionImpl<MSWindowsSystem>::isMSWindows()
{
    return ((this->code() & KLAB_OPERATINGSYSTEMTYPE_MASK) == KLAB_MSWINDOWS_OSTYPE);
}

// ---------------------------------------------------------------------------------------------------- //

inline bool TSystemVersionImpl<MSWindowsSystem>::isUnix()
{
    return false;
}

// ---------------------------------------------------------------------------------------------------- //

inline bool TSystemVersionImpl<MSWindowsSystem>::isMacOS()
{
    return false;
}

// ---------------------------------------------------------------------------------------------------- //

inline klab::UInt8 TSystemVersionImpl<MSWindowsSystem>::wordSize()
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

inline std::string TSystemVersionImpl<MSWindowsSystem>::name()
{
    std::string ret = "";

    switch(this->code() & KLAB_OPERATINGSYSTEM_MASK)
    {
    case KLAB_WINDOWS_OPERATINGSYSTEM:          ret = "Windows";                break;
    case KLAB_WINDOWS31_OPERATINGSYSTEM:        ret = "Windows 3.1";            break;
    case KLAB_WINDOWS95_OPERATINGSYSTEM:        ret = "Windows 95";             break;
    case KLAB_WINDOWS98_OPERATINGSYSTEM:        ret = "Windows 98";             break;
    case KLAB_WINDOWSME_OPERATINGSYSTEM:        ret = "Windows ME";             break;
    case KLAB_WINDOWSNT_OPERATINGSYSTEM:        ret = "Windows NT";             break;
    case KLAB_WINDOWSNT4_OPERATINGSYSTEM:       ret = "Windows NT4";            break;
    case KLAB_WINDOWS2000_OPERATINGSYSTEM:      ret = "Windows 2000";           break;
    case KLAB_WINDOWSXP_OPERATINGSYSTEM:        ret = "Windows XP";             break;
    case KLAB_WINDOWS2003_OPERATINGSYSTEM:      ret = "Windows 2003";           break;
    case KLAB_WINDOWSVISTA_OPERATINGSYSTEM:     ret = "Windows Vista";          break;
    case KLAB_WINDOWS2008_OPERATINGSYSTEM:      ret = "Windows 2008";           break;
    case KLAB_WINDOWS2008R2_OPERATINGSYSTEM:    ret = "Windows 2008 R2";        break;
    case KLAB_WINDOWSSEVEN_OPERATINGSYSTEM:     ret = "Windows 7";              break;
    case KLAB_HIGHERWINDOWS_OPERATINGSYSTEM:    ret = "Windows (Other)";        break;
    default:                                    ret = "Unknown Windows System"; break;
    };

    klab::UInt8 wordSize = this->wordSize();
    if(wordSize == 64)      ret += " 64-bits";
    else if(wordSize == 16) ret += " 16-bits";

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

inline std::string TSystemVersionImpl<MSWindowsSystem>::fullName()
{
    return this->name();
}

// ---------------------------------------------------------------------------------------------------- //

inline KOperatingSystemCode TSystemVersionImpl<MSWindowsSystem>::readCode()
{
    KOperatingSystemCode ret = KLAB_WINDOWS_OPERATINGSYSTEM;

    OSVERSIONINFOEX version;
	version.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

    if(::GetVersionEx((OSVERSIONINFO*)&version) == TRUE)
    {
        version.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
        if(::GetVersionEx((OSVERSIONINFO*)&version) == TRUE)
        {
            if(version.dwMajorVersion == 3)
            {
                ret = KLAB_WINDOWSNT_OPERATINGSYSTEM;
            }
            if(version.dwMajorVersion == 4)
            {
                if(version.dwMinorVersion>=0 && version.dwMinorVersion<10)         
                {
                    if(version.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)  ret = KLAB_WINDOWS95_OPERATINGSYSTEM;
                    else                                                    ret = KLAB_WINDOWSNT4_OPERATINGSYSTEM;
                }
                else if(version.dwMinorVersion>=10 && version.dwMinorVersion<90)   
                {
                    ret = KLAB_WINDOWS98_OPERATINGSYSTEM;
                }
                else if(version.dwMinorVersion>=90)   
                {
                    ret = KLAB_WINDOWSME_OPERATINGSYSTEM;
			    }
            }
            else if(version.dwMajorVersion == 5)
            {
                if(version.dwMinorVersion == 0) 
                {
                    ret = KLAB_WINDOWS2000_OPERATINGSYSTEM;
                }
                else if(version.dwMinorVersion == 1)
                {
                    ret = KLAB_WINDOWSXP_OPERATINGSYSTEM;
                }
                else if(version.dwMinorVersion >= 2)
                {
                    if(version.wProductType == VER_NT_WORKSTATION)      ret = KLAB_WINDOWSXP_OPERATINGSYSTEM;
                    else                                                ret = KLAB_WINDOWS2003_OPERATINGSYSTEM;
                }
            }
            else if(version.dwMajorVersion == 6)
            {
                if(version.dwMinorVersion == 0) 
                {
                    if(version.wProductType == VER_NT_WORKSTATION)      ret = KLAB_WINDOWSVISTA_OPERATINGSYSTEM;
                    else                                                ret = KLAB_WINDOWS2008_OPERATINGSYSTEM;
                }
                else if(version.dwMinorVersion == 1)
                {
                    if(version.wProductType == VER_NT_WORKSTATION)      ret = KLAB_WINDOWSSEVEN_OPERATINGSYSTEM;
                    else                                                ret = KLAB_WINDOWS2008R2_OPERATINGSYSTEM;
                }
                else if(version.dwMinorVersion > 1)
                {
                    ret = KLAB_HIGHERWINDOWS_OPERATINGSYSTEM;
                }
            }
            else if(version.dwMajorVersion > 6)
            {
                ret = KLAB_HIGHERWINDOWS_OPERATINGSYSTEM;
            }

            bool is64Bits = false;
            if(ret >= KLAB_WINDOWSXP_OPERATINGSYSTEM)
            {
                HKEY    key          = NULL;
                DWORD   bufferLength = 1024;  
                char    buffer[1024];	                          
                HRESULT result = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Installer"), 0, KEY_READ|KEY_WOW64_64KEY, &key);
                if(result == ERROR_SUCCESS)
                {
                    result = ::RegQueryValueEx(key, TEXT("MsiExecCA64"), NULL, NULL, (LPBYTE)buffer, &bufferLength);
                    is64Bits = (result == ERROR_SUCCESS);

                    ::RegCloseKey(key);
                }
            }

            if(ret == KLAB_WINDOWS31_OPERATINGSYSTEM)   ret |= 0x00001000;
            else if(is64Bits)                           ret |= 0x00003000;
            else                                        ret |= 0x00002000;
        }
    }

    return ret;
}

// ---------------------------------------------------------------------------------------------------- //

}


#endif
