#ifndef SimpleSquareMatrixH
#define SimpleSquareMatrixH
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

#include <math.h>
#include "SciMaFicMainHeader.hpp"

class CXMLElement;

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

template<class type, int size>
class CSimpleSquareMatrix {
public:
    CSimpleSquareMatrix(void);
    CSimpleSquareMatrix(const CSimpleSquareMatrix<type,size>& copy);

// information method --------------------------------------------------------
    int     GetSize(void);
    type*   GetRawDataField(void);

// operators -----------------------------------------------------------------
    void     operator = (const CSimpleSquareMatrix<type,size>& right);
    const CSimpleSquareMatrix<type,size>
    operator + (const CSimpleSquareMatrix<type,size>& right) const;
    void     operator += (const CSimpleSquareMatrix<type,size>& right);
    const CSimpleSquareMatrix<type,size>
    operator - (const CSimpleSquareMatrix<type,size>& right) const;
    void     operator -= (const CSimpleSquareMatrix<type,size>& right);
    const CSimpleSquareMatrix<type,size>
    operator * (const CSimpleSquareMatrix<type,size>& right) const;
    const CSimpleSquareMatrix<type,size>
    operator * (double right) const;
    void     operator *= (const CSimpleSquareMatrix<type,size>& right);

// set method ----------------------------------------------------------------
    void SetZero(void);
    void SetUnit(void);
    void AddTo(CSimpleSquareMatrix<type,size>& dest) const;
    void AddWith(const CSimpleSquareMatrix<type,size>& source);
    void SubFrom(CSimpleSquareMatrix<type,size>& dest) const;
    void SubWith(const CSimpleSquareMatrix<type,size>& source);
    // dest = this * dest
    void MultFromLeftTo(CSimpleSquareMatrix<type,size>& dest) const;
    // dest = dest * this
    void MultFromRightTo(CSimpleSquareMatrix<type,size>& dest) const;
    // this = source * this
    void MultFromLeftWith(const CSimpleSquareMatrix<type,size>& source);
    // this = this * source
    void MultFromRightWith(const CSimpleSquareMatrix<type,size>& source);
    void CopyTo(CSimpleSquareMatrix<type,size>& dest) const;
    void CopyFrom(const CSimpleSquareMatrix<type,size>& source);

// executive methods ---------------------------------------------------------
    bool Invert(void);
    bool LinearEquations(int rowmut[],type vect[]);
    bool LUFactorization(int rowmut[]);
    void Transpose(void);
    void SquareRoot(int maxiter=50);

// eigenproblems -------------------------------------------------------------
    // eigenvectors are stored columnwise
    bool EigenProblem(type eigenvalues[],int maxiter=50);

// section of public data ----------------------------------------------------
public:
    type Field[size][size];

// section of private data ---------------------------------------------------

// helper methods ------------------------------------------------------------
    void Swap(type& a, type& b);
};

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

template<class type, int size>
CSimpleSquareMatrix<type,size>::CSimpleSquareMatrix(void)
{
    SetZero();
}

//------------------------------------------------------------------------------

template<class type, int size>
CSimpleSquareMatrix<type,size>::CSimpleSquareMatrix(const CSimpleSquareMatrix<type,size>& copy)
{
    CopyFrom(copy);
}

//------------------------------------------------------------------------------

template<class type, int size>
int CSimpleSquareMatrix<type,size>::GetSize(void)
{
    return(size);
}

//------------------------------------------------------------------------------

template<class type, int size>
type*   CSimpleSquareMatrix<type,size>::GetRawDataField(void)
{
    return(&Field[0][0]);
}

//------------------------------------------------------------------------------

template<class type, int size>
void CSimpleSquareMatrix<type,size>::SetZero(void)
{
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            Field[i][j] = 0.0;
        }
    }
}

//------------------------------------------------------------------------------

template<class type, int size>
void CSimpleSquareMatrix<type,size>::SetUnit(void)
{
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            if( i == j ) Field[i][j] = 1.0;
            else Field[i][j] = 0.0;
        }
    }
}

//------------------------------------------------------------------------------

template<class type, int size>
void CSimpleSquareMatrix<type,size>::operator = (const CSimpleSquareMatrix<type,size>& right)
{
    CopyFrom(right);
}

//------------------------------------------------------------------------------

template<class type, int size>
const CSimpleSquareMatrix<type,size> CSimpleSquareMatrix<type,size>::operator + (const CSimpleSquareMatrix<type,size>& right) const
{
    CSimpleSquareMatrix<type,size> helper;

    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            helper.Field[i][j] = Field[i][j] + right.Field[i][j];
        }
    }

    return(helper);
}

//------------------------------------------------------------------------------

template<class type, int size>
void CSimpleSquareMatrix<type,size>::operator += (const CSimpleSquareMatrix<type,size>& right)
{
    AddWith(right);
}

