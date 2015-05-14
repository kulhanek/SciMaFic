!===============================================================================
! SciMaFic - Library Supporting Scientific Calculations
!-------------------------------------------------------------------------------
!    Copyright (C) 2007,2008 Petr Kulhanek, kulhanek@enzim.hu
!
!    This library is free software; you can redistribute it and/or
!    modify it under the terms of the GNU Lesser General Public
!    License as published by the Free Software Foundation; either
!    version 2.1 of the License, or (at your option) any later version.
!
!    This library is distributed in the hope that it will be useful,
!    but WITHOUT ANY WARRANTY; without even the implied warranty of
!    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
!    Lesser General Public License for more details.
!
!    You should have received a copy of the GNU Lesser General Public
!    License along with this library; if not, write to the Free Software
!    Foundation, Inc., 51 Franklin Street, Fifth Floor,
!    Boston, MA  02110-1301  USA
!===============================================================================

module smf_xyzfile

implicit none
contains

!===============================================================================
! Subroutine: init_xyz
!===============================================================================

subroutine init_xyz(xyz_file)

 use smf_xyzfile_type

 implicit none
 type(XYZFILE_TYPE),intent(inout)   :: xyz_file
 !------------------------------------------------------------------------------

 xyz_file%natoms    = 0
 xyz_file%opened    = .false.
 xyz_file%comment   = ''
 xyz_file%symbols   => NULL()
 xyz_file%cvs    => NULL()

end subroutine init_xyz

!===============================================================================
! Subroutine: allocate_xyz
!===============================================================================

subroutine allocate_xyz(xyz_file,natoms)

 use smf_xyzfile_type
 use smf_utils
 use smf_constants

 implicit none
 type(XYZFILE_TYPE),intent(inout)   :: xyz_file
 integer                            :: natoms
 !------------------------------------------------
 integer                            :: alloc_status
 !------------------------------------------------------------------------------

 xyz_file%natoms    = natoms
 xyz_file%opened    = .false.
 xyz_file%comment   = ''

 ! allocate arrays
 allocate(xyz_file%symbols(xyz_file%natoms),xyz_file%cvs(3,xyz_file%natoms),stat=alloc_status)

 if( alloc_status .ne. 0 ) then
   call libsmf_exit(SMF_OUT,1,'>>> ERROR: Unable to allocate memory for symbols and/or cvs in allocate_xyz!')
 endif

end subroutine allocate_xyz

!===============================================================================
! Subroutine: free_xyz
!===============================================================================

subroutine free_xyz(xyz_file)

 use smf_xyzfile_type

 implicit none
 type(XYZFILE_TYPE),intent(inout)   :: xyz_file
 !------------------------------------------------------------------------------

 deallocate(xyz_file%symbols,xyz_file%cvs)

 call init_xyz(xyz_file)

end subroutine free_xyz

!===============================================================================
! Subroutine: open_xyz
!===============================================================================

subroutine open_xyz(iounit,name,xyz_file,istatus)

 use smf_xyzfile_type
 use smf_utils
 use smf_constants

 implicit none
 integer,intent(in)                 :: iounit
 character(*),intent(in)            :: name
 type(XYZFILE_TYPE),intent(inout)   :: xyz_file
 character(*),intent(in)            :: istatus
 !------------------------------------------------------------------------------

 ! try to open XYZ file
 open(unit=iounit, file=name, status=istatus, form='FORMATTED', err=100)

 xyz_file%opened = .true.

 return

