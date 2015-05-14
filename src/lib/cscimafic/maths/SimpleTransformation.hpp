#ifndef SimpleTransformationH
#define SimpleTransformationH
/*! \file SimpleTransformation.hpp */
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
#include <SimplePoint.hpp>
#include <SimpleSquareMatrix.hpp>
#include <SimpleVector.hpp>
#include <XMLElement.hpp>
#include <math.h>

// -----------------------------------------------------------------------------

template<class type>
class SCIMAFIC_PACKAGE CSimpleTransformation : public CSimpleSquareMatrix<type,4> {
public:
    CSimpleTransformation(void);

// movement methods ------------------------------------------------------------
    /// translate about (dx,dy,dz) vector
    void Translate(type dx,type dy,type dz);

    /// translate about dmov vector
    void Translate(const CSimplePoint<type> &dmov);

// scale methods ---------------------------------------------------------------
    /// scale by (sx,sy,sz) vector
    void Scale(type sx,type sy,type sz);

    /// scale by scale vector
    void Scale(const CSimplePoint<type> &scale);

// rotation methods ------------------------------------------------------------
    /// rotate by alpha around (x,y,z) vector
    void Rotate(type alpha,type x,type y,type z);

    /// rotate by alpha around dir vector
    void Rotate(type alpha,const CSimplePoint<type> &dir);

    /// rotate by alpha, beta, gamma around X, Y, and Z axis
    void Rotate(type alpha,type beta,type gama);

    /// rotate by drot around X, Y, and Z axis
    void Rotate(const CSimplePoint<type> &drot);

    /// chande direction from odir to ndir vector
    void ChangeDirection(const CSimplePoint<type> &odir,
                                      const CSimplePoint<type> &ndir);

    /// quaternion fit
    void QuaternionFit(const CSimpleVector< CSimplePoint<type> >& ref,
                                    const CSimpleVector< CSimplePoint<type> >& sys);

    /// quaternion fit - weighted
    void QuaternionFitMW(const CSimpleVector< CSimplePoint<type> >& ref,
                                      const CSimpleVector< CSimplePoint<type> >& sys,
                                      const CSimpleVector<type>& weights);

// operators -------------------------------------------------------------------
    /// assign operator
    void operator=(const CSimpleTransformation<type>& trans);

    /// multiply from right operator
    void operator*=(const CSimpleTransformation<type>& trans);

    /// multiply operator
    CSimpleTransformation<type> operator*(const CSimpleTransformation<type>& trans) const;

// input/output methods --------------------------------------------------------
    /// load matrix
    void Load(CXMLElement* p_ele);

    /// save matrix
    void Save(CXMLElement* p_ele);

// executive methods -----------------------------------------------------------
    const CSimplePoint<type>     GetTransform(const CSimplePoint<type> &pos) const;
    void                         Apply(CSimplePoint<type> &pos) const;
};

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

template<class type>
CSimpleTransformation<type>::CSimpleTransformation(void)
{
    CSimpleSquareMatrix<type,4>::SetUnit();
}

//---------------------------------------------------------------------------

template<class type>
void CSimpleTransformation<type>::Translate(type dx,type dy,type dz)
{
    CSimpleSquareMatrix<type,4> helper;

    helper.SetUnit();
    helper.Field[3][0] = dx;
    helper.Field[3][1] = dy;
    helper.Field[3][2] = dz;

    CSimpleSquareMatrix<type,4>::MultFromRightWith(helper);
}

//---------------------------------------------------------------------------

template<class type>
void CSimpleTransformation<type>::Translate(const CSimplePoint<type> &dmov)
{
    CSimpleSquareMatrix<type,4> helper;

    helper.SetUnit();
    helper.Field[3][0] = dmov.x;
    helper.Field[3][1] = dmov.y;
    helper.Field[3][2] = dmov.z;

    CSimpleSquareMatrix<type,4>::MultFromRightWith(helper);
}

//---------------------------------------------------------------------------

template<class type>
void CSimpleTransformation<type>::Scale(type sx,type sy,type sz)
{
    CSimpleSquareMatrix<type,4> helper;

    helper.SetUnit();
    helper.Field[0][0] = sx;
    helper.Field[1][1] = sy;
    helper.Field[2][2] = sz;

    CSimpleSquareMatrix<type,4>::MultFromRightWith(helper);
}