//------------------------------------------------------------------------------

template<class type, int size>
const CSimpleSquareMatrix<type,size> CSimpleSquareMatrix<type,size>::operator - (const CSimpleSquareMatrix<type,size>& right) const
{
    CSimpleSquareMatrix<type,size> helper;

    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            helper[i][j] = Field[i][j] - right.Field[i][j];
        }
    }

    return(helper);
}

//------------------------------------------------------------------------------

template<class type, int size>
void CSimpleSquareMatrix<type,size>::operator -= (const CSimpleSquareMatrix<type,size>& right)
{
    SubWith(right);
}

//------------------------------------------------------------------------------

template<class type, int size>
const CSimpleSquareMatrix<type,size> CSimpleSquareMatrix<type,size>::operator * (const CSimpleSquareMatrix<type,size>& right) const
{
    CSimpleSquareMatrix<type,size> helper;

    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            for(int k=0; k<size; k++) helper.Field[i][j] += Field[i][k]*right.Field[k][j];
        }
    }

    return(helper);
}

//------------------------------------------------------------------------------

template<class type, int size>
const CSimpleSquareMatrix<type,size> CSimpleSquareMatrix<type,size>::operator * (double right) const
{
    CSimpleSquareMatrix<type,size> helper;

    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            helper.Field[i][j] = Field[i][j]*right;
        }
    }

    return(helper);
}

//------------------------------------------------------------------------------

template<class type, int size>
void CSimpleSquareMatrix<type,size>::operator *= (const CSimpleSquareMatrix<type,size>& right)
{
    MultFromRightWith(right);
}

//---------------------------------------------------------------------------

template<class type, int size>
void CSimpleSquareMatrix<type,size>::AddTo(CSimpleSquareMatrix<type,size>& dest) const
{
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            dest.Field[i][j] += Field[i][j];
        }
    }
}

//---------------------------------------------------------------------------

template<class type, int size>
void CSimpleSquareMatrix<type,size>::AddWith(const CSimpleSquareMatrix<type,size>& source)
{
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            Field[i][j] += source.Field[i][j];
        }
    }
}

//---------------------------------------------------------------------------

template<class type, int size>
void CSimpleSquareMatrix<type,size>::SubFrom(CSimpleSquareMatrix<type,size>& dest) const
{
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            dest.Field[i][j] -= Field[i][j];
        }
    }
}

//---------------------------------------------------------------------------

template<class type, int size>
void CSimpleSquareMatrix<type,size>::SubWith(const CSimpleSquareMatrix<type,size>& source)
{
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            Field[i][j] -= source.Field[i][j];
        }
    }
}

//---------------------------------------------------------------------------

// dest = this * dest

template<class type, int size>
void CSimpleSquareMatrix<type,size>::MultFromLeftTo(CSimpleSquareMatrix<type,size>& dest) const
{
    type     pomvect[size];

    for(int j=0; j<size; j++) {
        for(int i=0; i<size; i++) pomvect[i]=dest.Field[i][j];    // backup column
        for(int i=0; i<size; i++) {
            Field[i][j] = 0;
            for(int k=0; k<size; k++) dest.Field[i][j] += Field[i][k]*pomvect[k];
        }
    }
}

//---------------------------------------------------------------------------

// dest = dest * this

template<class type, int size>
void CSimpleSquareMatrix<type,size>::MultFromRightTo(CSimpleSquareMatrix<type,size>& dest) const
{
    type     pomvect[size];

    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) pomvect[j]=dest.Field[i][j];    // backup row
        for(int j=0; j<size; j++) {
            Field[i][j] = 0;
            for(int k=0; k<size; k++) dest.Field[i][j] += pomvect[k]*Field[k][j];
        }
    }
}

//---------------------------------------------------------------------------

// this = this * source

template<class type, int size>
void CSimpleSquareMatrix<type,size>::MultFromRightWith(const CSimpleSquareMatrix<type,size>& source)
{
    type     pomvect[size];

    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) pomvect[j]=Field[i][j];    // backup row
        for(int j=0; j<size; j++) {
            Field[i][j] = 0;
            for(int k=0; k<size; k++) Field[i][j] += pomvect[k]*source.Field[k][j];
        }
    }
}

//---------------------------------------------------------------------------

// this = source * this

template<class type, int size>
void CSimpleSquareMatrix<type,size>::MultFromLeftWith(const CSimpleSquareMatrix<type,size>& source)
{
    type     pomvect[size];

    for(int j=0; j<size; j++) {
        for(int i=0; i<size; i++) pomvect[i]=Field[i][j];    // backup column
        for(int i=0; i<size; i++) {
            Field[i][j] = 0;
            for(int k=0; k<size; k++) Field[i][j] += source.Field[i][k]*pomvect[k];
        }
    }
}

