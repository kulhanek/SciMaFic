#ifndef SimpleVectorH
#define SimpleVectorH
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
#include <stdlib.h>
#include <string.h>
#include <new>
#include <ErrorSystem.hpp>
#include <XMLBinData.hpp>
#include <typeinfo>
#include <Point.hpp>

// -----------------------------------------------------------------------------

/*! \brief vector support
 */

template<class OType>
class CSimpleVector {
public:
// constructor and destructor -------------------------------------------------
    CSimpleVector(void);
    CSimpleVector(const CSimpleVector& src);
    template <class IType>  CSimpleVector(const CSimpleVector<IType>& src);
    virtual                 ~CSimpleVector(void);

    CSimpleVector&                          operator=(const CSimpleVector& src);
    template <class IType>  CSimpleVector&  operator=(const CSimpleVector<IType>& src);

// allocation/deallocation methods --------------------------------------------
    /// create vector of size
    void CreateVector(int size);
    /// deallocate vector
    void FreeVector(void);

    /// return length of vector
    int GetLength(void) const;

// input/output methods ------------------------------------------------------
    /// load vector from XML binary element
    void Load(CXMLBinData* p_ele);

    /// save vector to XML binary element
    void Save(CXMLBinData* p_ele);

// set methods ---------------------------------------------------------------
    /// set all elements to zero
    void SetZero(void);

    /// set all elements to value
    void Set(OType value);

// operators ------------------------------------------------------------------
    /// access indivudual vector elements
    OType& operator [] (const unsigned int index);
    OType& operator [] (const int index);

    /// access individual vector elements
    const OType& operator [] (const unsigned int index) const;
    const OType& operator [] (const int index) const;

    /// return pointer to vector array
    operator const OType*() const;

    /// return pointer to vector array
    operator OType*();

    /// return pointer to vector array
    OType*  GetRawDataField(void);

// section of private data -----------------------------------------------------
private:
    long unsigned int   Size;       // size of array
    OType*              Array;      // array
};

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

template<class OType>
CSimpleVector<OType>::CSimpleVector(void)
{
    Size = 0;
    Array = NULL;
}

//------------------------------------------------------------------------------

template<class OType>
CSimpleVector<OType>::CSimpleVector(const CSimpleVector& src)
{
    Size = 0;
    Array = NULL;
    CreateVector(src.GetLength());
    if( Size != 0 ){
        memcpy(Array,src.Array,Size*sizeof(OType));
    }
}

//------------------------------------------------------------------------------

template<class OType> template<class IType>
CSimpleVector<OType>::CSimpleVector(const CSimpleVector<IType>& src)
{
    Size = 0;
    Array = NULL;
    CreateVector(src.GetLength());
    for(long unsigned int i=0; i < Size; i++) {
        Array[i] = src[i];
    }
}

//------------------------------------------------------------------------------

template<class OType>
CSimpleVector<OType>& CSimpleVector<OType>::operator=(const CSimpleVector& src)
{
    CreateVector(src.GetLength());
    if( Size != 0 ){
        memcpy(Array,src.Array,Size*sizeof(OType));
    }
    return(*this);
}

//------------------------------------------------------------------------------

template <class OType> template<class IType>
CSimpleVector<OType>&  CSimpleVector<OType>::operator=(const CSimpleVector<IType>& src)
{
    CreateVector(src.GetLength());
    for(int i=0; i < Size; i++) {
        Array[i] = src[i];
    }
    return(*this);
}

//------------------------------------------------------------------------------

template<class OType>
CSimpleVector<OType>::~CSimpleVector(void)
{
    if( Array != NULL) delete[] Array;
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

template<class OType>
void CSimpleVector<OType>::CreateVector(int size)
{
    if( size < 0 ){
        INVALID_ARGUMENT("size < 0");
    }

    if(Size > 0) {
        FreeVector();
    }
    if( size == 0 ) return;

    Array = new OType[size];
    Size = size;
}

//------------------------------------------------------------------------------

template<class OType>
void CSimpleVector<OType>::FreeVector(void)
{
    if( Array != NULL) delete[] Array;
    Size = 0;
    Array = NULL;
}

//------------------------------------------------------------------------------

template<class OType>
int CSimpleVector<OType>::GetLength(void) const
{
    return(Size);
}

//------------------------------------------------------------------------------

template<class OType>
void CSimpleVector<OType>::Load(CXMLBinData* p_ele)
{
    if( p_ele == NULL ) {
        INVALID_ARGUMENT("p_ele is NULL");
    }

// get size
    unsigned int size;
    size = p_ele->GetLength();
    if( size <= 0 ) return;

// create vector
    CreateVector(size/sizeof(OType));

// load data
    EXMLBinDataType ltype = EXBDT_UNKNOWN;

    if( typeid(OType) == typeid(int) ) ltype = EXBDT_INT;
    if( typeid(OType) == typeid(double) ) ltype = EXBDT_DOUBLE;
    if( typeid(OType) == typeid(CPoint) ) ltype = EXBDT_DOUBLE;

    if( ltype == EXBDT_UNKNOWN ) {
        ES_WARNING("unknown data type - is it implemented?");
    }

    EXMLBinDataType etype = EXBDT_UNKNOWN;

    etype = p_ele->GetDataType();

    if( ltype != etype ) {
        LOGIC_ERROR("type mismatch");
    }

// copy data
    void* p_data = p_ele->GetData();
    if( p_data == NULL ) {
        RUNTIME_ERROR("unable to get data");
    }
    memcpy(Array,p_data,size);
}

//------------------------------------------------------------------------------

template<class OType>
void CSimpleVector<OType>::Save(CXMLBinData* p_ele)
{
    if( p_ele == NULL ) {
        INVALID_ARGUMENT("p_ele is NULL");
    }

    EXMLBinDataType type = EXBDT_UNKNOWN;

    if( typeid(OType) == typeid(int) ) type = EXBDT_INT;
    if( typeid(OType) == typeid(double) ) type = EXBDT_DOUBLE;
    if( typeid(OType) == typeid(CPoint) ) type = EXBDT_DOUBLE;

    if( type == EXBDT_UNKNOWN ) {
        ES_WARNING("unknown data type - is it implemented?");
    }

    p_ele->CopyData(Array,Size*sizeof(OType),type);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

template<class OType>
void CSimpleVector<OType>::SetZero(void)
{
    for(long unsigned int i=0; i < Size; i++) Array[i] = 0;
}

//------------------------------------------------------------------------------

template<class OType>
void CSimpleVector<OType>::Set(OType value)
{
    for(long unsigned int i=0; i < Size; i++) Array[i] = value;
}

//------------------------------------------------------------------------------

template<class OType>
OType& CSimpleVector<OType>::operator [] (const unsigned int index)
{
    return(Array[index]);
}

//------------------------------------------------------------------------------

template<class OType>
OType& CSimpleVector<OType>::operator [] (const int index)
{
    return(Array[index]);
}

//------------------------------------------------------------------------------

template<class OType>
const OType& CSimpleVector<OType>::operator [] (const unsigned int index) const
{
    return(Array[index]);
}

//------------------------------------------------------------------------------

template<class OType>
const OType& CSimpleVector<OType>::operator [] (const int index) const
{
    return(Array[index]);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

template<class OType>
CSimpleVector<OType>::operator const OType*() const
{
    return(Array);
}

// -----------------------------------------------------------------------------

template<class OType>
CSimpleVector<OType>::operator OType*()
{
    return(Array);
}

// -----------------------------------------------------------------------------

template<class OType>
OType* CSimpleVector<OType>::GetRawDataField(void)
{
    return(Array);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

#endif
