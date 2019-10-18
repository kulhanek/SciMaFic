#ifndef SciLapackH
#define SciLapackH
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
#include <FortranMatrix.hpp>
#include <Vector.hpp>

//------------------------------------------------------------------------------

class SCIMAFIC_PACKAGE CSciLapack {
public:
    ///  computes all eigenvalues and, optionally, eigenvectors of a real symmetric matrix A
    //  eigenvectors are stored columnwise
    static int syev(char jobz,char uplo,CFortranMatrix& a,CVector& w,CVector& work);

    /// computes all eigenvalues and, optionally, eigenvectors of a real symmetric matrix A
    //  eigenvectors are stored columnwise
    static int syev(char jobz,char uplo,CFortranMatrix& a,CVector& w);

    /// solve system of linear equation by LU
    static int solvle(CFortranMatrix& a,CVector& rhs);

    /// solve least square problem - SVD
    static int gelsd(CFortranMatrix& a,CVector& rhs,double rcond,int& rank);

    /// solve least square problem
    static int gels(CFortranMatrix& a,CVector& rhs);

    /// inverse matrix by dgetrf and dgetri (via LU)
    /// logdet is logarithm of determinat of original matrix
    static int invLU(CFortranMatrix& a,double& logdet);

    /// inverse matrix by potrf and potri (via Cholesky factorization)
    /// logdet is logarithm of determinat of original matrix
    static int invLL(CFortranMatrix& a,double& logdet);

    /// inverse matrix by SVD - simple driver
    /// logdet is logarithm of determinat of original matrix
    static int invSVD1(CFortranMatrix& a,double& logdet,double rcond,int& rank);

    /// inverse matrix by SVD - divide and qonquer
    /// logdet is logarithm of determinat of original matrix
    static int invSVD2(CFortranMatrix& a,double& logdet,double rcond,int& rank);
};

//------------------------------------------------------------------------------

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

// SVD - simple driver
extern "C" void dgesvd_(char* jobu,char* jobvt,int* m,int* n,double* a,int* lda,double* s,double* u,int* ldu,
                        double* vt,int* ldvt,double* work,int* lwork,int* info);

// SVD - divide and conquer
extern "C" void dgesdd_(char* jobz,int* m,int* n,double* a,int* lda,double* s,double* u,int* ldu,
                        double* vt,int* ldvt,double* work,int* lwork,int* iwork,int* info);

// Cholesky factorization
extern "C" void dpotrf_(char* uplo,int* n,double* a,int* lda,int* info);
extern "C" void dpotri_(char* uplo,int* n,double* a,int* lda,int* info);

//------------------------------------------------------------------------------

#endif
