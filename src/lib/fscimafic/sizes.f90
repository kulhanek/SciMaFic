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

module smf_sizes

implicit none

! ------------------------------------------------------------------------------

integer,parameter       :: SMFDP                = 8     ! double precision - real(8)
integer,parameter       :: SMFSP                = 4     ! single precision - real(4)
integer,parameter       :: SMF_MAX_TIMER_TITLE  = 30    ! maximum length of timer legend
integer,parameter       :: SMF_MAX_TIMER_LINE   = 80    ! maximum length of line in write_timer
integer,parameter       :: SMF_MAX_SYMBOL       = 2
integer,parameter       :: SMF_MAX_XYZ_COMMENT  = 80

! ------------------------------------------------------------------------------

end module smf_sizes

!===============================================================================
