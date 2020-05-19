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

module smf_utils

use smf_sizes

implicit none
contains

!===============================================================================
! Subroutine:   libsmf_exit
!===============================================================================

subroutine libsmf_exit(unitnum, errcode, message)

 implicit none
 integer                :: unitnum
 integer                :: errcode
 character(*),optional  :: message
 ! -----------------------------------------------------------------------------

 if(present(message)) then
     write(unitnum,'(/,A)') message
 end if

 write(unitnum,'(/,A)') '>>> ERROR: Some fatal error occured in SciMaFic!'
 write(unitnum,'(A)')   '           Look above for detailed message (if any).'
 write(unitnum,'(A,/)') '           Program execution is terminated.'

 if( errcode .eq. 0 ) then
    stop 0
 else
    stop 1
 end if

end subroutine libsmf_exit

!===============================================================================
! Function:   real(DP) function rtime()
!===============================================================================

real(SMFDP) function rtime()

 implicit none
 ! -----------------------------------------------------------------------------

 INTEGER :: count, count_rate, count_max
 CALL SYSTEM_CLOCK(count, count_rate, count_max)
 rtime = real(count,SMFDP) / real(count_rate,SMFDP)

 ! this return all CPU time - misleading for OpenMP apps
 ! call cpu_time(rtime)
 
return

end function rtime

!===============================================================================
! Subroutine:   centered_heading
!===============================================================================

subroutine centered_heading(unit,msg,fill)

 implicit none
 integer,intent(in)         :: unit
 character(*),intent(in)    :: msg
 character,intent(in)       :: fill
 ! -----------------------------------------------
 integer                    :: n,m,i
 ! -----------------------------------------------------------------------------

 if( mod(len(msg),2) .eq. 0 ) then
    n = (80 - len(msg) - 2) / 2
    m = n
 else
    n = (80 - len(msg) - 2) / 2
    m = n+1
 end if

 write(unit,'(80a)') (fill, i=1,n), ' ', msg, ' ', (fill, i=1,m)

end subroutine centered_heading

!===============================================================================
! Subroutine:   centered_heading_closed
!===============================================================================

subroutine centered_heading_closed(unit,msg,fill,closing)

 implicit none
 integer,intent(in)         :: unit
 character(*),intent(in)    :: msg
 character,intent(in)       :: fill
 character,intent(in)       :: closing
 ! -----------------------------------------------
 integer                    :: n,m,i
 ! -----------------------------------------------------------------------------

 if( mod(len(msg),2) .eq. 0 ) then
    n = (80 - len(msg) - 2) / 2 - 1
    m = n
 else
    n = (80 - len(msg) - 2) / 2 - 1
    m = n + 1
 end if

 write(unit,'(80a)') closing,(fill, i=1,n), ' ', msg, ' ', (fill, i=1,m),closing

end subroutine centered_heading_closed

!===============================================================================

end module smf_utils

!===============================================================================
