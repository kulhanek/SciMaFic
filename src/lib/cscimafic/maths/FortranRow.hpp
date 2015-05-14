#ifndef FortranRowH
#define FortranRowH
//==============================================================================
//    Copyright 2010 Petr Kulhanek
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

//------------------------------------------------------------------------------

class CFortranMatrix;

//------------------------------------------------------------------------------

class SCIMAFIC_PACKAGE CFortranRow {
public:
// access method -------------------------------------------------------------
    double  operator[](int column) const;
    double& operator[](int column);

private:
    CFortranRow(CFortranMatrix* p_matrix,unsigned int row);
    CFortranRow(const CFortranMatrix* p_matrix,unsigned int row);

// section of private data ----------------------------------------------------
private:
    CFortranMatrix* Matrix;
    unsigned int    Row;

    friend class CFortranMatrix;
};

//------------------------------------------------------------------------------

#endif
