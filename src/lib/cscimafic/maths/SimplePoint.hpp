#ifndef SimplePointH
#define SimplePointH
/*! \file SimplePoint.hpp */
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

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

/// 3D point

template<class type>
class CSimplePoint {
public:
    type x,y,z;

public:
    inline CSimplePoint(void);
    inline CSimplePoint(type r_x,type r_y,type r_z);
    inline CSimplePoint(const CSimplePoint<float>& right);
    inline CSimplePoint(const CSimplePoint<double>& right);

    inline void operator = (const CSimplePoint<double>& right);
    inline void operator = (const CSimplePoint<float>& right);

    inline CSimplePoint<type> operator+ (const CSimplePoint<type>& right) const;
    inline const CSimplePoint<type> operator- (const CSimplePoint<type>& right) const;
    inline CSimplePoint<type> operator+ (void) const;
    inline CSimplePoint<type> operator- (void) const;

    inline void operator+=(const CSimplePoint<type>& right);
    inline void operator-=(const CSimplePoint<type>& right);
    inline void operator*=(const double value);
    inline void operator*=(const int value);
    inline void operator/=(const double value);
    inline void operator/=(const int value);

    inline CSimplePoint<type> operator/ (const double a) const;
    inline CSimplePoint<type> operator/ (const int a) const;
    inline CSimplePoint<type> operator* (const double a) const;
    inline CSimplePoint<type> operator* (const int a) const;

    inline operator type* ();

    inline bool operator==(const CSimplePoint<type> &right);
    inline bool operator!=(const CSimplePoint<type> &right);

    inline void Set(type r_x,type r_y,type r_z);
    inline void SetZero(void);
    inline void Normalize(void);
    inline void ConvertToSpherical();
    inline void ConvertToCartesian();
};

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

template<class type> const CSimplePoint<type> Norm(const CSimplePoint<type>& p);
template<class type> type Size(const CSimplePoint<type>& p);
template<class type> type Square(const CSimplePoint<type>& p);
template<class type> type Angle(
    const CSimplePoint<type> &l,
    const CSimplePoint<type> &r);
template<class type> CSimplePoint<type> CrossDot(
    const CSimplePoint<type>& l,
    const CSimplePoint<type>& r);
template<class type> type VectDot(
    const CSimplePoint<type>& l,
    const CSimplePoint<type>& r);

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

template<class type>
inline CSimplePoint<type>::CSimplePoint(void)
    :x(0),y(0),z(0)
{
}

//------------------------------------------------------------------------------

template<class type>
inline CSimplePoint<type>::CSimplePoint(type r_x,type r_y,type r_z)
    :x(r_x),y(r_y),z(r_z)
{
}

//------------------------------------------------------------------------------

template<class type>
inline CSimplePoint<type>::CSimplePoint(const CSimplePoint<float>& right)
    :x(right.x),y(right.y),z(right.z)
{
}

//------------------------------------------------------------------------------

template<class type>
inline CSimplePoint<type>::CSimplePoint(const CSimplePoint<double>& right)
    :x(right.x),y(right.y),z(right.z)
{

}

//------------------------------------------------------------------------------

template<class type>
inline void CSimplePoint<type>::operator= (const CSimplePoint<float> &right)
{
    x = right.x;
    y = right.y;
    z = right.z;
}

//------------------------------------------------------------------------------

template<class type>
inline void CSimplePoint<type>::operator= (const CSimplePoint<double> &right)
{
    x = right.x;
    y = right.y;
    z = right.z;
}

//------------------------------------------------------------------------------

template<class type>
inline CSimplePoint<type> CSimplePoint<type>::operator+ (const CSimplePoint<type>& right)const
{
    CSimplePoint<type> work;
    work.x = x + right.x;
    work.y = y + right.y;
    work.z = z + right.z;
    return(work);
}

//------------------------------------------------------------------------------

template<class type>
inline const CSimplePoint<type> CSimplePoint<type>::operator-(const CSimplePoint<type>& right) const
{
    CSimplePoint<type> work;
    work.x = x - right.x;
    work.y = y - right.y;
    work.z = z - right.z;
    return(work);
}

//------------------------------------------------------------------------------

template<class type>
inline CSimplePoint<type> CSimplePoint<type>::operator+ (void)const
{
    CSimplePoint<type> work(*this);
    return(work);
}

//------------------------------------------------------------------------------

template<class type>
inline CSimplePoint<type> CSimplePoint<type>::operator- (void)const
{
    CSimplePoint<type> work(*this);
    work.x *=-1.0;
    work.y *=-1.0;
    work.z *=-1.0;
    return(work);
}

//------------------------------------------------------------------------------

template<class type>
inline void CSimplePoint<type>::operator+=(const CSimplePoint<type>& right)
{
    x += right.x;
    y += right.y;
    z += right.z;
}

//------------------------------------------------------------------------------

template<class type>
inline void CSimplePoint<type>::operator-=(const CSimplePoint<type>& right)
{
    x -= right.x;
    y -= right.y;
    z -= right.z;
}

//------------------------------------------------------------------------------

template<class type>
inline CSimplePoint<type> CSimplePoint<type>::operator/(const double a) const
{
    CSimplePoint<type> work;
    work.x = x/a;
    work.y = y/a;
    work.z = z/a;
    return(work);
}

//------------------------------------------------------------------------------

