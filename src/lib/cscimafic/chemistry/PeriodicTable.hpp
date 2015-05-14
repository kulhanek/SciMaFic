#ifndef PeriodicTableH
#define PeriodicTableH
/*! \file PeriodicTable.hpp */
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
#include <Element.hpp>

// ----------------------------------------------------------------------------

#define CPT_NUM_OF_ELEMENTS         105      //(including virtual atom)

// ----------------------------------------------------------------------------

/*  CLASS:   CPeriodicTable
    PURPOSE: basic functions for manipulation with periodic table
*/

class SCIMAFIC_PACKAGE CPeriodicTable {
public:
    CPeriodicTable(void);

    /// find element with given name
    const CElement* SearchByName(const CSmallString& name) const;

    /// find element with given symbol
    const CElement* SearchBySymbol(const CSmallString& symbol) const;

    /// return element with given proton number
    const CElement*     GetElement(unsigned z) const;

    /// return symbol of element
    const char* GetSymbol(int z) const;

    /// return name of element
    const char* GetName(int z) const;

    /// return vdW radius of element
    float       GetVdWRadius(int z) const;

    /// return covalent radius of element
    float       GetCovalentRadius(int z) const;

    /// return mass of element
    float       GetMass(int z) const;

    /// return electronegativity of element
    float       GetElectronegativity(int z) const;

    /// return representation color of element
    CSmallColor<float> GetColor(int z) const;

    /// check if element is virtual (e.g. H or Vir)
    bool    IsVirtual(int z) const;

    /// return proton number of element
    int   SearchZBySymbol(const CSmallString& symbol) const;

    /// return proton number of element
    int   SearchZByName(const CSmallString& name) const;

    /// return proton number of element
    int   SearchZByMass(float mass,float tolerance=0.5) const;

    /// return aproximate value of covalent bond between two atoms
    float GetBondDistance(int z1,int z2) const;

    /// return pointer to virtual element
    const CElement*    GetVirtual(void) const;

// section of private data ----------------------------------------------------
private:
    CElement        Elements[CPT_NUM_OF_ELEMENTS]; // elements storage

    // predefined values
    static const char*              Symbols[CPT_NUM_OF_ELEMENTS];
    static const char*              Names[CPT_NUM_OF_ELEMENTS];
    static const float              Masses[CPT_NUM_OF_ELEMENTS];
    static const float              vdWRadii[CPT_NUM_OF_ELEMENTS];
    static const float              CovalentRadii[CPT_NUM_OF_ELEMENTS];
    static const float              Electronegativity[CPT_NUM_OF_ELEMENTS];
    static const CSmallColor<float> Color[CPT_NUM_OF_ELEMENTS];
};

// ----------------------------------------------------------------------------

extern SCIMAFIC_PACKAGE CPeriodicTable PeriodicTable;

// ----------------------------------------------------------------------------

#endif

