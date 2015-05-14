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

#include <XYZStructure.hpp>
#include <string.h>
#include <ErrorSystem.hpp>
#include <errno.h>
#include <XMLElement.hpp>
#include <XMLIterator.hpp>

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

CXYZStructure::CXYZStructure(void)
{
}

// ----------------------------------------------------------------------------

CXYZStructure::~CXYZStructure(void)
{
    Atoms.FreeVector();
    Comment = NULL;
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

bool CXYZStructure::Load(const CSmallString& name)
{
    FILE* p_file = fopen(name,"r");

    if( p_file == NULL ) {
        CSmallString error;
        error << "unable to open file : " << name << " (" << strerror(errno) << ")";
        ES_ERROR(error);
        return(false);
    }

    bool result = Load(p_file);

    fclose(p_file);

    return(result);
}

// ----------------------------------------------------------------------------

bool CXYZStructure::Load(FILE* p_fin)
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
    for(int i=0; i < GetNumberOfAtoms(); i++) {
        CXYZAtom* p_atom = &Atoms[i];
        if( fscanf(p_fin," %3s %lf %lf %lf",p_atom->Symbol,&p_atom->Position.x,&p_atom->Position.y, &p_atom->Position.z) != 4 ) {
            return(false);
        }
    }

    return(true);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

bool CXYZStructure::Save(const CSmallString& name)
{
    FILE* p_file = fopen(name,"w");

    if( p_file == NULL ) return(false);

    bool result = Save(p_file);

    fclose(p_file);

    return(result);
}

// ----------------------------------------------------------------------------

bool CXYZStructure::Save(FILE* p_fout)
{
    // write number of atoms
    if( fprintf(p_fout,"%d\n",GetNumberOfAtoms()) <= 0 ) return(false);

    // write comment
    if( fprintf(p_fout,"%s\n",(const char*)Comment) <= 0 ) return(false);

    // write data
    for(int i=0; i < GetNumberOfAtoms() ; i++) {
        CXYZAtom* p_atom = &Atoms[i];
        if( fprintf(p_fout,"%3s %14.7f %14.7f %14.7f\n",p_atom->Symbol,p_atom->Position.x,p_atom->Position.y,p_atom->Position.z) <= 0 ) {
            return(false);
        }
    }

    return(true);
}

//------------------------------------------------------------------------------

bool CXYZStructure::Load(CXMLElement* p_ele)
{
    if( p_ele == NULL ) {
        ES_ERROR("p_ele is NULL");
        return(false);
    }

    bool result = true;
    result &= p_ele->GetAttribute("comment",Comment);

    if( result == false ) {
        ES_ERROR("unable to get header I");
        return(false);
    }

    CXMLElement* p_aele = p_ele->GetFirstChildElement("ATOMS");
    if( p_aele == NULL ) {
        ES_ERROR("unable to get ATOMS element");
        return(false);
    }

    int natoms = 0;
    result &= p_aele->GetAttribute("natoms",natoms);
    if( result == false ) {
        ES_ERROR("unable to get header II");
        return(false);
    }
    Atoms.CreateVector(natoms);

    CXMLIterator   I(p_aele);
    for(int i=0; i < Atoms.GetLength(); i++) {
        CXMLElement* p_at = I.GetNextChildElement("ATOM");
        if( p_at == NULL ) {
            ES_ERROR("unable to get ATOM element");
            return(false);
        }
        CXYZAtom* p_atom = &Atoms[i];
        CSmallString symbol;
        result &= p_at->GetAttribute("s",symbol);
        p_atom->SetSymbol(symbol);
        result &= p_at->GetAttribute("x",p_atom->Position.x);
        result &= p_at->GetAttribute("y",p_atom->Position.y);
        result &= p_at->GetAttribute("z",p_atom->Position.z);

        if( result == false ) {
            ES_ERROR("unable to get atom data");
            return(false);
        }
    }

    return(true);
}

//------------------------------------------------------------------------------

void CXYZStructure::Save(CXMLElement* p_ele)
{
    if( p_ele == NULL ) {
        INVALID_ARGUMENT("p_ele is NULL");
    }

    p_ele->SetAttribute("comment",Comment);

    CXMLElement* p_aele = p_ele->CreateChildElement("ATOMS");
    p_aele->SetAttribute("natoms",Atoms.GetLength());

    for(int i=0; i < Atoms.GetLength(); i++) {
        CXMLElement* p_at = p_aele->CreateChildElement("ATOM");

        CXYZAtom* p_atom = &Atoms[i];
        p_at->SetAttribute("s",p_atom->GetSymbol());
        p_at->SetAttribute("x",p_atom->Position.x);
        p_at->SetAttribute("y",p_atom->Position.y);
        p_at->SetAttribute("z",p_atom->Position.z);
    }
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

int CXYZStructure::GetNumberOfAtoms(void) const
{
    return(Atoms.GetLength());
}

// ----------------------------------------------------------------------------

void CXYZStructure::SetNumberOfAtoms(int numofatoms)
{
    Atoms.CreateVector(numofatoms);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

const CSmallString& CXYZStructure::GetComment(void)
{
    return(Comment);
}

// ----------------------------------------------------------------------------

void CXYZStructure::SetComment(const CSmallString& comment)
{
    Comment = comment;
    // remove all \n characters
    for(unsigned int i=0; i < Comment.GetLength(); i++) {
        if( Comment[i] == '\n' ) Comment[i] = '|';
    }
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

const CPoint& CXYZStructure::GetPosition(int index) const
{
    return(Atoms[index].Position);
}

// ----------------------------------------------------------------------------

void CXYZStructure::SetPosition(int index,const CPoint& pos)
{
    Atoms[index].Position = pos;
}

// ----------------------------------------------------------------------------

const char* CXYZStructure::GetSymbol(int index) const
{
    return(Atoms[index].GetSymbol());
}

// ----------------------------------------------------------------------------

void CXYZStructure::SetSymbol(int index,const char* p_symbol)
{
    return(Atoms[index].SetSymbol(p_symbol));
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

CXYZAtom::CXYZAtom(void)
{
    memset(Symbol,0,4);
}

// ----------------------------------------------------------------------------

const char* CXYZAtom::GetSymbol(void) const
{
    return(Symbol);
}

// ----------------------------------------------------------------------------

void  CXYZAtom::SetSymbol(const char* p_symbol)
{
    strncpy(Symbol,p_symbol,3);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================


