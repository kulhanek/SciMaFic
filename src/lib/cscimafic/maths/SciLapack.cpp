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

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

// lapack entry points

extern "C" void dsyev_(char* jobz,char* uplo,int* n,double* a,int* lda,double* w,
                       double* work,int* lwork,int* info);

extern "C" void dgetrf_(int* m,int* n,double* a,int* lda,int* ipiv,int* info);
extern "C" void dgetrs_(char* trans,int* n,int* nrhs,double* a,int* lda,int* ipiv,double* b,int* ldb,int* info);
extern "C" void dgelsd_(int* m,int* n,int* nrhs,double* a,int* lda, double* b,int* ldb,
                        double* s, double* rcond, int* rank,
                        double* work, int* lwork, int* iwork, int* info);
extern "C" void dgels_(char* trans,int* m,int* n,int* nrhs,double* a,int* lda, double* b,int* ldb,
                        double* work, int* lwork, int* info);
extern "C" void dgetri_(int* m,double* a,int* lda,int* ipiv,double* work, int* lwork,int* info);

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

int CSciLapack::syev(char jobz,char uplo,CFortranMatrix& a,CVector& w,CVector& work)
{
    int info = 0;
    int nrows = a.GetNumberOfRows();
    int nwork = work.GetLength();

    dsyev_(&jobz,&uplo,&nrows,a.GetRawDataField(),&nrows,w.GetRawDataField(),
           work.GetRawDataField(),&nwork,&info);

    return(info);
}

//------------------------------------------------------------------------------

int CSciLapack::syev(char jobz,char uplo,CFortranMatrix& a,CVector& w)
{
    int     info = 0;
    int     nrows = a.GetNumberOfRows();
    int     nwork = -1;
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
    nwork = static_cast<int>(twork[0]) + 1;
    work.CreateVector(nwork);

    // run again
    dsyev_(&jobz,&uplo,&nrows,a.GetRawDataField(),&nrows,w.GetRawDataField(),
           work.GetRawDataField(),&nwork,&info);

    return(info);
}

//------------------------------------------------------------------------------

int CSciLapack::solvle(CFortranMatrix& a,CVector& rhs)
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

//------------------------------------------------------------------------------

int CSciLapack::gelsd(CFortranMatrix& a,CVector& rhs,double rcond,int& rank)
{
    int m = a.GetNumberOfRows();
    int n = a.GetNumberOfColumns();
    int nrhs = 1;
    int lda = m;
    int ldb = std::max(m,n);

    CVector s;
    int     ns = std::min(m,n);
    s.CreateVector(ns);

    int info = 0;

    // query work size
    int     lwork = -1;
    double  twork[1];

    // printf("lwork = %d\n",lwork);

    CSimpleVector<int>  iwork;
    int li = 3*std::min(m,n)*std::min(m,n) + 11*std::min(m,n);
    iwork.CreateVector(li);

    dgelsd_(&m,&n,&nrhs,a.GetRawDataField(),&lda,rhs.GetRawDataField(),&ldb,s.GetRawDataField(),
            &rcond,&rank,twork,&lwork,iwork.GetRawDataField(),&info);

    if( info != 0 ){
        CSmallString error;
        error << "unable to determine lwork, info = " << info;
        INVALID_ARGUMENT(error);
    }

    lwork = static_cast<int>(twork[0]) + 1;

    // printf("lwork = %d\n",lwork);

    CSimpleVector<double>  work;
    work.CreateVector(lwork);

    // run svd
    dgelsd_(&m,&n,&nrhs,a.GetRawDataField(),&lda,rhs.GetRawDataField(),&ldb,s.GetRawDataField(),
            &rcond,&rank,work.GetRawDataField(),&lwork,iwork.GetRawDataField(),&info);

    return(info);
}

//------------------------------------------------------------------------------

int CSciLapack::gels(CFortranMatrix& a,CVector& rhs)
{
    char trans = 'N';
    int m = a.GetNumberOfRows();
    int n = a.GetNumberOfColumns();
    int nrhs = 1;
    int lda = m;
    int ldb = std::max(m,n);
    int info = 0;

    // query work size
    int     lwork = -1;
    double  twork[1];

    dgels_(&trans,&m,&n,&nrhs,a.GetRawDataField(),&lda,rhs.GetRawDataField(),&ldb,
           twork,&lwork,&info);

    if( info != 0 ){
        CSmallString error;
        error << "unable to determine lwork, info = " << info;
        INVALID_ARGUMENT(error);
        return(info);
    }

    lwork = static_cast<int>(twork[0]) + 1;

    // printf("lwork = %d\n",lwork);

    CSimpleVector<double>  work;
    work.CreateVector(lwork);

    // run
    dgels_(&trans,&m,&n,&nrhs,a.GetRawDataField(),&lda,rhs.GetRawDataField(),&ldb,
            work.GetRawDataField(),&lwork,&info);

    return(info);
}

