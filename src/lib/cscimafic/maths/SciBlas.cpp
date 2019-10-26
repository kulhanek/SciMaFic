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
#include <BlasLapack.hpp>

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

double CSciBlas::dot(CVector& a,CVector& b)
{
    if( a.GetLength() != b.GetLength() ){
        RUNTIME_ERROR("lengths of A and B are not the same");
    }
    BL_INT inc = 1;
    double rv = 0.0;
    BL_INT n = a.GetLength();
    rv = ddot_(&n,a.GetRawDataField(),&inc,b.GetRawDataField(),&inc);
    return(rv);
}

//------------------------------------------------------------------------------

void CSciBlas::gemv(double alpha,CFortranMatrix& a,CVector& x,double beta,CVector& y)
{
    BL_INT inc = 1;
    char trans = 'N';
    BL_INT m = a.GetNumberOfRows();
    BL_INT n = a.GetNumberOfColumns();

    if( a.GetNumberOfColumns() != x.GetLength() ){
        RUNTIME_ERROR("matrix - vector inconsistency - columns");
    }
    if( a.GetNumberOfRows() != y.GetLength() ){
        RUNTIME_ERROR("matrix - vector inconsistency - rows");
    }

    dgemv_(&trans,&m,&n,&alpha,a.GetRawDataField(),&m,x.GetRawDataField(),&inc,&beta,y.GetRawDataField(),&inc);
}

//------------------------------------------------------------------------------

//extern "C" void dgemm_(char* transa, char* transb,BL_INT* M,BL_INT* N,BL_INT* K,double* alpha,
//                       double* a,BL_INT* lda,double* b,BL_INT* ldb,double* beta,double* c, BL_INT* ldc);

void CSciBlas::gemm(double alpha,CFortranMatrix& a,CFortranMatrix& b,double beta,CFortranMatrix& c)
{
    char transa = 'N';
    char transb = 'N';
    BL_INT m = a.GetNumberOfRows();
    BL_INT n = b.GetNumberOfColumns();
    BL_INT k = a.GetNumberOfColumns();

    if( a.GetNumberOfColumns() != b.GetNumberOfRows() ){
        RUNTIME_ERROR("matrix - matrix inconsistency");
    }

    dgemm_(&transa,&transb,&m,&n,&k,&alpha,a.GetRawDataField(),&m,b.GetRawDataField(),&k,&beta,c.GetRawDataField(),&m);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
