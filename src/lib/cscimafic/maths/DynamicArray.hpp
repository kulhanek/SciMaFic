#ifndef DynamicArrayH
#define DynamicArrayH
/*! \file DynamicArray.hpp */
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
#include "SimpleList.hpp"

//------------------------------------------------------------------------------

class SCIMAFIC_PACKAGE CDynamicArray {
public:
    CDynamicArray(void);
    ~CDynamicArray(void);

    /// get current size of array
    int  GetSize(void);

    /// remove all data from array
    void Clear(void);

    /// append new element to the end of array
    bool AppendValue(const double& value);

    /// access individual members of array
    double& operator[](int index);

// load data from file --------------------------------------------------------
    bool ReadData(FILE* InputFile,
                               int SkipLines,int AnalLines,
                               int PadLines,int ColumnIndex);

// section of private data ----------------------------------------------------
private:
    int                     BufferLength;
    int                     ActualSize;
    CSimpleList<double>     SubArrays;

    // write information
    double*                 CurrentWriteBlock;
    int                     PositionInWriteBlock;

    // read operation
    double*                 CurrentReadBlock;
    int                     ReadBlockIndex;

    static double zero;
};

//------------------------------------------------------------------------------
#endif
