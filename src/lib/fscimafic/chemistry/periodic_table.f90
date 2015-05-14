!===============================================================================
! SciMaFic - Library Supporting Scientific Calculations
!-------------------------------------------------------------------------------
!    Copyright (C) 2009       Petr Kulhanek, kulhanek@chemi.muni.cz
!    Copyright (C) 2007,2008  Petr Kulhanek, kulhanek@enzim.hu
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

module smf_periodic_table

use smf_sizes

implicit none
contains

!===============================================================================
!-------------------------------------------------------------------------------
!===============================================================================

integer function SearchZByMass(mass,tolerance)

 use smf_periodic_table_dat

 implicit none
 real(SMFDP),intent(in)    :: mass
 real(SMFDP),intent(in)    :: tolerance
 ! -----------------------------------------------
 integer                :: i
 ! -----------------------------------------------------------------------------

 SearchZByMass = 1  ! by default hydrogen

 do i=1,CPT_NELEMENTS
    if( abs(pt_masses(i) - mass) .le. tolerance ) then
        SearchZByMass = i
        return
    end if
 end do

end function SearchZByMass

!===============================================================================
!-------------------------------------------------------------------------------
!===============================================================================

integer function SearchZBySymbol(symbol)

 use smf_periodic_table_dat

 implicit none
 character(len=SMF_MAX_SYMBOL)       :: symbol
 ! -----------------------------------------------
 integer                :: i
 ! -----------------------------------------------------------------------------

 SearchZBySymbol = 0  ! by default zero -> error

 do i=1,CPT_NELEMENTS
    if( trim(pt_symbols(i)) .eq. trim(symbol) ) then
        SearchZBySymbol = i
        return
    end if
 end do

end function SearchZBySymbol

!===============================================================================
!-------------------------------------------------------------------------------
!===============================================================================

real(SMFDP) function SearchMassBySymbol(symbol)

 use smf_periodic_table_dat

 implicit none
 character(len=SMF_MAX_SYMBOL)       :: symbol
 ! -----------------------------------------------
 integer                :: i
 ! -----------------------------------------------------------------------------

 SearchMassBySymbol = 0.0  ! by default zero -> error

 do i=1,CPT_NELEMENTS
    if( trim(pt_symbols(i)) .eq. trim(symbol) ) then
        SearchMassBySymbol = pt_masses(i)
        return
    end if
 end do

end function SearchMassBySymbol

!===============================================================================
!-------------------------------------------------------------------------------
!===============================================================================

end module smf_periodic_table

