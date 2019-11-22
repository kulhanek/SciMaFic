#ifndef SciBlasH
#define SciBlasH
//==============================================================================
//    Copyright 2019 Petr Kulhanek
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

class SCIMAFIC_PACKAGE CSciBlas {
public:
    /// dot product
    /// ret = dot(a,b)
    static double dot(CVector& a,CVector& b);

    /// matrix vector multiplication
    /// y = alpha*A*x + beta*y
    static void gemv(double alpha,CFortranMatrix& a,CVector& x,double beta,CVector& y);

    /// matrix matrix multiplication
    /// C = alpha*A*B + beta*C;
    static void gemm(double alpha,CFortranMatrix& a,CFortranMatrix& b,double beta,CFortranMatrix& c);

    /// matrix matrix multiplication
    /// C = alpha*op(A)*op(B) + beta*C;
    static void gemm(double alpha,char transa, CFortranMatrix& a,char transb,CFortranMatrix& b,double beta,CFortranMatrix& c);
};

//------------------------------------------------------------------------------

#endif
