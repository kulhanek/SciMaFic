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

#include <XYZGradient.hpp>
#include <string.h>

//==============================================================================
// -----------------------------------------------------------------------------
//==============================================================================

CXYZGradient::CXYZGradient(void)
{
}

// -----------------------------------------------------------------------------

CXYZGradient::~CXYZGradient(void)
{
}

//==============================================================================
// -----------------------------------------------------------------------------
//==============================================================================

bool CXYZGradient::LoadGradient(const CSmallString& name)
{
    FILE* p_file = fopen(name,"r");

    if( p_file == NULL ) return(false);

    bool result = LoadGradient(p_file);

    fclose(p_file);

    return(result);
}

// -----------------------------------------------------------------------------

bool CXYZGradient::LoadGradient(FILE* p_fin)
{
    // clean previous data
    SetNumberOfAtoms(0);

    int numofatoms = 0;
    // get number of atoms
    if( fscanf(p_fin,"%d",&numofatoms) != 1 ) return(false);

    if( numofatoms == 0 ) return(false);
    SetNumberOfAtoms(numofatoms);

    // skip ends of the first line
    int c = 0;
    while( ((c = fgetc(p_fin)) != '\n') && (feof(p_fin) == false) );
    // read comment line
    if( Comment.ReadLineFromFile(p_fin) == false ) return(false);

    // remove terminal '\n' characters in Comment
    if( Comment.GetLength() > 1 ) {
        Comment[Comment.GetLength()-1] = '\0';
    }

    // load data
    for(size_t i=0; i < GetLength(); i++) {
        /*    CPoint* p_atom = &AtomList[i];
            if( fscanf(p_fin,"%lf %lf %lf",&p_atom->x,&p_atom->y,&p_atom->z) != 3 ) return(false);*/
    }

    return(true);
}

//==============================================================================
// -----------------------------------------------------------------------------
//==============================================================================

bool CXYZGradient::SaveGradient(const CSmallString& name)
{
    FILE* p_file = fopen(name,"w");

    if( p_file == NULL ) return(false);

    bool result = SaveGradient(p_file);

    fclose(p_file);

    return(result);
}

// -----------------------------------------------------------------------------

bool CXYZGradient::SaveGradient(FILE* p_fout)
{
    // write number of atoms
    if( fprintf(p_fout,"%ld\n",GetLength()) <= 0 ) return(false);

    // write comment
    if( fprintf(p_fout,"%s\n",(const char*)Comment) <= 0 ) return(false);

    // write data
    for(size_t i=0; i < GetLength(); i++) {
        /*    CPoint* p_atom = &AtomList[i];
             if( fprintf(p_fout,"%+16.13e %+16.13e %+16.13e\n",p_atom->x,p_atom->y,p_atom->z) <= 0 ) */return(false);
    }

    return(true);
}

//==============================================================================
// -----------------------------------------------------------------------------
//==============================================================================

void CXYZGradient::SetNumberOfAtoms(int numofatoms)
{
    Comment = NULL;
    CreateVector(numofatoms);
}

// -----------------------------------------------------------------------------

int CXYZGradient::GetNumberOfAtoms(void) const
{
    return(GetLength());
}

//==============================================================================
// -----------------------------------------------------------------------------
//==============================================================================

void CXYZGradient::SetComment(const CSmallString& comment)
{
    Comment = comment;
}

// -----------------------------------------------------------------------------

const CSmallString& CXYZGradient::GetComment(void) const
{
    return(Comment);
}

//==============================================================================
// -----------------------------------------------------------------------------
//==============================================================================

CPoint& CXYZGradient::operator [] (unsigned int index)
{
    return(*this[index]);
}

// -----------------------------------------------------------------------------

const CPoint& CXYZGradient::operator [] (unsigned int index) const
{
    return(*this[index]);
}

// -----------------------------------------------------------------------------

const CPoint& CXYZGradient::GetGradient(unsigned int index) const
{
    return(*this[index]);
}

// -----------------------------------------------------------------------------

void CXYZGradient::SetGradient(unsigned int index,const CPoint& grd)
{
    *this[index] = grd;
}

//==============================================================================
// -----------------------------------------------------------------------------
//==============================================================================

