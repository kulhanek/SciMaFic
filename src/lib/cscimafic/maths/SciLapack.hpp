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
#include <VerboseStr.hpp>

//------------------------------------------------------------------------------

class SCIMAFIC_PACKAGE CSciLapack {
public:
    /// print info about Blas/Lapack
    static void PrintExecInfo(CVerboseStr& vout);

    /// set number of threads for Lapack/Blas
    static void SetNumThreadsLocal(int nthrs);

    /// get number of threads available for Lapack/Blas
    static int GetNumThreads(void);

    ///  computes all eigenvalues and, optionally, eigenvectors of a real symmetric matrix A
    //  eigenvectors are stored columnwise
    static int syev(char jobz,char uplo,CFortranMatrix& a,CVector& w,CVector& work);

    /// computes all eigenvalues and, optionally, eigenvectors of a real symmetric matrix A
    //  eigenvectors are stored columnwise
    static int syev(char jobz,char uplo,CFortranMatrix& a,CVector& w);

    /// solve system of linear equation by LU
    static int solvle(CFortranMatrix& a,CVector& rhs);

    /// solve least square problem - SVD
    static int gelsd(CFortranMatrix& a,CVector& rhs,double rcond,int& rank,double& a_rcond);

    /// solve least square problem - QR
    static int gels(CFortranMatrix& a,CVector& rhs);

    /// inverse matrix by dgetrf and dgetri (via LU)
    /// logdet is logarithm of determinat of original matrix
    static int invLU(CFortranMatrix& a,double& logdet);

    /// inverse matrix by potrf and potri (via Cholesky factorization)
    /// logdet is logarithm of determinat of original matrix
    static int invLL(CFortranMatrix& a,double& logdet);

    /// inverse matrix by SVD - simple driver
    /// logdet is logarithm of determinat of original matrix
    static int invSVD1(CFortranMatrix& a,double& logdet,double rcond,int& rank,double& a_rcond);

    /// inverse matrix by SVD - divide and qonquer
    /// logdet is logarithm of determinat of original matrix
    static int invSVD2(CFortranMatrix& a,double& logdet,double rcond,int& rank,double& a_rcond);
};

//------------------------------------------------------------------------------

#endif
