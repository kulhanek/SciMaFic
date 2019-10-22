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

#include <SciLapack.hpp>
#include <ErrorSystem.hpp>
#include <algorithm>
#include <SciBlas.hpp>
#include <sstream>

// MKL support
#ifdef HAVE_MKL_PARALLEL
// hack - disable loading mkl_lapack.h, which conflicts with BlasLapack.hpp
#define _MKL_LAPACK_H_
#include <mkl.h>
#endif

#include <BlasLapack.hpp>

using namespace  std;

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

void CSciLapack::PrintExecInfo(CVerboseStr& vout)
{
#ifdef HAVE_MKL
#ifdef HAVE_MKL_PARALLEL
    {
        int ncpus = mkl_get_max_threads();
        vout << "   Lapack/Blas via MKL - number of threads: " << ncpus << endl;
    }
#else
        vout << "   Lapack/Blas via MKL - sequential mode." << endl;
#endif
#else
    vout << "   Native Lapack/Blas - sequential mode." << endl;
#endif
}

//------------------------------------------------------------------------------

void CSciLapack::SetNumThreadsLocal(int nthrs)
{
#ifdef HAVE_MKL
#ifdef HAVE_MKL_PARALLEL
    mkl_set_num_threads_local(nthrs);
#endif
#endif
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

int CSciLapack::syev(char jobz,char uplo,CFortranMatrix& a,CVector& w,CVector& work)
{
    BL_INT info = 0;
    BL_INT nrows = a.GetNumberOfRows();
    BL_INT nwork = work.GetLength();

    dsyev_(&jobz,&uplo,&nrows,a.GetRawDataField(),&nrows,w.GetRawDataField(),
           work.GetRawDataField(),&nwork,&info);

    return(info);
}

//------------------------------------------------------------------------------

int CSciLapack::syev(char jobz,char uplo,CFortranMatrix& a,CVector& w)
{
    BL_INT     info = 0;
    BL_INT     nrows = a.GetNumberOfRows();
    BL_INT     nwork = -1;
    double  twork[1];

    // query workspace length
    dsyev_(&jobz,&uplo,&nrows,a.GetRawDataField(),&nrows,w.GetRawDataField(),
           twork,&nwork,&info);

    if( info != 0 ){
        CSmallString error;
        error << "unable to determine lwork, info = " << info;
        INVALID_ARGUMENT(error);
    }

    // allocate work space
    CVector work;
    nwork = static_cast<BL_INT>(twork[0]) + 1;
    work.CreateVector(nwork);

    // run again
    dsyev_(&jobz,&uplo,&nrows,a.GetRawDataField(),&nrows,w.GetRawDataField(),
           work.GetRawDataField(),&nwork,&info);

    return(info);
}

//------------------------------------------------------------------------------

int CSciLapack::solvle(CFortranMatrix& a,CVector& rhs)
{
    BL_INT info = 0;
    BL_INT ndimm = a.GetNumberOfRows();

    if( ndimm == 0 ){
        ES_ERROR("no rows in rhs");
        return(-1);
    }
    if( a.GetNumberOfRows() != a.GetNumberOfColumns() ){
        ES_ERROR("matrix A must be a square matrix");
        return(-1);
    }
    if( a.GetNumberOfRows() != rhs.GetLength() ){
        ES_ERROR("rhs is not compatible with A");
        return(-1);
    }

    BL_INT* indx = new BL_INT[ndimm];

    dgetrf_(&ndimm,&ndimm,a.GetRawDataField(),&ndimm,indx,&info);
    if( info != 0 ){
        delete[] indx;
        ES_ERROR("unable to do LU decomposition");
        return(info);
    }

    char trans = 'N';
    BL_INT  nrshs = 1;
    dgetrs_(&trans,&ndimm,&nrshs,a.GetRawDataField(),&ndimm,indx,rhs.GetRawDataField(),&ndimm,&info);
    if( info != 0 ){
        delete[] indx;
        ES_ERROR("unable to solve system of linear equations");
        return(info);
    }

    delete[] indx;
    return(info);
}

//------------------------------------------------------------------------------

int CSciLapack::gelsd(CFortranMatrix& a,CVector& rhs,double rcond,int& rank)
{
    BL_INT m = a.GetNumberOfRows();
    BL_INT n = a.GetNumberOfColumns();
    BL_INT nrhs = 1;
    BL_INT lda = m;
    BL_INT ldb = std::max(m,n);

    CVector s;
    BL_INT     ns = std::min(m,n);
    s.CreateVector(ns);

    BL_INT info = 0;

    // query work size
    BL_INT     lwork = -1;
    double  twork[1];

    // printf("lwork = %d\n",lwork);

    CSimpleVector<BL_INT>  iwork;
    BL_INT li = 3*std::min(m,n)*std::min(m,n) + 11*std::min(m,n);
    iwork.CreateVector(li);

    BL_INT lrank = 0;

    dgelsd_(&m,&n,&nrhs,a.GetRawDataField(),&lda,rhs.GetRawDataField(),&ldb,s.GetRawDataField(),
            &rcond,&lrank,twork,&lwork,iwork.GetRawDataField(),&info);

    rank = lrank;

    if( info != 0 ){
        CSmallString error;
        error << "unable to determine lwork, info = " << info;
        INVALID_ARGUMENT(error);
    }

    lwork = static_cast<BL_INT>(twork[0]) + 1;
    if( lwork < 0 ){
        stringstream error;
        error << "memory request overflow, twork = " << twork[0] << " -> lwork = " << lwork;
        RUNTIME_ERROR(error.str());
    }

    // printf("lwork = %d\n",lwork);

    CSimpleVector<double>  work;
    work.CreateVector(lwork);

    lrank = 0;

    // run svd
    dgelsd_(&m,&n,&nrhs,a.GetRawDataField(),&lda,rhs.GetRawDataField(),&ldb,s.GetRawDataField(),
            &rcond,&lrank,work.GetRawDataField(),&lwork,iwork.GetRawDataField(),&info);

    rank = lrank;

    return(info);
}

//------------------------------------------------------------------------------

int CSciLapack::gels(CFortranMatrix& a,CVector& rhs)
{
    char trans = 'N';
    BL_INT m = a.GetNumberOfRows();
    BL_INT n = a.GetNumberOfColumns();
    BL_INT nrhs = 1;
    BL_INT lda = m;
    BL_INT ldb = std::max(m,n);
    BL_INT info = 0;

    // query work size
    BL_INT     lwork = -1;
    double  twork[1];

    dgels_(&trans,&m,&n,&nrhs,a.GetRawDataField(),&lda,rhs.GetRawDataField(),&ldb,
           twork,&lwork,&info);

    if( info != 0 ){
        CSmallString error;
        error << "unable to determine lwork, info = " << info;
        INVALID_ARGUMENT(error);
        return(info);
    }

    lwork = static_cast<BL_INT>(twork[0]) + 1;
    if( lwork < 0 ){
        stringstream error;
        error << "memory request overflow, twork = " << twork[0] << " -> lwork = " << lwork;
        RUNTIME_ERROR(error.str());
    }

    // printf("lwork = %d\n",lwork);

    CSimpleVector<double>  work;
    work.CreateVector(lwork);

    // run
    dgels_(&trans,&m,&n,&nrhs,a.GetRawDataField(),&lda,rhs.GetRawDataField(),&ldb,
            work.GetRawDataField(),&lwork,&info);

    return(info);
}

//------------------------------------------------------------------------------

int CSciLapack::invLU(CFortranMatrix& a,double& logdet)
{
    BL_INT info = 0;
    BL_INT ndimm = a.GetNumberOfRows();

    logdet = 0.0;

    if( ndimm == 0 ){
        ES_ERROR("no rows in a");
        return(-1);
    }
    if( a.GetNumberOfRows() != a.GetNumberOfColumns() ){
        ES_ERROR("matrix A must be a square matrix");
        return(-1);
    }

    BL_INT* indx = new BL_INT[ndimm];

    dgetrf_(&ndimm,&ndimm,a.GetRawDataField(),&ndimm,indx,&info);
    if( info != 0 ){
        delete[] indx;
        ES_ERROR("unable to do LU decomposition");
        return(info);
    }

    // calculate log determinat of A
    for(BL_INT i=0; i < ndimm; i++){
        logdet += log(fabs(a[i][i]));
    }

    // query work size
    BL_INT     lwork = -1;
    double  twork[1];

    dgetri_(&ndimm,a.GetRawDataField(),&ndimm,indx,twork,&lwork,&info);

    if( info != 0 ){
        delete[] indx;
        CSmallString error;
        error << "unable to determine lwork, info = " << info;
        INVALID_ARGUMENT(error);
        return(info);
    }

    lwork = static_cast<BL_INT>(twork[0]) + 1;
    if( lwork < 0 ){
        stringstream error;
        error << "memory request overflow, twork = " << twork[0] << " -> lwork = " << lwork;
        RUNTIME_ERROR(error.str());
    }

    // printf("lwork = %d\n",lwork);

    CSimpleVector<double>  work;
    work.CreateVector(lwork);

    // run
    dgetri_(&ndimm,a.GetRawDataField(),&ndimm,indx,work,&lwork,&info);

    if( info != 0 ){
        delete[] indx;
        CSmallString error;
        error << "unable to invert the matrix, info = " << info;
        INVALID_ARGUMENT(error);
        return(info);
    }

    delete[] indx;

    return(info);
}

//------------------------------------------------------------------------------

int CSciLapack::invLL(CFortranMatrix& a,double& logdet)
{
    BL_INT info = 0;
    BL_INT ndimm = a.GetNumberOfRows();

    logdet = 0.0;

    if( ndimm == 0 ){
        ES_ERROR("no rows in a");
        return(-1);
    }
    if( a.GetNumberOfRows() != a.GetNumberOfColumns() ){
        ES_ERROR("matrix A must be a square matrix");
        return(-1);
    }

    char uplo = 'L';
    dpotrf_(&uplo,&ndimm,a.GetRawDataField(),&ndimm,&info);
    if( info != 0 ){
        ES_ERROR("unable to do LL decomposition");
        return(info);
    }

    // calculate log determinat of A
    for(BL_INT i=0; i < ndimm; i++){
        logdet += 2.0*log(fabs(a[i][i]));
    }

    dpotri_(&uplo,&ndimm,a.GetRawDataField(),&ndimm,&info);

    if( info != 0 ){
        CSmallString error;
        error << "unable to invert the matrix, info = " << info;
        INVALID_ARGUMENT(error);
        return(info);
    }

    // reconstruct the upper part of matrix
    for(BL_INT i=0; i < ndimm; i++){
        for(BL_INT j=0; j < i; j++){
            a[j][i] = a[i][j];
        }
    }

    return(info);
}

//------------------------------------------------------------------------------

int CSciLapack::invSVD1(CFortranMatrix& a,double& logdet,double rcond,int& rank,double& a_rcond)
{
    BL_INT info = 0;
    BL_INT ndimm = a.GetNumberOfRows();

    logdet = 0.0;
    rank = 0;
    a_rcond = 0.0;

    if( ndimm == 0 ){
        ES_ERROR("no rows in a");
        return(-1);
    }
    if( a.GetNumberOfRows() != a.GetNumberOfColumns() ){
        ES_ERROR("matrix A must be a square matrix");
        return(-1);
    }

    BL_INT m = a.GetNumberOfRows();
    BL_INT n = a.GetNumberOfColumns();
    BL_INT k = std::min(m,n);

    CVector         sig;
    CFortranMatrix  u;
    CFortranMatrix  vt;
    CFortranMatrix  sig_plus;
    CFortranMatrix  temp_mat;

    sig.CreateVector(k);
    u.CreateMatrix(m,m);
    vt.CreateMatrix(n,n);
    sig_plus.CreateMatrix(n,m);
    temp_mat.CreateMatrix(n,m);

    u.SetZero();
    vt.SetZero();
    sig.SetZero();
    sig_plus.SetZero();

    // query work size
    BL_INT     lwork = -1;
    double  twork[1];

    //     lwork = -1
    char mode = 'A';
    dgesvd_(&mode, &mode, &m, &n, a.GetRawDataField(), &m, sig.GetRawDataField(), u.GetRawDataField(), &m,
            vt.GetRawDataField(), &n, twork, &lwork, &info);

    if( info != 0 ){
        CSmallString error;
        error << "unable to determine lwork, info = " << info;
        INVALID_ARGUMENT(error);
        return(info);
    }

    lwork = static_cast<BL_INT>(twork[0]) + 1;
    if( lwork < 0 ){
        stringstream error;
        error << "memory request overflow, twork = " << twork[0] << " -> lwork = " << lwork;
        RUNTIME_ERROR(error.str());
    }

    // printf("lwork = %d\n",lwork);

    CSimpleVector<double>  work;
    work.CreateVector(lwork);

    // run
    dgesvd_(&mode, &mode, &m, &n, a.GetRawDataField(), &m, sig.GetRawDataField(), u.GetRawDataField(), &m,
            vt.GetRawDataField(), &n, work.GetRawDataField(), &lwork, &info);

    if( info != 0 ){
        CSmallString error;
        error << "unable to calculate SVD, info = " << info;
        INVALID_ARGUMENT(error);
        return(info);
    }

    // invert singular numbers
    double maxval = sig[0];
    double minval = sig[0];
    for(size_t i=0; i < (size_t)k; i++){
        if( maxval < sig[i] ){
            maxval = sig[i];
        }
        if( minval > sig[i] ){
            minval = sig[i];
        }
    }

    a_rcond = minval/maxval;

    for(size_t i=0; i < (size_t)k; i++){
        if( sig[i] > rcond*maxval ) {
           logdet += log(fabs(sig[i]));
           sig_plus[i][i] = 1.0/sig[i];
           rank++;
        } else {
           sig_plus[i][i] = 0.0;
        }
    }

    double  one = 1.0;
    double  zero = 0.0;
    char    nmode = 'N';
    char    tmode = 'T';

    // build pseudoinverse: V*sig_plus*UT
    dgemm_(&nmode, &tmode, &n, &m, &m, &one, sig_plus.GetRawDataField(), &n, u.GetRawDataField(), &m, &zero,
           temp_mat.GetRawDataField(), &n);
    dgemm_(&tmode, &nmode, &n, &m, &n, &one, vt.GetRawDataField(), &n, temp_mat.GetRawDataField(), &n, &zero,
           a.GetRawDataField(), &n);

    return(info);
}

//------------------------------------------------------------------------------

int CSciLapack::invSVD2(CFortranMatrix& a,double& logdet,double rcond,int& rank,double& a_rcond)
{
    BL_INT info = 0;
    BL_INT ndimm = a.GetNumberOfRows();

    logdet = 0.0;
    rank = 0;
    a_rcond = 0.0;

    if( ndimm == 0 ){
        ES_ERROR("no rows in a");
        return(-1);
    }
    if( a.GetNumberOfRows() != a.GetNumberOfColumns() ){
        ES_ERROR("matrix A must be a square matrix");
        return(-1);
    }

    BL_INT m = a.GetNumberOfRows();
    BL_INT n = a.GetNumberOfColumns();
    BL_INT k = std::min(m,n);

    CVector         sig;
    CFortranMatrix  u;
    CFortranMatrix  vt;
    CFortranMatrix  sig_plus;
    CFortranMatrix  temp_mat;

    sig.CreateVector(k);
    u.CreateMatrix(m,m);
    vt.CreateMatrix(n,n);
    sig_plus.CreateMatrix(n,m);
    temp_mat.CreateMatrix(n,m);

    u.SetZero();
    vt.SetZero();
    sig.SetZero();
    sig_plus.SetZero();

    BL_INT* iwork = new BL_INT[8*k];

    // query work size
    BL_INT     lwork = -1;
    double  twork[1];

    //     lwork = -1
    char mode = 'A';
    dgesdd_(&mode, &m, &n, a.GetRawDataField(), &m, sig.GetRawDataField(), u.GetRawDataField(), &m,
            vt.GetRawDataField(), &n, twork, &lwork, iwork, &info);

    if( info != 0 ){
        delete[] iwork;
        CSmallString error;
        error << "unable to determine lwork, info = " << info;
        INVALID_ARGUMENT(error);
        return(info);
    }

    lwork = static_cast<BL_INT>(twork[0]) + 1;
    if( lwork < 0 ){
        stringstream error;
        error << "memory request overflow, twork = " << twork[0] << " -> lwork = " << lwork;
        RUNTIME_ERROR(error.str());
    }

    // printf("lwork = %d\n",lwork);

    CSimpleVector<double>  work;
    work.CreateVector(lwork);

    // run
    dgesdd_(&mode, &m, &n, a.GetRawDataField(), &m, sig.GetRawDataField(), u.GetRawDataField(), &m,
            vt.GetRawDataField(), &n, work.GetRawDataField(), &lwork, iwork, &info);

    if( info != 0 ){
        delete[] iwork;
        CSmallString error;
        error << "unable to calculate SVD, info = " << info;
        INVALID_ARGUMENT(error);
        return(info);
    }

    delete[] iwork;

    // invert singular numbers
    double maxval = sig[0];
    double minval = sig[0];
    for(size_t i=0; i < (size_t)k; i++){
        if( maxval < sig[i] ){
            maxval = sig[i];
        }
        if( minval > sig[i] ){
            minval = sig[i];
        }
    }

    a_rcond = minval/maxval;

    for(size_t i=0; i < (size_t)k; i++){
        if( sig[i] > rcond*maxval ) {
           logdet += log(fabs(sig[i]));
           sig_plus[i][i] = 1.0/sig[i];
           rank++;
        } else {
           sig_plus[i][i] = 0.0;
        }
    }

    double  one = 1.0;
    double  zero = 0.0;
    char    nmode = 'N';
    char    tmode = 'T';

    // build pseudoinverse: V*sig_plus*UT
    dgemm_(&nmode, &tmode, &n, &m, &m, &one, sig_plus.GetRawDataField(), &n, u.GetRawDataField(), &m, &zero,
           temp_mat.GetRawDataField(), &n);
    dgemm_(&tmode, &nmode, &n, &m, &n, &one, vt.GetRawDataField(), &n, temp_mat.GetRawDataField(), &n, &zero,
           a.GetRawDataField(), &n);

    return(info);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
