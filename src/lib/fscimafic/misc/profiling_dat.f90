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

module smf_profiling_dat

use smf_sizes
use smf_profiling_types

implicit none

! timers data ------------------------------------------------------------------
integer                         :: MAX_NUMBER_OF_TIMERS     = 50    ! max number of timers
integer                         :: TIM_OUT                  = 6     ! output unit
integer                         :: TopTimer                 = 0     ! Index of last timer
type(ROUTINE_TIMER),allocatable :: Timers(:)                        ! list of timers

! ------------------------------------------------------------------------------

end module smf_profiling_dat

!===============================================================================