//---------------------------------------------------------------------------

template<class type>
void CSimpleTransformation<type>::Scale(const CSimplePoint<type> &scale)
{
    CSimpleSquareMatrix<type,4> helper;

    helper.SetUnit();
    helper.Field[0][0] = scale.x;
    helper.Field[1][1] = scale.y;
    helper.Field[2][2] = scale.z;

    CSimpleSquareMatrix<type,4>::MultFromRightWith(helper);
}

//---------------------------------------------------------------------------

template<class type>
void CSimpleTransformation<type>::Rotate(type alpha,type x,type y,type z)
{
    CSimpleSquareMatrix<type,4> helper;

    double d  = sqrt(x*x+y*y+z*z);
    double pd = sqrt(x*x+y*y);

    helper.SetUnit();

    if( pd > 0 ) {                 // rotate around z
        helper.Field[0][0] = x/pd;
        helper.Field[1][1] = helper.Field[0][0];
        helper.Field[0][1] = -y/pd;
        helper.Field[1][0] = -helper.Field[0][1];

        CSimpleSquareMatrix<type,4>::MultFromRightWith(helper);
        helper.SetUnit();
    }

    if( d > 0 ) {                 // rotate around y
        helper.Field[0][0] = z/d;
        helper.Field[2][2] = helper.Field[0][0];
        helper.Field[0][2] = pd/d;
        helper.Field[2][0] = -helper.Field[0][2];

        CSimpleSquareMatrix<type,4>::MultFromRightWith(helper);
        helper.SetUnit();
    }

// rotate around z about angle aplha

    helper.Field[0][0] = cos(alpha);
    helper.Field[1][1] = helper.Field[0][0];
    helper.Field[0][1] = sin(alpha);
    helper.Field[1][0] = -helper.Field[0][1];

    CSimpleSquareMatrix<type,4>::MultFromRightWith(helper);
    helper.SetUnit();

// backward transformation

    if( d > 0 ) {                 // rotate around y
        helper.Field[0][0] = z/d;
        helper.Field[2][2] = helper.Field[0][0];
        helper.Field[0][2] = -pd/d;
        helper.Field[2][0] = -helper.Field[0][2];

        CSimpleSquareMatrix<type,4>::MultFromRightWith(helper);
        helper.SetUnit();
    }

    if( pd > 0 ) {                 // rotate around z
        helper.Field[0][0] = x/pd;
        helper.Field[1][1] = helper.Field[0][0];
        helper.Field[0][1] = y/pd;
        helper.Field[1][0] = -helper.Field[0][1];

        CSimpleSquareMatrix<type,4>::MultFromRightWith(helper);
    }
}

//---------------------------------------------------------------------------

template<class type>
void CSimpleTransformation<type>::Rotate(type alpha,const CSimplePoint<type> &dir)
{
    Rotate(alpha,dir.x,dir.y,dir.z);
}

//---------------------------------------------------------------------------

template<class type>
void CSimpleTransformation<type>::Rotate(const CSimplePoint<type> &drot)
{
    Rotate(drot.x,drot.y,drot.z);
}

//---------------------------------------------------------------------------

template<class type>
void CSimpleTransformation<type>::Rotate(type alpha,type beta,type gama)
{
    CSimpleSquareMatrix<type,4> helper;

    helper.SetUnit();

// rotate around x
    helper.Field[1][1] = cos(alpha);
    helper.Field[2][2] = helper.Field[1][1];
    helper.Field[1][2] = sin(alpha);
    helper.Field[2][1] = -helper.Field[1][2];

    CSimpleSquareMatrix<type,4>::MultFromRightWith(helper);

    helper.SetUnit();

// rotate around y
    helper.Field[0][0] = cos(beta);
    helper.Field[2][2] = helper.Field[0][0];
    helper.Field[0][2] = sin(beta);
    helper.Field[2][0] = -helper.Field[0][2];

    CSimpleSquareMatrix<type,4>::MultFromRightWith(helper);

    helper.SetUnit();

// rotate around z
    helper.Field[0][0] = cos(gama);
    helper.Field[1][1] = helper.Field[0][0];
    helper.Field[0][1] = sin(gama);
    helper.Field[1][0] = -helper.Field[0][1];

    CSimpleSquareMatrix<type,4>::MultFromRightWith(helper);
}

//---------------------------------------------------------------------------

