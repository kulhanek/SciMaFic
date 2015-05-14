#ifndef XYZGradientH
#define XYZGradientH
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

/*! \brief XYZ gradient support
 */

class SCIMAFIC_PACKAGE CXYZGradient : private CSimpleVector<CPoint> {
public:
// constructor and destructor -------------------------------------------------
    CXYZGradient(void);
    virtual ~CXYZGradient(void);

// I/O operations -------------------------------------------------------------
    /// load gradient from a file
    bool LoadGradient(const CSmallString& name);

    /// save gradient to a file
    bool SaveGradient(const CSmallString& name);

    /// load gradient from XML file
    bool LoadGradient(FILE* p_fin);

    /// save gradient to XML file
    bool SaveGradient(FILE* p_fout);

// size operation  ------------------------------------------------------------
    /// set number of atoms - previous data are destroyed
    void SetNumberOfAtoms(int numofatoms);

    /// return number of atoms
    int  GetNumberOfAtoms(void) const;

// comment --------------------------------------------------------------------
    /// set comment
    void                SetComment(const CSmallString& comment);

    /// get comment
    const CSmallString& GetComment(void) const;

// access methods -------------------------------------------------------------
    /// access individual gradient elements
    CPoint&       operator [] (unsigned int index);

    /// access individual gradient elements
    const CPoint& operator [] (unsigned int index) const;

    /// access individula gradient elements
    const CPoint&   GetGradient(unsigned int index) const;

    /// access individula atom elements
    void            SetGradient(unsigned int index,const CPoint& grd);

// section of private data ----------------------------------------------------
private:
    CSmallString    Comment;
};

// ----------------------------------------------------------------------------

#endif
