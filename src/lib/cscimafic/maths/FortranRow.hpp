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
#include <stddef.h>

//------------------------------------------------------------------------------

class CFortranMatrix;

//------------------------------------------------------------------------------

class SCIMAFIC_PACKAGE CFortranRow {
public:
// access method -------------------------------------------------------------
    double  operator[](const size_t column) const;
    double& operator[](const size_t column);

private:
    CFortranRow(CFortranMatrix* p_matrix,const size_t row);
    CFortranRow(const CFortranMatrix* p_matrix,const size_t row);

// section of private data ----------------------------------------------------
private:
    CFortranMatrix* Matrix;
    size_t          Row;

    friend class CFortranMatrix;
};

//------------------------------------------------------------------------------

#endif
