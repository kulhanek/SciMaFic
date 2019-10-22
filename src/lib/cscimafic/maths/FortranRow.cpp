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

#include <FortranRow.hpp>
#include <FortranMatrix.hpp>

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

double CFortranRow::operator[](const size_t column) const
{
    return(Matrix->Array[column*Matrix->NRows + Row]);
}

//------------------------------------------------------------------------------

double& CFortranRow::operator[](const size_t column)
{
    return(Matrix->Array[column*Matrix->NRows + Row]);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

CFortranRow::CFortranRow(CFortranMatrix* p_matrix,const size_t row)
{
    Matrix = p_matrix;
    Row = row;
}

//------------------------------------------------------------------------------

CFortranRow::CFortranRow(const CFortranMatrix* p_matrix,const size_t row)
{
    Matrix = (CFortranMatrix*)p_matrix;
    Row = row;
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

