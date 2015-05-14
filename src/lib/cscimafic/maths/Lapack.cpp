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

#include <Lapack.hpp>
#include <ErrorSystem.hpp>

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

// lapack entry points

extern "C" void dsyev_(char* jobz,char* uplo,int* n,double* a,int* lda,double* w,
                       double* work,int* lwork,int* info);

extern "C" void dgetrf_(int* m,int* n,double* a,int* lda,int* ipiv,int* info);
extern "C" void dgetrs_(char* trans,int* n,int* nrhs,double* a,int* lda,int* ipiv,double* b,int* ldb,int* info);

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

int CLapack::syev(char jobz,char uplo,CFortranMatrix& a,CVector& w,CVector& work)
{
    int info = 0;
    int nrows = a.GetNumberOfRows();
    int nwork = work.GetLength();

    dsyev_(&jobz,&uplo,&nrows,a.GetRawDataField(),&nrows,w.GetRawDataField(),
           work.GetRawDataField(),&nwork,&info);

    return(info);
}

//------------------------------------------------------------------------------

int CLapack::syev(char jobz,char uplo,CFortranMatrix& a,CVector& w)
{
    int     info = 0;
    int     nrows = a.GetNumberOfRows();
    int     nwork = -1;
    double  twork[1];

    // query workspace length
    dsyev_(&jobz,&uplo,&nrows,a.GetRawDataField(),&nrows,w.GetRawDataField(),
           twork,&nwork,&info);

    // allocate work space
    CVector work;
    nwork = static_cast<int>(twork[0]) + 1;
    work.CreateVector(nwork);

    // run again
    dsyev_(&jobz,&uplo,&nrows,a.GetRawDataField(),&nrows,w.GetRawDataField(),
           work.GetRawDataField(),&nwork,&info);

    return(info);
}

//------------------------------------------------------------------------------

int CLapack::solvle(CFortranMatrix& a,CVector& rhs)
{
    int info = 0;
    int ndimm = a.GetNumberOfRows();

    if( ndimm == 0 ){
        ES_ERROR("no rows in rhs");
        return(-1);
    }
    if( a.GetNumberOfRows() != a.GetNumberOfColumns() ){
        ES_ERROR("matrix A must be a square matrix");
        return(-1);
    }
    if( (int)a.GetNumberOfRows() != rhs.GetLength() ){
        ES_ERROR("rhs is not compatible with A");
        return(-1);
    }

    int* indx = new int[ndimm];

    dgetrf_(&ndimm,&ndimm,a.GetRawDataField(),&ndimm,indx,&info);
    if( info != 0 ){
        delete[] indx;
        ES_ERROR("unable to do LU decomposition");
        return(info);
    }

    char trans = 'N';
    int  nrshs = 1;
    dgetrs_(&trans,&ndimm,&nrshs,a.GetRawDataField(),&ndimm,indx,rhs.GetRawDataField(),&ndimm,&info);
    if( info != 0 ){
        delete[] indx;
        ES_ERROR("unable to solve system of linear equations");
        return(info);
    }

    delete[] indx;
    return(info);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
