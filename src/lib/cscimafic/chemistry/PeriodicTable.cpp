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
#include <PeriodicTable.hpp>
#include <XMLDocument.hpp>
#include <ErrorSystem.hpp>

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================


CPeriodicTable PeriodicTable;

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

CPeriodicTable::CPeriodicTable(void)
{
    for(int i=0; i<CPT_NUM_OF_ELEMENTS; i++) {
        Elements[i].Symbol = Symbols[i];
        Elements[i].Name = Names[i];
        Elements[i].Mass = Masses[i];
        Elements[i].Z = i;
        Elements[i].Color = Color[i];
        Elements[i].vdWRadius = vdWRadii[i];
        Elements[i].CovalentRadius = CovalentRadii[i];
        Elements[i].Electronegativity = Electronegativity[i];
    }
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

const CElement* CPeriodicTable::GetElement(unsigned z) const
{
    return(&Elements[z]);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

float CPeriodicTable::GetBondDistance(int z1,int z2) const
{
    const CElement* p_e1 = GetElement(z1);
    if( p_e1 == NULL ) return(1.0);
    const CElement* p_e2 = GetElement(z2);
    if( p_e2 == NULL ) return(1.0);

    //http://en.wikipedia.org/wiki/Covalent_radius_of_fluorine
    //Schomaker and Stevenson

    float d = p_e1->GetCovalentRadius() + p_e2->GetCovalentRadius();
    d  += 0.09*fabs(p_e1->GetElectronegativity() - p_e2->GetElectronegativity());

    return(d);
}

//------------------------------------------------------------------------------

int CPeriodicTable::SearchZBySymbol(const CSmallString& symbol) const
{
    if( symbol == NULL ) return(0);
    if( symbol == "Dummy" ) return(-1);

    CSmallString   tmp(symbol);

    if( islower(tmp[0]) != 0 ) {
        tmp[0] = tmp[0] - 'a' + 'A';
    }

    for(unsigned i=0; i<CPT_NUM_OF_ELEMENTS; i++) {
        if( strcmp(tmp,Elements[i].Symbol) == 0) return(i);
    }

    return(0);
}

//------------------------------------------------------------------------------

int CPeriodicTable::SearchZByName(const CSmallString& name) const
{
    if( name == NULL ) return(0);

    if( name == "Dummy" ) return(-1);

    for(unsigned i=0; i<CPT_NUM_OF_ELEMENTS; i++) {
        if( name == Elements[i].Name ) return(i);
    }

    return(0);
}

//------------------------------------------------------------------------------

int CPeriodicTable::SearchZByMass(float mass,float tolerance) const
{
    if( mass == 0 ) return(0);

    // do not include Vir
    for(unsigned i=1; i<CPT_NUM_OF_ELEMENTS; i++) {
        if( fabs(Elements[i].Mass - mass) < tolerance ) return(i);
    }

    return(0);
}

//------------------------------------------------------------------------------

float CPeriodicTable::GetVdWRadius(int z) const
{
    if( (z < 0) || (z >= CPT_NUM_OF_ELEMENTS) ) return(Elements[0].vdWRadius);
    return((Elements[z].vdWRadius));
}

//------------------------------------------------------------------------------

float CPeriodicTable::GetCovalentRadius(int z) const
{
    if( (z < 0) || (z >= CPT_NUM_OF_ELEMENTS) ) return(Elements[0].CovalentRadius);
    return((Elements[z].CovalentRadius));
}


//------------------------------------------------------------------------------

float CPeriodicTable::GetMass(int z) const
{
    if( (z < 0) || (z >= CPT_NUM_OF_ELEMENTS) ) return(Elements[0].Mass);
    return((Elements[z].Mass));
}

//------------------------------------------------------------------------------

CSmallColor<float> CPeriodicTable::GetColor(int z) const
{
    if( (z < 0) || (z >= CPT_NUM_OF_ELEMENTS) ) return(Elements[0].Color);
    return(Elements[z].Color);
}

//------------------------------------------------------------------------------

const char* CPeriodicTable::GetSymbol(int z) const
{
    if( z == -1 ) return("Dummy");
    if( z >= CPT_NUM_OF_ELEMENTS ) return("Unknown");
    return((Elements[z].Symbol));
}

//------------------------------------------------------------------------------

const char* CPeriodicTable::GetName(int z) const
{
    if( z == -1 ) return("Dummy");
    if( z >= CPT_NUM_OF_ELEMENTS ) return("Unknown");
    return((Elements[z].Name));
}

//------------------------------------------------------------------------------

const CElement* CPeriodicTable::SearchByName(const CSmallString& name) const
{
    for(unsigned i=0; i<CPT_NUM_OF_ELEMENTS; i++) {
        if(strcmp(Elements[i].Name,name)==0)return(&Elements[i]);
    }
    return(&Elements[0]);
}

//------------------------------------------------------------------------------

const CElement* CPeriodicTable::SearchBySymbol(const CSmallString& symbol) const
{
    for(unsigned i=0; i<CPT_NUM_OF_ELEMENTS; i++) {
        if( Symbols[i] != NULL ) {
            if(strcmp(Symbols[i],symbol)==0)return(&Elements[i]);
        }
    }
    return(NULL);
}

// ----------------------------------------------------------------------------

const CElement* CPeriodicTable::GetVirtual(void) const
{
    return(&Elements[0]);
}

// ----------------------------------------------------------------------------

bool CPeriodicTable::IsVirtual(int z) const
{
    return((z==0)||(z == 1));
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================