//------------------------------------------------------------------------------

int CSciLapack::inv1(CFortranMatrix& a,double& det)
{
    int info = 0;
    int ndimm = a.GetNumberOfRows();

    det = 0.0;

    if( ndimm == 0 ){
        ES_ERROR("no rows in a");
        return(-1);
    }
    if( a.GetNumberOfRows() != a.GetNumberOfColumns() ){
        ES_ERROR("matrix A must be a square matrix");
        return(-1);
    }

    int* indx = new int[ndimm];

    dgetrf_(&ndimm,&ndimm,a.GetRawDataField(),&ndimm,indx,&info);
    if( info != 0 ){
        delete[] indx;
        ES_ERROR("unable to do LU decomposition");
        return(info);
    }

    // calculate determinat of A
    det = 1.0;
    for(int i=0; i < ndimm; i++){
        det *= a[i][i];
        if( indx[i] != i + 1 ){ // indx - fortran indexes
            det *= -1.0;
        }
    }

    // query work size
    int     lwork = -1;
    double  twork[1];

    dgetri_(&ndimm,a.GetRawDataField(),&ndimm,indx,twork,&lwork,&info);

    if( info != 0 ){
        delete[] indx;
        CSmallString error;
        error << "unable to determine lwork, info = " << info;
        INVALID_ARGUMENT(error);
        return(info);
    }

    lwork = static_cast<int>(twork[0]) + 1;

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

int CSciLapack::inv2(CFortranMatrix& a,double& det,double rcond,int& rank)
{
    int info = 0;
    int ndimm = a.GetNumberOfRows();

    det = 0.0;

    if( ndimm == 0 ){
        ES_ERROR("no rows in a");
        return(-1);
    }
    if( a.GetNumberOfRows() != a.GetNumberOfColumns() ){
        ES_ERROR("matrix A must be a square matrix");
        return(-1);
    }

//    fac = 1d-5

//     m = size(jac,1)
//     n = size(jac,2)
//     k = min(m,n)

//     allocate(u(m,m),vt(n,n),sig(k),sig_plus(n,m),iwork(8*k),work(1),temp_mat(n,m), &
//              stat = alloc_stat)
//     if( alloc_stat .ne. 0) then
//        call ffdev_utils_exit(DEV_OUT,1,'Unable to allocate arrays I in ffdev_jacobian_inverse!')
//     end if

//     u(:,:)          = 0.0d0
//     vt(:,:)         = 0.0d0
//     sig(:)          = 0.0d0
//     sig_plus(:,:)   = 0.0d0
//     work(:)         = 0.0d0

//     ! work size query
//     lwork = -1
//     call dgesdd('A', m, n, jac(1,1), m, sig(1), u(1,1), m, vt(1,1), n, work(1), &
//                 lwork, iwork(1), info)

//     if( info .ne. 0) then
//        call ffdev_utils_exit(DEV_OUT,1,'Unable to get size of working array in ffdev_jacobian_inverse!')
//     end if

//     ! reinit working array
//     deallocate(work)
//     lwork = int(work(1))
//     allocate(work(lwork), stat = alloc_stat)

//     if( alloc_stat .ne. 0) then
//        call ffdev_utils_exit(DEV_OUT,1,'Unable to allocate arrays II in ffdev_jacobian_inverse!')
//     end if

//     ! do SVD
//     call dgesdd('A', m, n, jac(1,1), m, sig(1), u(1,1), m, vt(1,1), n, work(1), &
//                 lwork, iwork(1), info)

//     if( info .ne. 0) then
//        call ffdev_utils_exit(DEV_OUT,1,'SVD failed in ffdev_jacobian_inverse!')
//     end if

//     ! set singular values that are too small to zero
//     do i = 1, k
//        if( sig(i) > fac*maxval(sig) ) then
//           sig_plus(i,i) = 1.0d0/sig(i)
//        else
//           sig_plus(i,i) = 0.0d0
//        end if
//     end do

//     ! build pseudoinverse: V*sig_plus*UT
//     CALL dgemm('N', 'T', n, m, m, 1.0d0, sig_plus, n, u, m, 0.0d0, temp_mat, n)
//     CALL dgemm('T', 'N', n, m, n, 1.0d0, vt, n, temp_mat, n, 0.0d0, ijac, n)

//     ! clean data
//     deallocate(u, vt, sig, iwork, work, sig_plus, temp_mat)

    return(info);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
