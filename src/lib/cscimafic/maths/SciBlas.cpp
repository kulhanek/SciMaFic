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

#include <SciBlas.hpp>
#include <ErrorSystem.hpp>

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

// blas entry points

extern "C" double ddot_(int* N,double* DX,int* INCX,double* DY,int* INCY);
extern "C" void dgemv_(char* trans,int* M, int* N, double* ALPHA,
                      double* A,int* LDA,double* X,int* INCX,double* BETA,double* Y,int* INCY);

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

double CSciBlas::dot(CVector& a,CVector& b)
{
    if( a.GetLength() != b.GetLength() ){
        RUNTIME_ERROR("lengths of A and B are not the same");
    }
    int inc = 1;
    double rv = 0.0;
    int n = a.GetLength();
    rv = ddot_(&n,a.GetRawDataField(),&inc,b.GetRawDataField(),&inc);
    return(rv);
}

//------------------------------------------------------------------------------

void CSciBlas::gemv(double alpha,CFortranMatrix& a,CVector& x,double beta,CVector& y)
{
    int inc = 1;
    char trans = 'N';
    int m = a.GetNumberOfRows();
    int n = a.GetNumberOfColumns();

    if( n != x.GetLength() ){
        RUNTIME_ERROR("matrix - vector inconsistency - columns");
    }
    if( m != y.GetLength() ){
        RUNTIME_ERROR("matrix - vector inconsistency - rows");
    }

    dgemv_(&trans,&m,&n,&alpha,a.GetRawDataField(),&m,x.GetRawDataField(),&inc,&beta,y.GetRawDataField(),&inc);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
