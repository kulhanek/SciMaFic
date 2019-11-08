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

#include <stdio.h>
#include <Matrix.hpp>

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

CMatrix::CMatrix(void)
{
    Rows = 0;
    Columns = 0;
    RowVectors = NULL;
}

//------------------------------------------------------------------------------

CMatrix::~CMatrix(void)
{
    if( RowVectors ) delete[] RowVectors;
    RowVectors = NULL;
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

void CMatrix::CreateMatrix(long unsigned int rows,long unsigned int columns)
{
    if( (rows < 0) || (columns < 0) ){
        INVALID_ARGUMENT("(rows < 0) || (columns < 0)");
    }

    if(Rows > 0) {
        FreeMatrix();
    }
    if( (rows == 0) || (columns == 0) ) return;

    RowVectors = new CVector[rows];

    for(long unsigned int i=0; i < rows; i++ ) {
        RowVectors[i].CreateVector(columns);
    }

    Rows = rows;
    Columns = columns;
}

//------------------------------------------------------------------------------

void CMatrix::FreeMatrix(void)
{
    if( RowVectors ) delete[] RowVectors;
    RowVectors = NULL;
    Rows = 0;
    Columns = 0;
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

void CMatrix::Load(CXMLBinData* p_el)
{

}

//------------------------------------------------------------------------------

void CMatrix::Save(CXMLBinData* p_el)
{

}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

long unsigned int CMatrix::GetNumberOfRows(void)
{
    return(Rows);
}

//------------------------------------------------------------------------------

long unsigned int CMatrix::GetNumberOfColumns(void)
{
    return(Columns);
}

//------------------------------------------------------------------------------

void CMatrix::SetZero(void)
{
    for(long unsigned int i=0; i<Rows; i++) {
        for(long unsigned int j=0; j<Columns; j++) {
            RowVectors[i][j] = 0.0;
        }
    }
}

//------------------------------------------------------------------------------

void CMatrix::SetUnit(void)
{
    if( Rows != Columns ){
        RUNTIME_ERROR("Rows != Columns");
    }

    for(long unsigned int i=0; i<Rows; i++) {
        for(long unsigned int j=0; j<Columns; j++) {
            if( i == j ){
                RowVectors[i][j] = 1.0;
            } else {
                RowVectors[i][j] = 0.0;
            }
        }
    }
}

//------------------------------------------------------------------------------

void CMatrix::operator = (const CMatrix& right)
{
    CopyFrom(right);
}

//------------------------------------------------------------------------------

void CMatrix::operator += (const CMatrix& right)
{
    AddWith(right);
}

//------------------------------------------------------------------------------

void CMatrix::operator -= (const CMatrix& right)
{
    SubWith(right);
}

//------------------------------------------------------------------------------

void CMatrix::operator *= (const CMatrix& right)
{
    MultFromRightWith(right);
}

//---------------------------------------------------------------------------

CVector& CMatrix::operator [] (const unsigned int index)
{
    return(RowVectors[index]);
}

//---------------------------------------------------------------------------

void CMatrix::AddTo(CMatrix& dest) const
{
    /* for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            dest[i][j] += RowVectors[i][j];
            }
        }*/
}

//---------------------------------------------------------------------------

void CMatrix::AddWith(const CMatrix& source)
{
    /*
    for(int i=0; i<size; i++){
       for(int j=0; j<size; j++){
           RowVectors[i][j] += source[i][j];
           }
       } */
}

//---------------------------------------------------------------------------

void CMatrix::SubFrom(CMatrix& dest) const
{
    /*for(int i=0; i<size; i++){
       for(int j=0; j<size; j++){
           dest[i][j] -= RowVectors[i][j];
           }
       }*/

}

//---------------------------------------------------------------------------

void CMatrix::SubWith(const CMatrix& source)
{
    /*for(int i=0; i<size; i++){
       for(int j=0; j<size; j++){
           RowVectors[i][j] -= source[i][j];
           }
       }*/
}

//---------------------------------------------------------------------------

// dest = this * dest

void CMatrix::MultFromLeftTo(CMatrix& dest) const
{
    /* double     pomvect[size];

     for(int i=0; i<size; i++){
        for(int j=0; j<size; j++) pomvect[j]=dest.Field[i][j];    // backup row
        for(int j=0; j<size; j++){
            dest.Field[i][j] = 0;
            for(int k=0; k<size; k++) dest.Field[i][j] += Field[i][k]*pomvect[k];
            }
        }*/
}

//---------------------------------------------------------------------------

// dest = dest * this

void CMatrix::MultFromRightTo(CMatrix& dest) const
{
    /* double     pomvect[size];

     for(int i=0; i<size; i++){
        for(int j=0; j<size; j++) pomvect[j]=dest.Field[i][j];    // backup row
        for(int j=0; j<size; j++){
            dest.Field[i][j] = 0;
            for(int k=0; k<size; k++) dest.Field[i][j] += pomvect[k]*Field[k][j];
            }
        }*/
}

//---------------------------------------------------------------------------

// this = this * source

void CMatrix::MultFromLeftWith(const CMatrix& source)
{
    /*double     pomvect[size];

    for(int i=0; i<size; i++){
       for(int j=0; j<size; j++) pomvect[j]=Field[i][j];    // backup row
       for(int j=0; j<size; j++){
           Field[i][j] = 0;
           for(int k=0; k<size; k++) Field[i][j] += pomvect[k]*source.Field[k][j];
           }
       }*/
}

//---------------------------------------------------------------------------

// this = source * this

void CMatrix::MultFromRightWith(const CMatrix& source)
{
    /*double     pomvect[size];

    for(int i=0; i<size; i++){
       for(int j=0; j<size; j++) pomvect[j]=Field[i][j];    // backup row
       for(int j=0; j<size; j++){
           Field[i][j] = 0;
           for(int k=0; k<size; k++) Field[i][j] += source.Field[i][k]*pomvect[k];
           }
       }*/
}

//---------------------------------------------------------------------------

void CMatrix::CopyTo(CMatrix& dest) const
{
    /*for(int i=0; i<size; i++){
       for(int j=0; j<size; j++){
           dest[i][j] = RowVectors[i][j];
           }
       }*/
}

//---------------------------------------------------------------------------

void CMatrix::CopyFrom(const CMatrix& source)
{
    /*for(int i=0; i<size; i++){
       for(int j=0; j<size; j++){
           RowVectors[i][j] = source[i][j];
           }
       }*/
}

//---------------------------------------------------------------------------

bool CMatrix::Invert(void)
{

    return(false);
}

//---------------------------------------------------------------------------

bool CMatrix::LinearEquations(int rowmut[],double vect[])
{

    return(false);
}

//---------------------------------------------------------------------------

bool CMatrix::LUFactorization(int rowmut[])
{


    return(false);
}

//---------------------------------------------------------------------------

void CMatrix::Transpose(void)
{
    /*
    for(int i=1; i<size; i++){
       for(int j=i; j<size; j++){
           Swap(Field[i][j],Field[j][i]);
           }
       } */
}

//---------------------------------------------------------------------------

void CMatrix::Swap(double& a, double& b)
{
    double swap;
    swap = a;
    a = b;
    b = swap;
}

//---------------------------------------------------------------------------
