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

#include <Blas.hpp>
#include <ErrorSystem.hpp>

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

// blas entry points

extern "C" void ddot_(int& N,double& DX,int& INCX,double& DY,int& INCY,double& rv);
extern "C" void gemv_(char& trans,int& M, int& N, double& ALPHA,
                      double& A,int& LDA,double& X,int& INCX,double& BETA,double& Y,int& INCY);

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

double CBlas::dot(CVector& a,CVector& b)
{
    if( a.GetLength() != b.GetLength() ){
        RUNTIME_ERROR("lengths of A and B are not the same");
    }
    int inc = 1;
    double rv = 0.0;
    ddot_(a.GetLength(),a.GetRawDataField(),&inc,b.GetRawDataField(),&inc,&rv);
    return(rv);
}

//------------------------------------------------------------------------------

void CBlas::gemv(double alpha,CFortranMatrix& a,double beta,CVector& x,CVector& y)
{
    int inc = 1;
    char trans = 'N';
    int m = a.GetNumberOfRows();
    int n = a.GetNumberOfColumns();

    if( n != b.GetLength() ){
        RUNTIME_ERROR("matrix - vector inconsistency - columns");
    }
    if( n != y.GetLength() ){
        RUNTIME_ERROR("matrix - vector inconsistency - rows");
    }

    gemv_(&trans,&m,&n,&alpha,a.GetRawDataField(),&m,x.GetRawDataField(),&inc,&beta,y.GetRawDataField(),&inc);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