template<class type>
void CSimpleTransformation<type>::ChangeDirection(
    const CSimplePoint<type> &odir,
    const CSimplePoint<type> &ndir)
{
    CSimpleSquareMatrix<type,4> helper;
    double d  = sqrt(odir.x*odir.x+odir.y*odir.y+odir.z*odir.z);
    double pd = sqrt(odir.x*odir.x+odir.y*odir.y);
    double nd  = sqrt(ndir.x*ndir.x+ndir.y*ndir.y+ndir.z*ndir.z);
    double npd = sqrt(ndir.x*ndir.x+ndir.y*ndir.y);

    helper.SetUnit();

    if( pd > 0 ) {                 // rotate around z
        helper.Field[0][0] = odir.x/pd;
        helper.Field[1][1] = helper.Field[0][0];
        helper.Field[0][1] = -odir.y/pd;
        helper.Field[1][0] = -helper.Field[0][1];

        CSimpleSquareMatrix<type,4>::MultFromRightWith(helper);
        helper.SetUnit();
    }

    if( d > 0 ) {                 // rotate around  y
        helper.Field[0][0] = odir.z/d;
        helper.Field[2][2] = helper.Field[0][0];
        helper.Field[0][2] = pd/d;
        helper.Field[2][0] = -helper.Field[0][2];

        CSimpleSquareMatrix<type,4>::MultFromRightWith(helper);
        helper.SetUnit();
    }

    if( nd > 0 ) {                 // rotate around y
        helper.Field[0][0] = ndir.z/nd;
        helper.Field[2][2] = helper.Field[0][0];
        helper.Field[0][2] = -npd/nd;
        helper.Field[2][0] = -helper.Field[0][2];

        CSimpleSquareMatrix<type,4>::MultFromRightWith(helper);
        helper.SetUnit();
    }

    if( npd > 0 ) {                 // rotate around z
        helper.Field[0][0] = ndir.x/npd;
        helper.Field[1][1] = helper.Field[0][0];
        helper.Field[0][1] = ndir.y/npd;
        helper.Field[1][0] = -helper.Field[0][1];

        CSimpleSquareMatrix<type,4>::MultFromRightWith(helper);
        helper.SetUnit();
    }

}

//---------------------------------------------------------------------------

template<class type>
void CSimpleTransformation<type>::operator=(const CSimpleTransformation<type> &trans)
{
    CSimpleSquareMatrix<type,4>::CopyFrom(trans);
}

//---------------------------------------------------------------------------

template<class type>
void CSimpleTransformation<type>::operator*=(const CSimpleTransformation<type> &trans)
{
    CSimpleSquareMatrix<type,4>::MultFromRightWith(trans);
}

//---------------------------------------------------------------------------

template<class type>
CSimpleTransformation<type> CSimpleTransformation<type>::operator*(const CSimpleTransformation<type>& trans) const
{
    CSimpleTransformation<type> t;
    CSimpleSquareMatrix<type,4>::CopyTo(t);
    t.MultFromRightWith(trans);
    return(t);
}

//---------------------------------------------------------------------------

template<class type>
void CSimpleTransformation<type>::Apply(CSimplePoint<type> &pos) const
{
    type helper[4];

    helper[0] = pos.x;
    helper[1] = pos.y;
    helper[2] = pos.z;
    helper[3] = 1;

    pos.x = 0;
    pos.y = 0;
    pos.z = 0;

    for(int k=0; k<4; k++) {
        pos.x += helper[k]*CSimpleSquareMatrix<type,4>::Field[k][0];
        pos.y += helper[k]*CSimpleSquareMatrix<type,4>::Field[k][1];
        pos.z += helper[k]*CSimpleSquareMatrix<type,4>::Field[k][2];
    }
}

//---------------------------------------------------------------------------

