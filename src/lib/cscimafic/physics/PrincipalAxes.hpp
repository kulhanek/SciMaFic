#ifndef PrincipalAxesH
#define PrincipalAxesH
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
#include <FortranMatrix.hpp>
#include <Vector.hpp>
#include <Point.hpp>
#include <XYZStructure.hpp>

// -----------------------------------------------------------------------------

// IMPORTANT: Center of mass has to be in origin !!!!!

class SCIMAFIC_PACKAGE CPrincipalAxes {
public:
    CPrincipalAxes(void);

// set methods ----------------------------------------------------------------
    void SetZero(void);
    void AddPoint(const CPoint& pos,double mass);
    void AddXYZStructure(const CXYZStructure& str);

// execute --------------------------------------------------------------------
    bool CalcPrincipalAxes(void);

// get methods ----------------------------------------------------------------
    double           GetAMoment(void);
    const CPoint     GetAAxis(void);
    double           GetBMoment(void);
    const CPoint     GetBAxis(void);
    double           GetCMoment(void);
    const CPoint     GetCAxis(void);

// section of private data ----------------------------------------------------
private:
    CFortranMatrix  TensorOfInertia;
    CVector         Moments;
};

// -----------------------------------------------------------------------------

#endif
