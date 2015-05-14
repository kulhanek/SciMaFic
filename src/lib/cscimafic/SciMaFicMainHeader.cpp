/*******************************************************************************
 * Copyright (c) 1998-2007 Petr Kulhanek                                      *
 *                         kulhanek@chemi.muni.cz                             *
 *                                                                            *
 *   This file is part of SciMaFic library.                                   *
 *                                                                            *
 *   This library is free software; you can redistribute it and/or modify     *
 *   it under the terms of the GNU General Public License as published by     *
 *   the Free Software Foundation; either version 2 of the License, or        *
 *   (at your option) any later version.                                      *
 *                                                                            *
 *   This library is distributed in the hope that it will be useful,          *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 *   GNU General Public License for more details.                             *
 *                                                                            *
 *   You should have received a copy of the GNU General Public License        *
 *   along with this library; if not, write to the                            *
 *   Free Software Foundation, Inc.,                                          *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.                *
*******************************************************************************/

#include <SciMaFicMainHeader.hpp>

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

const char* LibBuildVersion_SciMaFic = SCIMAFIC_VERSION;

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

#if defined _WIN32 || defined __CYGWIN__

#include <windows.h>

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    return(TRUE);
}

//==============================================================================
#else
//==============================================================================

#include <stdio.h>
#include <unistd.h>

// under UNIX we try to make library as executable object that will
// print copyright notice and build number

// you need to compile shared library with following options

// -e __hipoly_main                         <- define entry point
// --dynamic-loader /ld/ld-linux.so.2       <- redefine dynamic loader
// -pie                                     <- make position independent executable
// --export-dynamic                         <- export symbols

// declare entry point
extern "C" void __scimafic_main(void) __attribute__ ((noreturn));

// define entry point
extern "C" void __scimafic_main(void)
{
    printf("\n");
    printf("===========================================================\n");
    printf(" *********** SciMaFic - Scientific Math Library ********** \n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf(" (c) 1998-2009                                             \n");
    printf("     Library maintainer: Petr Kulhanek                     \n");
    printf("                         kulhanek@chemi.muni.cz            \n");
    printf("     SciMaFic is licenced under GNU GPL.                   \n");
    printf("-----------------------------------------------------------\n");
    printf(" SciMaFic contains following imported code:                \n");
    printf("     - some parts of OpenBabel                             \n");
    printf("===========================================================\n");
    printf(" Build: %s\n",LibBuildVersion_SciMaFic);
    printf("===========================================================\n");
    printf("\n");
    _exit(0);
}

#endif

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
