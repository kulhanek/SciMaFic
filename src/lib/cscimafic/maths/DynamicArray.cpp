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

#include <ctype.h>
#include <DynamicArray.hpp>
#include <SimpleIterator.hpp>

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

double SCIMAFIC_PACKAGE CDynamicArray::zero = 0.0;

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

__hipolyspec CDynamicArray::CDynamicArray(void)
{
    BufferLength = 32768;
    ActualSize = 0;
    CurrentWriteBlock = NULL;
    PositionInWriteBlock = 0;
    CurrentReadBlock = NULL;
    ReadBlockIndex = -1;
}

//------------------------------------------------------------------------------

__hipolyspec CDynamicArray::~CDynamicArray(void)
{
    Clear();
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

int  CDynamicArray::GetSize(void)
{
    return(ActualSize);
}

//------------------------------------------------------------------------------

void CDynamicArray::Clear(void)
{
    CSimpleIterator<double> I(SubArrays);
    double* p_subarray;
    while( (p_subarray = I.Current()) != NULL ) {
        delete[] p_subarray;
        I++;
    }
    SubArrays.RemoveAll();
    ActualSize = 0;
    CurrentWriteBlock = NULL;
    PositionInWriteBlock = 0;
    CurrentReadBlock = NULL;
    ReadBlockIndex = -1;
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

bool CDynamicArray::AppendValue(const double& value)
{
    if( (CurrentWriteBlock == NULL) || (PositionInWriteBlock >= BufferLength) ) {
        CurrentWriteBlock = new double[BufferLength];
        if( CurrentWriteBlock == NULL ) return(false);
        SubArrays.InsertToEnd(CurrentWriteBlock);
        PositionInWriteBlock=0;
    }
    CurrentWriteBlock[PositionInWriteBlock++] = value;
    ActualSize++;
    return(true);
}

//------------------------------------------------------------------------------

double& CDynamicArray::operator[](int index)
{
    int bpos = index / BufferLength;
    if( bpos != ReadBlockIndex ) {
        CurrentReadBlock = SubArrays[bpos];
        ReadBlockIndex = bpos;
    }
    if( CurrentReadBlock == NULL ) return(zero);
    return(CurrentReadBlock[index % BufferLength]);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

bool CDynamicArray::ReadData(FILE* InputFile,int SkipLines,int AnalLines,int PadLines,int ColumnIndex)
{
    // read specified data to dynamic array

    // skip first <SkipLines> lines
    int sl = 0;
    int c;
    while( (sl < SkipLines) && (feof(InputFile) == 0) ) {
        c = fgetc(InputFile);
        if( c == '\n' ) sl++;
    }
    if( feof(InputFile) > 0 ) return(true); // no other data

    // now we are ready to read real data --------------

    while( feof(InputFile) == false ) {

        // find data in column --------------
        bool is_space = true;

        sl = 1;
        while( (sl < ColumnIndex) && (feof(InputFile) == 0) ) {
            c = fgetc(InputFile);
            if( c == '\n' ) {
                if( sl > 0 ) {
                    printf("ERROR: Unexpected end of line ! Only \'%d\' columns from \'%d\' were read.\n",sl,ColumnIndex);
                    return(false);
                }
            }
            if( isspace(c) > 0 ) {
                if( is_space == false ) {
                    sl ++;
                    is_space = true;
                }
            } else {
                is_space = false;
            }

        }
        if( feof(InputFile) > 0 ) return(true); // no other data

        // read data from column -------------------
        double value = 0;
        if( fscanf(InputFile,"%le",&value) != 1 ) {
            if( ColumnIndex == 1 ) {
                while( feof(InputFile) == 0 ) {
                    c = fgetc(InputFile);
                    if( isspace(c) == 0 ) {
                        printf("ERROR: read error - file contains non-numeric record in specified column !\n");
                        return(false);
                    }
                }
                return(true);
            } else {
                printf("ERROR: read error - file contains non-numeric record in specified column !\n");
            }
            return(false);
        }
        AppendValue(value);

        if( (AnalLines > 0) && (GetSize() >= AnalLines) ) return(true);

        // read to line end  -------------------
        do {
            c = fgetc(InputFile);
        } while( (c != '\n') && (feof(InputFile) == 0) );

        // read pad lines -----------------------
        int sl = 0;
        while( (sl < PadLines) && (feof(InputFile) == 0) ) {
            c = fgetc(InputFile);
            if( c == '\n' ) sl++;
        }
    }

    return(true);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================