//---------------------------------------------------------------------------

template<class type, int size>
void CSimpleSquareMatrix<type,size>::CopyTo(CSimpleSquareMatrix<type,size>& dest) const
{
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            dest.Field[i][j] = Field[i][j];
        }
    }
}

//---------------------------------------------------------------------------

template<class type, int size>
void CSimpleSquareMatrix<type,size>::CopyFrom(const CSimpleSquareMatrix<type,size>& source)
{
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            Field[i][j] = source.Field[i][j];
        }
    }
}

//---------------------------------------------------------------------------

template<class type, int size>
bool CSimpleSquareMatrix<type,size>::Invert(void)
{
    CSimpleSquareMatrix<type,size> LUcopy;
    int                            rowmut[size];
    type                            helper[size];

// make copy of matrix
    CopyTo(LUcopy);

// make LU factorization of matrix
    if( LUcopy.LUFactorization(rowmut) == false ) return(false);

    for(int k=0; k<size; k++) {
        // process each column
        for(int i=0; i<size; i++) {
            if( i != k ) helper[i] = 0;
            else helper[i] = 1;
        }

        if( LUcopy.LinearEquations(rowmut,helper) == false )return(false);

        for(int i=0; i<size; i++) {
            Field[i][k] = helper[i];
        }
    }

    return(true);
}

//---------------------------------------------------------------------------

template<class type, int size>
bool CSimpleSquareMatrix<type,size>::LinearEquations(int rowmut[],type vect[])
{
    type d;

    for(int i=0; i<size; i++) {
        Swap(vect[i],vect[rowmut[i]]);
        for(int j=i+1; j<size; j++) {
            vect[j] -= Field[j][i]*vect[i];
        }
    }

    for(int i=size-1; i>=0; i--) {
        d = vect[i];
        for(int j=i+1; j<size; j++) {
            d -= Field[i][j]*vect[j];
        }
        if( Field[i][i] == 0.0 ) return(false);
        vect[i] = d/Field[i][i];
    }

    return(true);
}

//---------------------------------------------------------------------------

template<class type, int size>
bool CSimpleSquareMatrix<type,size>::LUFactorization(int rowmut[])
{
    type        dold, d;
    type        helper[size];

    dold   = Field[0][0];
    rowmut[0] = 0;
    helper[0] = dold;
    for(int i=1; i<size; i++) {
        d = Field[i][0];
        if( fabs(d) > fabs(dold) ) {
            rowmut[0] = i;
            dold = d;
        }
        helper[i] = d;
    }

    Field[0][0] = helper[rowmut[0]];
    helper[rowmut[0]] = helper[0];

    if( dold == 0.0 ) return(false);

    for(int i=1; i<size; i++) {
        Field[i][0] = helper[i]/dold;
    }

    for(int r=1; r<size; r++) {
        for(int k=0; k<size; k++) {
            helper[k] = Field[k][r];
        }

        for(int j=0; j<r; j++) {
            Field[j][r] = helper[rowmut[j]];
            helper[rowmut[j]] = helper[j];
            for(int i=j+1; i<size; i++) {
                helper[i] -= Field[i][j]*Field[j][r];
            }
        }

        dold = helper[r];
        rowmut[r] = r;
        for(int i = r+1; i<size; i++) {
            if( fabs(helper[i]) > fabs(dold)) {
                rowmut[r] = i;
                dold = helper[i];
            }
        }
        helper[rowmut[r]] = helper[r];
        Field[r][r] = dold;

        if( dold == 0.0 ) return(false);

        for(int i=r+1; i<size; i++) {
            Field[i][r] = helper[i]/dold;
        }
    }

    return(true);
}

//---------------------------------------------------------------------------

template<class type, int size>
void CSimpleSquareMatrix<type,size>::Transpose(void)
{
    for(int i=1; i<size; i++) {
        for(int j=i; j<size; j++) {
            Swap(Field[i][j],Field[j][i]);
        }
    }
}

//---------------------------------------------------------------------------

template<class type, int size>
void CSimpleSquareMatrix<type,size>::SquareRoot(int maxiter)
{
    CSimpleSquareMatrix<type,size>    Y;
    CSimpleSquareMatrix<type,size>    Z;
    CSimpleSquareMatrix<type,size>    Y1;
    CSimpleSquareMatrix<type,size>    Z1;
    CSimpleSquareMatrix<type,size>    Yk;
    CSimpleSquareMatrix<type,size>    Zk;

    CopyTo(Y);
    Z.SetUnit();

    // http://en.wikipedia.org/wiki/Square_root_of_a_matrix

    for(int i=0; i < maxiter; i++) {
        Y1 = Y;
        Z1 = Z;
        Y1.Invert();
        Z1.Invert();
        Yk = (Y + Z1)*0.5;
        Zk = (Y1 + Z)*0.5;
        Y = Yk;
        Z = Zk;
    }

    CopyFrom(Y);
}