template<class type>
const CSimplePoint<type> CSimpleTransformation<type>::GetTransform(const CSimplePoint<type> &pos) const
{
    CSimplePoint<type>  work;

    work.x=CSimpleSquareMatrix<type,4>::Field[3][0];
    work.y=CSimpleSquareMatrix<type,4>::Field[3][1];
    work.z=CSimpleSquareMatrix<type,4>::Field[3][2];

    work.x +=     pos.x*CSimpleSquareMatrix<type,4>::Field[0][0] +
                  pos.y*CSimpleSquareMatrix<type,4>::Field[1][0] +
                  pos.z*CSimpleSquareMatrix<type,4>::Field[2][0];
    work.y +=     pos.x*CSimpleSquareMatrix<type,4>::Field[0][1] +
                  pos.y*CSimpleSquareMatrix<type,4>::Field[1][1] +
                  pos.z*CSimpleSquareMatrix<type,4>::Field[2][1];
    work.z +=     pos.x*CSimpleSquareMatrix<type,4>::Field[0][2] +
                  pos.y*CSimpleSquareMatrix<type,4>::Field[1][2] +
                  pos.z*CSimpleSquareMatrix<type,4>::Field[2][2];

    return(work);
}

//------------------------------------------------------------------------------
//##############################################################################
//------------------------------------------------------------------------------

template<class type>
void CSimpleTransformation<type>::QuaternionFit(
    const CSimpleVector< CSimplePoint<type> >& ref,
    const CSimpleVector< CSimplePoint<type> >& sys)
{
    CSimpleSquareMatrix<type,4>    helper;
    type       rx,ry,rz;
    type       fx,fy,fz;
    type       xxyx, xxyy, xxyz;
    type       xyyx, xyyy, xyyz;
    type       xzyx, xzyy, xzyz;
    type       q[4];

// generate the upper triangle of the quadratic form matrix
    xxyx = 0.0;
    xxyy = 0.0;
    xxyz = 0.0;
    xyyx = 0.0;
    xyyy = 0.0;
    xyyz = 0.0;
    xzyx = 0.0;
    xzyy = 0.0;
    xzyz = 0.0;

    for(int i = 0; i < ref.GetLength(); i++) {
        rx = sys[i].x;
        ry = sys[i].y;
        rz = sys[i].z;
        fx = ref[i].x;
        fy = ref[i].y;
        fz = ref[i].z;

        xxyx += fx*rx;
        xxyy += fx*ry;
        xxyz += fx*rz;
        xyyx += fy*rx;
        xyyy += fy*ry;
        xyyz += fy*rz;
        xzyx += fz*rx;
        xzyy += fz*ry;
        xzyz += fz*rz;
    }

    helper.Field[0][0] = xxyx + xyyy + xzyz;

    helper.Field[0][1] = xzyy - xyyz;
    helper.Field[1][1] = xxyx - xyyy - xzyz;

    helper.Field[0][2] = xxyz - xzyx;
    helper.Field[1][2] = xxyy + xyyx;
    helper.Field[2][2] = xyyy - xzyz - xxyx;

    helper.Field[0][3] = xyyx - xxyy;
    helper.Field[1][3] = xzyx + xxyz;
    helper.Field[2][3] = xyyz + xzyy;
    helper.Field[3][3] = xzyz - xxyx - xyyy;

// complete matrix
    helper.Field[1][0] = helper.Field[0][1];

    helper.Field[2][0] = helper.Field[0][2];
    helper.Field[2][1] = helper.Field[1][2];

    helper.Field[3][0] = helper.Field[0][3];
    helper.Field[3][1] = helper.Field[1][3];
    helper.Field[3][2] = helper.Field[2][3];

// diagonalize helper matrix
    helper.EigenProblem(q);

// extract the desired quaternion
    q[0] = helper.Field[0][3];
    q[1] = helper.Field[1][3];
    q[2] = helper.Field[2][3];
    q[3] = helper.Field[3][3];

// generate the rotation matrix
    helper.SetUnit();

    helper.Field[0][0] = q[0]*q[0] + q[1]*q[1] - q[2]*q[2] - q[3]*q[3];
    helper.Field[1][0] = 2.0 * (q[1] * q[2] - q[0] * q[3]);
    helper.Field[2][0] = 2.0 * (q[1] * q[3] + q[0] * q[2]);

    helper.Field[0][1] = 2.0 * (q[2] * q[1] + q[0] * q[3]);
    helper.Field[1][1] = q[0]*q[0] - q[1]*q[1] + q[2]*q[2] - q[3]*q[3];
    helper.Field[2][1] = 2.0 * (q[2] * q[3] - q[0] * q[1]);

    helper.Field[0][2] = 2.0 * (q[3] * q[1] - q[0] * q[2]);
    helper.Field[1][2] = 2.0 * (q[3] * q[2] + q[0] * q[1]);
    helper.Field[2][2] = q[0]*q[0] - q[1]*q[1] - q[2]*q[2] + q[3]*q[3];

    CSimpleSquareMatrix<type,4>::MultFromRightWith(helper);
}