template<class type>
inline CSimplePoint<type> CSimplePoint<type>::operator/(const int a) const
{
    CSimplePoint<type> work;
    work.x = x/a;
    work.y = y/a;
    work.z = z/a;
    return(work);
}

//------------------------------------------------------------------------------

template<class type>
inline CSimplePoint<type> CSimplePoint<type>::operator*(const double a) const
{
    CSimplePoint<type> work;

    work.x = x*a;
    work.y = y*a;
    work.z = z*a;
    return(work);
}

//------------------------------------------------------------------------------

template<class type>
inline CSimplePoint<type> CSimplePoint<type>::operator* (const int a) const
{
    CSimplePoint<type> work;

    work.x = x*a;
    work.y = y*a;
    work.z = z*a;
    return(work);
}

//------------------------------------------------------------------------------

template<class type>
inline void CSimplePoint<type>::operator*=(const double value)
{
    x *= value;
    y *= value;
    z *= value;
}

//------------------------------------------------------------------------------

template<class type>
inline void CSimplePoint<type>::operator*=(const int value)
{
    x *= value;
    y *= value;
    z *= value;
}

//------------------------------------------------------------------------------

template<class type>
inline void CSimplePoint<type>::operator/=(const double value)
{
    x /= value;
    y /= value;
    z /= value;
}

//------------------------------------------------------------------------------

template<class type>
inline void CSimplePoint<type>::operator/=(const int value)
{
    x /= value;
    y /= value;
    z /= value;
}


//------------------------------------------------------------------------------

template<class type>
inline CSimplePoint<type>::operator type* ()
{
    return(&x);
}

//------------------------------------------------------------------------------

template<class type>
inline bool CSimplePoint<type>::operator==(const CSimplePoint<type>& right)
{
    if( x != right.x )return(false);
    if( y != right.y )return(false);
    if( z != right.z )return(false);
    return(true);
}

//------------------------------------------------------------------------------

template<class type>
inline bool CSimplePoint<type>::operator!=(const CSimplePoint<type>& right)
{
    if( x != right.x )return(true);
    if( y != right.y )return(true);
    if( z != right.z )return(true);
    return(false);
}

//------------------------------------------------------------------------------

template<class type>
inline void CSimplePoint<type>::Set(type r_x,type r_y,type r_z)
{
    x = r_x;
    y = r_y;
    z = r_z;
}

//------------------------------------------------------------------------------

template<class type>
inline void CSimplePoint<type>::SetZero(void)
{
    x = 0;
    y = 0;
    z = 0;
}

//------------------------------------------------------------------------------

template<class type>
inline void CSimplePoint<type>::Normalize(void)
{
    double s = sqrt(x*x + y*y + z*z);
    if( s == 0 ) return;
    x /= s;
    y /= s;
    z /= s;
}

//------------------------------------------------------------------------------

template<class type>
inline void CSimplePoint<type>::ConvertToSpherical()
{
    CSimplePoint<type> temp;

    temp.x = Size(*this);
    if( temp.x == 0 ) {
        temp.y = 0;
        temp.z = 0;
    } else {
        temp.y = acos(z/temp.x);
        if( x != 0 ){
            temp.z = atan2(y,x);
        } else{
            temp.z = 0;
        }
    }
    x = temp.x; // radius
    y = temp.y; // theta   - inclination
    z = temp.z; // phi     - azimuth
}

//------------------------------------------------------------------------------

template<class type>
inline void CSimplePoint<type>::ConvertToCartesian()
{
    CSimplePoint<type> temp;

    temp.x = x*sin(y)*cos(z);
    temp.y = x*sin(y)*sin(z);
    temp.z = x*cos(y);
    x = temp.x;
    y = temp.y;
    z = temp.z;
}

//------------------------------------------------------------------------------

template<class type>
const CSimplePoint<type> Norm(const CSimplePoint<type>& p)
{
    CSimplePoint<type> work;
    double s = sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
    if( s == 0 ) return(work);

    work.x = p.x / s;
    work.y = p.y / s;
    work.z = p.z / s;

    return(work);
}

//------------------------------------------------------------------------------

template<class type>
type Size(const CSimplePoint<type>& p)
{
    return(sqrt(p.x*p.x + p.y*p.y + p.z*p.z));
}

//------------------------------------------------------------------------------

template<class type>
type Square(const CSimplePoint<type>& p)
{
    return (p.x*p.x + p.y*p.y + p.z*p.z);
}

//------------------------------------------------------------------------------

template<class type>
type Angle(const CSimplePoint<type> &l,const CSimplePoint<type> &r)
{
    type top = l.x*r.x + l.y*r.y + l.z*r.z;
    type down = Size(l)*Size(r);
    type rt = top / down;
    if( rt < -1 ) rt = -1;
    if( rt > 1 ) rt = 1;

    return( acos( rt ) );
}

//------------------------------------------------------------------------------

template<class type>
CSimplePoint<type> CrossDot(const CSimplePoint<type>& l,const CSimplePoint<type>& r)
{
    CSimplePoint<type> work;
    work.x = l.y * r.z - l.z * r.y;
    work.y = l.z * r.x - l.x * r.z;
    work.z = l.x * r.y - l.y * r.x;
    return( work );
}

//------------------------------------------------------------------------------

template<class type>
type VectDot(const CSimplePoint<type>& l,const CSimplePoint<type>& r)
{
    return(l.x*r.x + l.y*r.y + l.z*r.z );
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

#endif