//---------------------------------------------------------------------------

template<class type, int size>
void CSimpleSquareMatrix<type,size>::Swap(type& a, type& b)
{
    type swap;
    swap = a;
    a = b;
    b = swap;
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

/* this method is redesigned method Jacobi(unsigned int n, double *a, double *d, double *v)
   from matrix3x3.cpp of OpenBabel project

// **********************************************************************
matrix3x3.cpp - Rotation matrix.

Copyright (C) 1998-2001 by OpenEye Scientific Software, Inc.
Some portions Copyright (c) 2001-2003 by Geoffrey R. Hutchison

This file is part of the Open Babel project.
For more information, see <http://openbabel.sourceforge.net/>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
// ***********************************************************************

*/

template<class type, int size>
bool CSimpleSquareMatrix<type,size>::EigenProblem(type eigenvalues[],int maxiter)
{
    CSimpleSquareMatrix<type,size>    helper;
    type                             onorm, dnorm;
    type                             b, dma, q, t, c, s;
    type                              atemp, vtemp, dtemp;

// Set v to the identity matrix, set the vector d to contain the
// diagonal elements of the matrix a
    helper.SetUnit();

    for(int i = 0; i < size; i++) {
        eigenvalues[i] = Field[i][i];
    }

    for(int l = 1; l <= maxiter; l++) {
        // Set dnorm to be the maximum norm of the diagonal elements, set
        // onorm to the maximum norm of the off-diagonal elements
        dnorm = 0.0;
        onorm = 0.0;
        for(int j = 0; j < size; j++) {
            dnorm += (type)fabs(eigenvalues[j]);
            for(int i = 0; i < j; i++) onorm += (type)fabs(Field[i][j]);
        }

        // Normal end point of this algorithm.
        if((onorm/dnorm) <= 1.0e-12) goto Exit_now;

        for(int j = 1; j < size; j++) {
            for(int i = 0; i <= j - 1; i++) {
                b = Field[i][j];
                if(fabs(b) > 0.0) {
                    dma = eigenvalues[j] - eigenvalues[i];
                    if((fabs(dma) + fabs(b)) <=  fabs(dma)) {
                        t = b / dma;
                    } else {
                        q = 0.5 * dma / b;
                        t = 1.0/((type)fabs(q) + (type)sqrt(1.0+q*q));
                        if (q < 0.0) t = -t;
                    }

                    c = 1.0/(type)sqrt(t*t + 1.0);
                    s = t * c;
                    Field[i][j] = 0.0;

                    for(int k = 0; k <= i-1; k++) {
                        atemp = c * Field[k][i] - s * Field[k][j];
                        Field[k][j] = s * Field[k][i] + c * Field[k][j];
                        Field[k][i] = atemp;
                    }

                    for(int k = i+1; k <= j-1; k++) {
                        atemp = c * Field[i][k] - s * Field[k][j];
                        Field[k][j] = s * Field[i][k] + c * Field[k][j];
                        Field[i][k] = atemp;
                    }

                    for(int k = j+1; k < size; k++) {
                        atemp = c * Field[i][k] - s * Field[j][k];
                        Field[j][k] = s * Field[i][k] + c * Field[j][k];
                        Field[i][k] = atemp;
                    }

                    for(int k = 0; k < size; k++) {
                        vtemp = c * helper.Field[k][i] - s * helper.Field[k][j];
                        helper.Field[k][j] = s * helper.Field[k][i] + c * helper.Field[k][j];
                        helper.Field[k][i] = vtemp;
                    }

                    dtemp = c*c*eigenvalues[i] + s*s*eigenvalues[j] - 2.0*c*s*b;
                    eigenvalues[j] = s*s*eigenvalues[i] + c*c*eigenvalues[j] +  2.0*c*s*b;
                    eigenvalues[i] = dtemp;
                }
            }
        }
    }

Exit_now:

// Now sort the eigenvalues (and the eigenvectors) so that the
// smallest eigenvalues come first.

    for(int j = 0; j < size-1; j++) {
        int k = j;
        dtemp = eigenvalues[k];
        for(int i = j+1; i < size; i++) {
            if(eigenvalues[i] < dtemp) {
                k = i;
                dtemp = eigenvalues[k];
            }
        }

        if(k > j) {
            // swap eigenvalues
            eigenvalues[k] = eigenvalues[j];
            eigenvalues[j] = dtemp;
            // swap vectors
            for(int i = 0; i < size; i++) {
                dtemp = helper.Field[i][k];
                helper.Field[i][k] = helper.Field[i][j];
                helper.Field[i][j] = dtemp;
            }
        }
    }

// copy eigenvectors
    CopyFrom(helper);

    return(true);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

#endif
