#ifndef MatrixH
#define MatrixH
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

#include <SciMaFicMainHeader.hpp>
#include <Vector.hpp>

// -----------------------------------------------------------------------------

class CXMLElement;

// -----------------------------------------------------------------------------

/// matrix
class SCIMAFIC_PACKAGE CMatrix {
public:
    CMatrix(void);
    ~CMatrix(void);

// setup methods ---------------------------------------------------------------
    /// create matrix
    void CreateMatrix(long unsigned int rows,long unsigned int columns);

    /// free matrix
    void FreeMatrix(void);

// I/O methods -----------------------------------------------------------------
    /// load matrix data from XMLBinData
    void Load(CXMLBinData* p_el);

    /// load matrix data from XMLBinData
    void Save(CXMLBinData* p_el);

// information method ----------------------------------------------------------
    /// get number of rows
    long unsigned int GetNumberOfRows(void);

    /// get number of columns
    long unsigned int GetNumberOfColumns(void);

// operators -------------------------------------------------------------------
    void        operator = (const CMatrix& right);
    void        operator += (const CMatrix& right);
    void        operator -= (const CMatrix& right);
    void        operator *= (const CMatrix& right);
    CVector&    operator [] (const unsigned int index);

// set method ------------------------------------------------------------------
    /// set all elements to zero
    void SetZero(void);

    /// set to unit matrix
    void SetUnit(void);

    void AddTo(CMatrix& dest) const;
    void AddWith(const CMatrix& source);

    void SubFrom(CMatrix& dest) const;
    void SubWith(const CMatrix& source);

    // dest = this * dest
    void MultFromLeftTo(CMatrix& dest) const;
    // dest = dest * this
    void MultFromRightTo(CMatrix& dest) const;
    // this = source * this
    void MultFromLeftWith(const CMatrix& source);
    // this = this * source
    void MultFromRightWith(const CMatrix& source);

    void CopyTo(CMatrix& dest) const;
    void CopyFrom(const CMatrix& source);

// executive methods -----------------------------------------------------------
    bool Invert(void);
    bool EigenProblem(double eigenvalues[],int maxiter=50);
    bool LinearEquations(int rowmut[],double vect[]);
    bool LUFactorization(int rowmut[]);
    void Transpose(void);

// section of private data
private:
    unsigned int    Rows;       // number of rows
    unsigned int    Columns;    // number of columns
    CVector*        RowVectors; // matrix data

    void Swap(double& a, double& b);
};

// -----------------------------------------------------------------------------

#endif
