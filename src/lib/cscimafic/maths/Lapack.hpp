#ifndef LapackH
#define LapackH
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

class SCIMAFIC_PACKAGE CLapack {
public:
    ///  computes all eigenvalues and, optionally, eigenvectors of a real symmetric matrix A
    //  eigenvectors are stored columnwise
    static int syev(char jobz,char uplo,CFortranMatrix& a,CVector& w,CVector& work);

    /// computes all eigenvalues and, optionally, eigenvectors of a real symmetric matrix A
    //  eigenvectors are stored columnwise
    static int syev(char jobz,char uplo,CFortranMatrix& a,CVector& w);

    /// solve system of linear equation by LU
    static int solvle(CFortranMatrix& a,CVector& rhs);

    /// solve least square problem
    static int gelsd(CFortranMatrix& a,CVector& rhs,double rcond,int& rank);

    /// solve least square problem
    static int gels(CFortranMatrix& a,CVector& rhs);
};

//------------------------------------------------------------------------------

#endif