//------------------------------------------------------------------------------
//##############################################################################
//------------------------------------------------------------------------------

template<class type>
void CSimpleTransformation<type>::Load(CXMLElement* p_ele)
{
    if( p_ele == NULL ){
        INVALID_ARGUMENT("p_ele == NULL");
    }

    p_ele->GetAttribute("m00",CSimpleSquareMatrix<type,4>::Field[0][0]);
    p_ele->GetAttribute("m01",CSimpleSquareMatrix<type,4>::Field[0][1]);
    p_ele->GetAttribute("m02",CSimpleSquareMatrix<type,4>::Field[0][2]);
    p_ele->GetAttribute("m03",CSimpleSquareMatrix<type,4>::Field[0][3]);

    p_ele->GetAttribute("m10",CSimpleSquareMatrix<type,4>::Field[1][0]);
    p_ele->GetAttribute("m11",CSimpleSquareMatrix<type,4>::Field[1][1]);
    p_ele->GetAttribute("m12",CSimpleSquareMatrix<type,4>::Field[1][2]);
    p_ele->GetAttribute("m13",CSimpleSquareMatrix<type,4>::Field[1][3]);

    p_ele->GetAttribute("m20",CSimpleSquareMatrix<type,4>::Field[2][0]);
    p_ele->GetAttribute("m21",CSimpleSquareMatrix<type,4>::Field[2][1]);
    p_ele->GetAttribute("m22",CSimpleSquareMatrix<type,4>::Field[2][2]);
    p_ele->GetAttribute("m23",CSimpleSquareMatrix<type,4>::Field[2][3]);

    p_ele->GetAttribute("m30",CSimpleSquareMatrix<type,4>::Field[3][0]);
    p_ele->GetAttribute("m31",CSimpleSquareMatrix<type,4>::Field[3][1]);
    p_ele->GetAttribute("m32",CSimpleSquareMatrix<type,4>::Field[3][2]);
    p_ele->GetAttribute("m33",CSimpleSquareMatrix<type,4>::Field[3][3]);
}

//------------------------------------------------------------------------------

template<class type>
void CSimpleTransformation<type>::Save(CXMLElement* p_ele)
{
    if( p_ele == NULL ){
        INVALID_ARGUMENT("p_ele == NULL");
    }

    p_ele->SetAttribute("m00",CSimpleSquareMatrix<type,4>::Field[0][0]);
    p_ele->SetAttribute("m01",CSimpleSquareMatrix<type,4>::Field[0][1]);
    p_ele->SetAttribute("m02",CSimpleSquareMatrix<type,4>::Field[0][2]);
    p_ele->SetAttribute("m03",CSimpleSquareMatrix<type,4>::Field[0][3]);

    p_ele->SetAttribute("m10",CSimpleSquareMatrix<type,4>::Field[1][0]);
    p_ele->SetAttribute("m11",CSimpleSquareMatrix<type,4>::Field[1][1]);
    p_ele->SetAttribute("m12",CSimpleSquareMatrix<type,4>::Field[1][2]);
    p_ele->SetAttribute("m13",CSimpleSquareMatrix<type,4>::Field[1][3]);

    p_ele->SetAttribute("m20",CSimpleSquareMatrix<type,4>::Field[2][0]);
    p_ele->SetAttribute("m21",CSimpleSquareMatrix<type,4>::Field[2][1]);
    p_ele->SetAttribute("m22",CSimpleSquareMatrix<type,4>::Field[2][2]);
    p_ele->SetAttribute("m23",CSimpleSquareMatrix<type,4>::Field[2][3]);

    p_ele->SetAttribute("m30",CSimpleSquareMatrix<type,4>::Field[3][0]);
    p_ele->SetAttribute("m31",CSimpleSquareMatrix<type,4>::Field[3][1]);
    p_ele->SetAttribute("m32",CSimpleSquareMatrix<type,4>::Field[3][2]);
    p_ele->SetAttribute("m33",CSimpleSquareMatrix<type,4>::Field[3][3]);
}

//------------------------------------------------------------------------------
//##############################################################################
//------------------------------------------------------------------------------

#endif
