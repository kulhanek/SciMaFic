#ifndef SciMaFicMainHeaderH
#define SciMaFicMainHeaderH
/*! \file SciMaFicMainHeader.hpp */
//==============================================================================
//    Copyright 1998-2008 Petr Kulhanek
//
//    This file is part of SciMaFic library.
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Lesser General Public
//    License as published by the Free Software Foundation; either
//    version 2.1 of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Lesser General Public License for more details.
//
//    You should have received a copy of the GNU Lesser General Public
//    License along with this library; if not, write to the Free Software
//    Foundation, Inc., 51 Franklin Street, Fifth Floor,
//    Boston, MA  02110-1301  USA
//==============================================================================

#include <HiPoLyMainHeader.hpp>

//------------------------------------------------------------------------------

#define SCIMAFIC_VERSION "SciMaFic 1.0.SVNVERSION (DATE)"

extern const char* LibBuildVersion_SciMaFic;

//------------------------------------------------------------------------------

#if defined _WIN32 || defined __CYGWIN__
#ifdef SCIMAFIC_BUILDING_DLL
#ifdef __GNUC__
#define SCIMAFIC_DLL_PUBLIC __attribute__((dllexport))
#else
#define SCIMAFIC_DLL_PUBLIC __declspec(dllexport)
#endif
#else
#ifdef __GNUC__
#define SCIMAFIC_DLL_PUBLIC __attribute__((dllimport))
#else
#define SCIMAFIC_DLL_PUBLIC __declspec(dllimport)
#endif
#define SCIMAFIC_DLL_LOCAL
#endif
#else
#if __GNUC__ >= 4
#define SCIMAFIC_DLL_PUBLIC __attribute__ ((visibility("default")))
#define SCIMAFIC_DLL_LOCAL  __attribute__ ((visibility("hidden")))
#else
#define SCIMAFIC_DLL_PUBLIC
#define SCIMAFIC_DLL_LOCAL
#endif
#endif

#define SCIMAFIC_PACKAGE SCIMAFIC_DLL_PUBLIC

//--------------------------------------------------------------------------------

#endif
