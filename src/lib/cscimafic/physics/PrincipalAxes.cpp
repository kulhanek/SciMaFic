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

#include <PrincipalAxes.hpp>
#include <PeriodicTable.hpp>
#include <Lapack.hpp>

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

CPrincipalAxes::CPrincipalAxes(void)
{
    TensorOfInertia.CreateMatrix(3,3);
    Moments.CreateVector(3);
    TensorOfInertia.SetZero();
    Moments.SetZero();
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

void CPrincipalAxes::SetZero(void)
{
    TensorOfInertia.SetZero();
    Moments.SetZero();
}

//------------------------------------------------------------------------------

void CPrincipalAxes::AddPoint(const CPoint& pos,double mass)
{
    TensorOfInertia[0][0] += mass*(pos.y*pos.y+pos.z*pos.z);
    TensorOfInertia[1][1] += mass*(pos.x*pos.x+pos.z*pos.z);
    TensorOfInertia[2][2] += mass*(pos.x*pos.x+pos.y*pos.y);

    TensorOfInertia[0][1] -= mass*pos.x*pos.y;
    TensorOfInertia[0][2] -= mass*pos.x*pos.z;
    TensorOfInertia[1][2] -= mass*pos.y*pos.z;

    TensorOfInertia[1][0] = TensorOfInertia[0][1];
    TensorOfInertia[2][0] = TensorOfInertia[0][2];
    TensorOfInertia[2][1] = TensorOfInertia[1][2];
}

//------------------------------------------------------------------------------

void CPrincipalAxes::AddXYZStructure(const CXYZStructure& str)
{
    for(int i=0; i < str.GetNumberOfAtoms(); i++) {
        CPoint pos = str.GetPosition(i);
        double mass = PeriodicTable.GetMass(PeriodicTable.SearchZBySymbol(str.GetSymbol(i)));
        AddPoint(pos,mass);
    }
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

bool CPrincipalAxes::CalcPrincipalAxes(void)
{
    bool result = CLapack::syev('V','U',TensorOfInertia,Moments) == 0;
    if( result == true ){
        // make axes RHS (right hand system)
        CPoint cp = CrossDot(GetBAxis(),GetCAxis());
        double an = Angle(GetAAxis(),cp);
        if( an > M_PI/2.0 ){
            // swap axes
            TensorOfInertia[0][0] = -TensorOfInertia[0][0];
            TensorOfInertia[1][0] = -TensorOfInertia[1][0];
            TensorOfInertia[2][0] = -TensorOfInertia[2][0];
        }
    }
    return(result);
}

//------------------------------------------------------------------------------

double CPrincipalAxes::GetAMoment(void)
{
    return(Moments[0]);
}

//------------------------------------------------------------------------------

const CPoint CPrincipalAxes::GetAAxis(void)
{
    CPoint axis;
    axis.x = TensorOfInertia[0][0];
    axis.y = TensorOfInertia[1][0];
    axis.z = TensorOfInertia[2][0];
    return(axis);
}

//------------------------------------------------------------------------------

double CPrincipalAxes::GetBMoment(void)
{
    return(Moments[1]);
}

//------------------------------------------------------------------------------

const CPoint CPrincipalAxes::GetBAxis(void)
{
    CPoint axis;
    axis.x = TensorOfInertia[0][1];
    axis.y = TensorOfInertia[1][1];
    axis.z = TensorOfInertia[2][1];
    return(axis);
}

//------------------------------------------------------------------------------

double CPrincipalAxes::GetCMoment(void)
{
    return(Moments[2]);
}

//------------------------------------------------------------------------------

const CPoint CPrincipalAxes::GetCAxis(void)
{
    CPoint axis;
    axis.x = TensorOfInertia[0][2];
    axis.y = TensorOfInertia[1][2];
    axis.z = TensorOfInertia[2][2];
    return(axis);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
