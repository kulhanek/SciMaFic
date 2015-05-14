#ifndef ElementH
#define ElementH
/*! \file Element.hpp */
//==============================================================================
//    Copyright 2008      Jakub Stepan
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

#include <SciMaFicMainHeader.hpp>
#include <SmallString.hpp>
#include <SmallColor.hpp>

// ----------------------------------------------------------------------------

/*

 Special meaning of proton numbers:
 -1  - dummy atom
  0  - virtual atom aka valence
  1  - hydrogen (also virtual atom)

*/

// ----------------------------------------------------------------------------

/*  CLASS:   CElement
    PURPOSE: basic properties of element
*/

class SCIMAFIC_PACKAGE CElement {
public:

       CElement(void);

// access methods ------------------------------------------------------------
    const char*         GetSymbol(void) const;
    int                 GetZ(void) const;
    const CSmallString& GetName(void) const;
    float               GetVdWRadius(void) const;
    float               GetCovalentRadius(void) const;
    float               GetElectronegativity(void) const;
    float               GetMass(void) const;
    bool                IsVirtual(void) const;

// section of private data ----------------------------------------------------
private:
    const char*         Symbol;             // symbol
    CSmallString        Name;               // name
    int                 Z;                  // proton number
    float               Mass;               // mass
    float               vdWRadius;          // van der Waals radius
    float               CovalentRadius;     // covalent radius
    float               Electronegativity;  // electronegativity
    CSmallColor<float>  Color;              // color for representation

    friend class CPeriodicTable;
};


// ----------------------------------------------------------------------------

#endif

