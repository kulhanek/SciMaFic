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

#include <XYZHessian.hpp>
#include <string.h>

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

CXYZHessian::CXYZHessian(void)
{
    NumOfAtoms = 0;
    Array = NULL;
}

// ----------------------------------------------------------------------------

CXYZHessian::~CXYZHessian(void)
{
    if( Array != NULL ) delete[] Array;
    Array = NULL;
    NumOfAtoms = 0;
    Comment = NULL;
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

bool CXYZHessian::LoadHessian(const CSmallString& name)
{
    FILE* p_file = fopen(name,"r");

    if( p_file == NULL ) return(false);

    bool result = LoadHessian(p_file);

    fclose(p_file);

    return(result);
}

// ----------------------------------------------------------------------------

bool CXYZHessian::LoadHessian(FILE* p_fin)
{
    // clean previous data
    SetNumberOfAtoms(0);

    int numofatoms = 0;
    // get number of atoms
    if( fscanf(p_fin,"%d",&numofatoms) != 1 ) return(false);

    if( numofatoms == 0 ) return(false);
    if( SetNumberOfAtoms(numofatoms) == false ) return(false);

    char mode;
    if( fscanf(p_fin," %c",&mode) != 1 ) return(false);

    // skip ends of the first line
    int c = 0;
    while( ((c = fgetc(p_fin)) != '\n') && (feof(p_fin) == false) );
    // read comment line
    if( Comment.ReadLineFromFile(p_fin) == false ) return(false);

    // remove terminal '\n' characters in Comment
    if( Comment.GetLength() > 1 ) {
        Comment[Comment.GetLength()-1] = '\0';
    }

    // load data
    switch(mode) {
    case 'U':
        for(int i=0; i < 3*NumOfAtoms; i++) {
            for(int j=0; j < 3*NumOfAtoms-i; j++) {
                //                if( fscanf(p_fin,"%+16.13e ",&Array[i*3*NumOfAtoms+j]) != 1 ) return(false);
            }
        }
        break;
    case 'L':
        for(int i=0; i < 3*NumOfAtoms; i++) {
            for(int j=0; j < 3*NumOfAtoms-i; j++) {
                //             if( fscanf(p_fin,"%+16.13e ",&Array[i*3*NumOfAtoms+j]) != 1 ) return(false);
            }
        }
        break;
    case 'F':
        for(int i=0; i < 3*NumOfAtoms; i++) {
            for(int j=0; j < 3*NumOfAtoms-i; j++) {
                //            if( fscanf(p_fin,"%+16.13e ",&Array[i*3*NumOfAtoms+j]) != 1 ) return(false);
            }
        }
        break;
    default:
        return(false);
    }

    return(true);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

bool CXYZHessian::SaveHessian(const CSmallString& name,EXYZHessianShape shape)
{
    FILE* p_file = fopen(name,"w");

    if( p_file == NULL ) return(false);

    bool result = SaveHessian(p_file,shape);

    fclose(p_file);

    return(result);
}

// ----------------------------------------------------------------------------

bool CXYZHessian::SaveHessian(FILE* p_fout,EXYZHessianShape shape)
{
    // write number of atoms
    if( fprintf(p_fout,"%d ",NumOfAtoms) <= 0 ) return(false);
    switch(shape) {
    case EHS_UPPER:
        if( fprintf(p_fout,"U\n") <= 0 ) return(false);
        break;
    case EHS_LOWER:
        if( fprintf(p_fout,"L\n") <= 0 ) return(false);
        break;
    case EHS_FULL:
        if( fprintf(p_fout,"F\n") <= 0 ) return(false);
        break;
    default:
        return(false);
    };

    // write comment
    if( fprintf(p_fout,"%s\n",(const char*)Comment) <= 0 ) return(false);

    switch(shape) {
    case EHS_UPPER:
        for(int i=0; i < 3*NumOfAtoms; i++) {
            for(int j=0; j < 3*NumOfAtoms-i; j++) {
                if( fprintf(p_fout,"%+16.13e ",Array[i*3*NumOfAtoms+j]) <= 0 ) return(false);
            }
            if( fprintf(p_fout,"\n") <= 0 ) return(false);
        }
        break;
    case EHS_LOWER:
        for(int i=0; i < 3*NumOfAtoms; i++) {
            for(int j=0; j < i; j++) {
                if( fprintf(p_fout,"%+16.13e ",Array[i*3*NumOfAtoms+j]) <= 0 ) return(false);
            }
            if( fprintf(p_fout,"\n") <= 0 ) return(false);
        }
        break;
    case EHS_FULL:
        for(int i=0; i < 3*NumOfAtoms; i++) {
            for(int j=0; j < 3*NumOfAtoms; j++) {
                if( fprintf(p_fout,"%+16.13e ",Array[i*3*NumOfAtoms+j]) <= 0 ) return(false);
            }
            if( fprintf(p_fout,"\n") <= 0 ) return(false);
        }
        break;
    default:
        return(false);
    };

    return(true);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

int CXYZHessian::GetNumberOfAtoms(void)
{
    return(NumOfAtoms);
}

// ----------------------------------------------------------------------------

bool CXYZHessian::SetNumberOfAtoms(int numofatoms)
{
    if( Array != NULL ) delete[] Array;
    Array = NULL;
    Comment = NULL;
    NumOfAtoms = 0;
    if( numofatoms > 0 ) {
        Array = new double[3*numofatoms*3*numofatoms];
        if( Array == NULL ) return(false);
        NumOfAtoms = numofatoms;
    }
    return(true);
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

const CSmallString& CXYZHessian::GetComment(void)
{
    return(Comment);
}

// ----------------------------------------------------------------------------

void CXYZHessian::SetComment(const CSmallString& comment)
{
    Comment = comment;
    // remove all \n characters
    for(unsigned int i=0; i < Comment.GetLength(); i++) {
        if( Comment[i] == '\n' ) Comment[i] = '|';
    }
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

double CXYZHessian::GetSecondDerivative(int row,int column)
{
    return(Array[row*3*NumOfAtoms+column]);
}

// ----------------------------------------------------------------------------

void CXYZHessian::SetSecondDerivative(int row,int column,const double secdev)
{
    Array[row*3*NumOfAtoms+column] = secdev;
}

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

