#ifndef XYZStructureH
#define XYZStructureH
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

#include <SciMaFicMainHeader.hpp>
#include <stdio.h>
#include <SmallString.hpp>
#include <Point.hpp>
#include <SimpleVector.hpp>

// -----------------------------------------------------------------------------

class CXMLElement;

// -----------------------------------------------------------------------------

class SCIMAFIC_PACKAGE CXYZAtom {
public:
    CXYZAtom(void);

// position -------------------------------------------
    CPoint    Position;

// symbol ---------------------------------------------
    const char* GetSymbol(void) const;
    void        SetSymbol(const char* p_symbol);

// section of private data -------------------------------
private:
    char       Symbol[4];

    friend class CXYZStructure;
};

// ----------------------------------------------------------------------------

class SCIMAFIC_PACKAGE CXYZStructure {
public:
    CXYZStructure(void);
    ~CXYZStructure(void);

// I/O operations -------------------------------------
    bool Load(const CSmallString& name);
    bool Save(const CSmallString& name);

    bool Load(FILE* p_fin);
    bool Save(FILE* p_fout);

    bool Load(CXMLElement* p_ele);
    void Save(CXMLElement* p_ele);

// number of atoms ------------------------------------
    int     GetNumberOfAtoms(void) const;
    void    SetNumberOfAtoms(int numofatoms);

// comment --------------------------------------------
    const CSmallString& GetComment(void);
    void                SetComment(const CSmallString& comment);

// positions ------------------------------------------
    const CPoint&    GetPosition(int index) const;
    void             SetPosition(int index,const CPoint& pos);

// symbols --------------------------------------------
    const char* GetSymbol(int index) const;
    void        SetSymbol(int index,const char* p_symbol);

// section of private data -------------------------------
private:
    CSmallString                Comment;
    CSimpleVector<CXYZAtom>     Atoms;
};

// ----------------------------------------------------------------------------

#endif
