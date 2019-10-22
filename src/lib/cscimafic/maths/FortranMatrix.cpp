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

#include <FortranMatrix.hpp>
#include <string.h>
#include <SmallString.hpp>
#include <ErrorSystem.hpp>
#include <XMLBinData.hpp>

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

CFortranMatrix::CFortranMatrix(void)
{
    NRows = 0;
    NColumns = 0;
    Array = NULL;
}

//------------------------------------------------------------------------------

CFortranMatrix::~CFortranMatrix(void)
{
    if( Array ){
        delete[] Array;
        Array = NULL;
    }
}

//------------------------------------------------------------------------------

CFortranMatrix::CFortranMatrix(const CFortranMatrix& src)
{
    CreateMatrix(src.GetNumberOfRows(),src.GetNumberOfColumns());
    if( Array != NULL ) memcpy(Array,src.Array,NRows*NColumns*sizeof(double));
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

size_t CFortranMatrix::GetNumberOfRows(void) const
{
    return(NRows);
}

//------------------------------------------------------------------------------

size_t CFortranMatrix::GetNumberOfColumns(void) const
{
    return(NColumns);
}

//------------------------------------------------------------------------------

double* CFortranMatrix::GetRawDataField(void)
{
    return(Array);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

bool CFortranMatrix::CreateMatrix(size_t nrows,size_t ncolumns)
{
    if( Array != NULL ) {
        delete[] Array;
    }
    Array = NULL;
    NRows = nrows;
    NColumns = ncolumns;
    if( NRows*NColumns > 0 ) {
        try {
            Array =  new double[NRows*NColumns];
        } catch(...) {
            CSmallString error;
            error << "unable to allocate fortran matrix for dim(" << NRows << "," << NColumns <<")";
            ES_ERROR(error);
            NRows = 0;
            NColumns = 0;
            return(false);
        }
    }
    return(true);
}

//------------------------------------------------------------------------------

void CFortranMatrix::FreeMatrix(void)
{
    if( Array ){
        delete[] Array;
        Array = NULL;
    }
    NRows = 0;
    NColumns = 0;
}

//------------------------------------------------------------------------------

void CFortranMatrix::SetZero(void)
{
    for(size_t i=0; i < NRows*NColumns; i++) {
        Array[i] = 0.0;
    }
}

//------------------------------------------------------------------------------

bool CFortranMatrix::SetUnit(void)
{
    if( NRows != NColumns ) {
        ES_ERROR("squared matrix is requied");
        return(false);
    }

    for(size_t i=0; i < NRows; i++) {
        for(size_t j=0; j < NColumns; j++) {
            if( i != j ) {
                (*this)[i][j] = 0.0;
            } else {
                (*this)[i][j] = 1.0;
            }
        }
    }
    return(true);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

const CFortranRow CFortranMatrix::operator[](const size_t row) const
{
    return(CFortranRow(this,row));
}

//------------------------------------------------------------------------------

CFortranRow CFortranMatrix::operator[](const size_t row)
{
    return(CFortranRow(this,row));
}

//------------------------------------------------------------------------------

void CFortranMatrix::operator=(const CFortranMatrix& src)
{
    CreateMatrix(src.GetNumberOfRows(),src.GetNumberOfColumns());
    if( Array != NULL ) memcpy(Array,src.Array,NRows*NColumns*sizeof(double));
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

void CFortranMatrix::Load(CXMLBinData* p_ele)
{
    if( p_ele == NULL ) {
        INVALID_ARGUMENT("p_ele is NULL");
    }

// get size
    size_t size;
    size = p_ele->GetLength();
    if( size <= 0 ) return;

    size_t rows = 0;
    size_t columns = 0;

    p_ele->GetAttribute("rows",rows);
    p_ele->GetAttribute("columns",columns);

    CreateMatrix(rows,columns);

    if( size != rows*columns*sizeof(double) ){
        RUNTIME_ERROR("inconsistent size");
    }

// load data
    EXMLBinDataType ltype = p_ele->GetDataType();

    if( ltype != EXBDT_DOUBLE ) {
        LOGIC_ERROR("type mismatch");
    }

// copy data
    void* p_data = p_ele->GetData();
    if( p_data == NULL ) {
        RUNTIME_ERROR("unable to get data");
    }
    memcpy(Array,p_data,size);
}

//------------------------------------------------------------------------------

void CFortranMatrix::Save(CXMLBinData* p_ele)
{
    if( p_ele == NULL ) {
        INVALID_ARGUMENT("p_ele is NULL");
    }

// set size
    p_ele->SetAttribute("rows",NRows);
    p_ele->SetAttribute("columns",NColumns);

    if( Array == NULL ) return;

// copy data
    p_ele->SetData(Array,NRows*NColumns*sizeof(double),false,EXBDT_DOUBLE);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