! error handlers ---------------------------------
100  call libsmf_exit(SMF_OUT,1,&
            '>>> ERROR: Opening of XYZ file ' // trim(name) // ' failed!')

end subroutine open_xyz

!===============================================================================
! Subroutine: close_xyz
!===============================================================================

subroutine close_xyz(iounit,xyz_file)

 use smf_xyzfile_type
 use smf_utils
 use smf_constants

 implicit none
 integer,intent(in)                 :: iounit
 type(XYZFILE_TYPE),intent(inout)   :: xyz_file
 !------------------------------------------------------------------------------

 ! close file
 close(iounit)

 xyz_file%opened = .false.

 return

end subroutine close_xyz

!===============================================================================
! Function: is_next_xyz_record
!===============================================================================

logical function is_next_xyz_record(iounit,xyz_file)

 use smf_xyzfile_type
 use smf_utils
 use smf_constants

 implicit none
 integer,intent(in)                 :: iounit
 type(XYZFILE_TYPE),intent(inout)   :: xyz_file
 !------------------------------------------------------------------------------

 is_next_xyz_record = .false.

 read(iounit,fmt=*,err=110,end=110) xyz_file%natoms

 is_next_xyz_record = .true.
 backspace(iounit)

110 return

end function

!===============================================================================
! Subroutine: read_xyz
!===============================================================================

subroutine read_xyz(iounit,xyz_file)

 use smf_xyzfile_type
 use smf_utils
 use smf_constants

 implicit none
 integer,intent(in)                 :: iounit
 type(XYZFILE_TYPE),intent(inout)   :: xyz_file
 !------------------------------------------------
 integer                            :: alloc_status, i
 !------------------------------------------------------------------------------

 if( xyz_file%opened .eqv. .false. ) then
   call libsmf_exit(SMF_OUT,1,'>>> ERROR: xyz_file is not opened!')
 end if

 ! read header
 read(iounit,fmt=*,err=110,end=110) xyz_file%natoms
 read(iounit,fmt='(A80)',err=120,end=120) xyz_file%comment

 ! allocate arrays
 allocate(xyz_file%symbols(xyz_file%natoms),xyz_file%cvs(3,xyz_file%natoms),stat=alloc_status)

 if( alloc_status .ne. 0 ) then
   call libsmf_exit(SMF_OUT,1,'>>> ERROR: Unable to allocate memory for symbols and/or cvs in read_xyz!')
 endif

 ! read data
 do i=1,xyz_file%natoms
    read(iounit,fmt=*,err=130,end=130) xyz_file%symbols(i), &
                                xyz_file%cvs(1,i),xyz_file%cvs(2,i),xyz_file%cvs(3,i)
 end do

 return

! error handlers ---------------------------------
110  call libsmf_exit(SMF_OUT,1,&
            '>>> ERROR: Cannot read the number of atoms from the first line of XYZ file!')
120  call libsmf_exit(SMF_OUT,1,&
            '>>> ERROR: Cannot read the comment from the second line of XYZ file!')
130  call libsmf_exit(SMF_OUT,1,&
            '>>> ERROR: Cannot read the line with symbol and coordinates!')

end subroutine read_xyz

!===============================================================================
! Subroutine: write_xyz
!===============================================================================

subroutine write_xyz(iounit,xyz_file)

 use smf_xyzfile_type
 use smf_utils
 use smf_constants

 implicit none
 integer,intent(in)             :: iounit
 type(XYZFILE_TYPE),intent(in)  :: xyz_file
 !------------------------------------------------
 integer                        :: i
 !------------------------------------------------------------------------------

 if( xyz_file%opened .eqv. .false. ) then
   call libsmf_exit(SMF_OUT,1,'>>> ERROR: xyz_file is not opened!')
 end if

 ! read header
 write(iounit,fmt=10,err=110) xyz_file%natoms
 write(iounit,fmt=20,err=120) xyz_file%comment

 ! read data
 do i=1,xyz_file%natoms
    write(iounit,fmt=30,err=130) xyz_file%symbols(i), &
                                xyz_file%cvs(1,i),xyz_file%cvs(2,i),xyz_file%cvs(3,i)
 end do

 return

 10  format(I6)
 20  format(A80)
 30  format(A2,1X,F14.6,1X,F14.6,1X,F14.6)

! error handlers ---------------------------------
110  call libsmf_exit(SMF_OUT,1,&
            '>>> ERROR: Cannot write the number of atoms to the first line of XYZ file!')
120  call libsmf_exit(SMF_OUT,1,&
            '>>> ERROR: Cannot write the comment to the second line of XYZ file!')
130  call libsmf_exit(SMF_OUT,1,&
            '>>> ERROR: Cannot write the line with symbol and coordinates!')

end subroutine write_xyz

!===============================================================================
! Subroutine: print_xyz_info
!===============================================================================

subroutine print_xyz_info(io_out,xyz_file)

 use smf_xyzfile_type
 use smf_utils
 use smf_constants

 implicit none
 integer,intent(in)             :: io_out
 type(XYZFILE_TYPE),intent(in)  :: xyz_file
 !------------------------------------------------------------------------------

 write(io_out,'(a24,i8)') 'Total number of atoms = ',xyz_file%natoms
 write(io_out,'(a24,a)')  'XYZ file comment      = ',trim(xyz_file%comment)

end subroutine print_xyz_info

!===============================================================================
! Subroutine: print_xyz
!===============================================================================

subroutine print_xyz(io_out,xyz_file)

 use smf_xyzfile_type
 use smf_utils
 use smf_constants

 implicit none
 integer,intent(in)             :: io_out
 type(XYZFILE_TYPE),intent(in)  :: xyz_file
 ! -----------------------------------------------
 integer                        :: i
 !------------------------------------------------------------------------------

 write(io_out,10)
 write(io_out,20)

 do i=1,xyz_file%natoms
    write(io_out,30) i,xyz_file%symbols(i),xyz_file%cvs(1,i),xyz_file%cvs(2,i),xyz_file%cvs(3,i)
 end do

 return

10 format('  Index   Symbol            X [A]              Y [A]               Z [A]        ')
20 format(' ------- -------- -------------------- -------------------- --------------------')
30 format(2X,I5,3X,A6,3X,F18.6,3X,F18.6,3X,F18.6)

end subroutine print_xyz

!===============================================================================
!-------------------------------------------------------------------------------
!===============================================================================

end module smf_xyzfile
