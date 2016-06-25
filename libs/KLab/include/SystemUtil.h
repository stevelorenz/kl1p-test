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

#ifndef KLAB_SYSTEMUTIL_H
#define KLAB_SYSTEMUTIL_H

#include "TypeUtil.h"
#include "FuncUtil.h"




namespace klab
{

// ---------------------------------------------------------------------------------------------------- //

KLAB_DECLARETYPE(UnknownSystem)
KLAB_DECLARETYPE(MSWindowsSystem)
KLAB_DECLARETYPE(UnixSystem)
KLAB_DECLARETYPE(MacOSSystem)

// ---------------------------------------------------------------------------------------------------- //

#if defined(KLAB_MSWINDOWS_SYSTEM)
    typedef MSWindowsSystem     CurrentSystem;
#elif  defined(KLAB_UNIX_SYSTEM)
    typedef UnixSystem          CurrentSystem;
#elif  defined(KLAB_MACOS_SYSTEM)
    typedef MacOSSystem         CurrentSystem;
#else
    typedef UnknownSystem       CurrentSystem;
#endif

// ---------------------------------------------------------------------------------------------------- //

typedef klab::UInt32            KOperatingSystemCode;

// ---------------------------------------------------------------------------------------------------- //

// Operating Systems code mask.
#define KLAB_OPERATINGSYSTEMTYPE_MASK           0xFF000000
#define KLAB_OPERATINGSYSTEM_MASK               0xFFFF0000
#define KLAB_WORDSIZEOPERATINGSYSTEM_MASK       0x0000F000
#define KLAB_RESERVEDOPERATINGSYSTEM_MASK       0x00000F00
#define KLAB_SUBVERSIONOPERATINGSYSTEM_MASK     0x000000FF

// ---------------------------------------------------------------------------------------------------- //

// Operating Systems Types.
#define KLAB_UNKNOWN_OSTYPE                     0x00000000
#define KLAB_MSWINDOWS_OSTYPE                   0x01000000
#define KLAB_UNIX_OSTYPE                        0x02000000
#define KLAB_MACOS_OSTYPE                       0x03000000

// ---------------------------------------------------------------------------------------------------- //

// Operating Systems versions.
#define KLAB_UNKNOWN_OPERATINGSYSTEM            0x00000000

#define KLAB_WINDOWS_OPERATINGSYSTEM            0x01000000
#define KLAB_WINDOWS31_OPERATINGSYSTEM          0x01010000
#define KLAB_WINDOWS95_OPERATINGSYSTEM          0x01020000
#define KLAB_WINDOWS98_OPERATINGSYSTEM          0x01030000
#define KLAB_WINDOWSME_OPERATINGSYSTEM          0x01040000
#define KLAB_WINDOWSNT_OPERATINGSYSTEM          0x01050000
#define KLAB_WINDOWSNT4_OPERATINGSYSTEM         0x01060000
#define KLAB_WINDOWS2000_OPERATINGSYSTEM        0x01080000
#define KLAB_WINDOWSXP_OPERATINGSYSTEM          0x01090000
#define KLAB_WINDOWS2003_OPERATINGSYSTEM        0x010A0000
#define KLAB_WINDOWSVISTA_OPERATINGSYSTEM       0x010B0000
#define KLAB_WINDOWS2008_OPERATINGSYSTEM        0x010C0000
#define KLAB_WINDOWS2008R2_OPERATINGSYSTEM      0x010D0000
#define KLAB_WINDOWSSEVEN_OPERATINGSYSTEM       0x010E0000
#define KLAB_HIGHERWINDOWS_OPERATINGSYSTEM      0x01FF0000

#define KLAB_UNIX_OPERATINGSYSTEM               0x02000000
#define KLAB_SOLARIS_OPERATINGSYSTEM            0x02010000
#define KLAB_LINUX_OPERATINGSYSTEM              0x02810000
#define KLAB_DEBIAN_OPERATINGSYSTEM             0x02820000
#define KLAB_UBUNTU_OPERATINGSYSTEM             0x02830000
#define KLAB_MANDRAKE_OPERATINGSYSTEM           0x02840000
#define KLAB_MANDRIVA_OPERATINGSYSTEM           0x02850000
#define KLAB_REDHAT_OPERATINGSYSTEM             0x02860000
#define KLAB_SUSE_OPERATINGSYSTEM               0x02870000

#define KLAB_MACOS_OPERATINGSYSTEM              0x03000000
#define KLAB_MACOSX_OPERATINGSYSTEM             0x03010000
#define KLAB_MACOSXCHEETAH_OPERATINGSYSTEM      0x03020000
#define KLAB_MACOSXPUMA_OPERATINGSYSTEM         0x03030000
#define KLAB_MACOSXJAGUAR_OPERATINGSYSTEM       0x03040000
#define KLAB_MACOSXPANTHER_OPERATINGSYSTEM      0x03050000
#define KLAB_MACOSXTIGER_OPERATINGSYSTEM        0x03060000
#define KLAB_MACOSXLEOPARD_OPERATINGSYSTEM      0x03070000
#define KLAB_MACOSXSNOWLEOPARD_OPERATINGSYSTEM  0x03080000
#define KLAB_MACOSXLION_OPERATINGSYSTEM  		0x03090000
#define KLAB_MACOSXMOUNTAINLION_OPERATINGSYSTEM 0x030A0000
#define KLAB_HIGHERMACOS_OPERATINGSYSTEM        0x03FF0000

// ---------------------------------------------------------------------------------------------------- //

#define KLAB_UNKNOWNWORDSIZE_OPERATINGSYSTEM    0x0
#define KLAB_16BITS_OPERATINGSYSTEM             0x1
#define KLAB_32BITS_OPERATINGSYSTEM             0x2
#define KLAB_64BITS_OPERATINGSYSTEM             0x3

// ---------------------------------------------------------------------------------------------------- //

}


#endif
