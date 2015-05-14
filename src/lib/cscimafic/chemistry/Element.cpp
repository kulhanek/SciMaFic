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

#include <math.h>
#include <string.h>
#include <ctype.h>
#include <Element.hpp>

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

CElement::CElement(void)
{
    Symbol = NULL;
    Z = 0;
    Mass = 0.0;
    vdWRadius = 0.0;
    CovalentRadius = 0.0;
    Electronegativity = 0.0;
}

// ----------------------------------------------------------------------------

const char* CElement::GetSymbol(void) const
{
    return(Symbol);
}

// ----------------------------------------------------------------------------

int CElement::GetZ(void) const
{
    return(Z);
}

// ----------------------------------------------------------------------------

const CSmallString& CElement::GetName(void) const
{
    return(Name);
}

// ----------------------------------------------------------------------------

float CElement::GetVdWRadius(void) const
{
    return(vdWRadius);
}

// ----------------------------------------------------------------------------

float CElement::GetCovalentRadius(void) const
{
    return(CovalentRadius);
}

// ----------------------------------------------------------------------------

float CElement::GetElectronegativity(void) const
{
    return(Electronegativity);
}

// ----------------------------------------------------------------------------

float CElement::GetMass(void) const
{
    return(Mass);
}

// ----------------------------------------------------------------------------

bool CElement::IsVirtual(void) const
{
    return((Z==0)||(Z == 1));
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================




