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

module smf_profiling

implicit none

! timer indexes ----------------------------------------------------------------
integer                     :: TOTAL_TIMER              =  -1

contains

!===============================================================================
!-------------------------------------------------------------------------------
!===============================================================================

subroutine init_profiling(out_unit,max_timers)

 use smf_profiling_dat
 use smf_utils

 implicit none
 integer,intent(in) :: out_unit         ! output unit number
 integer,intent(in) :: max_timers       ! maximum number of timers
 ! -----------------------------------------------
 integer            :: i,alloc_failed
 ! -----------------------------------------------------------------------------

 TIM_OUT = out_unit
 MAX_NUMBER_OF_TIMERS = max_timers

 if( MAX_NUMBER_OF_TIMERS .le. 0 ) return

 ! allocate timers
 allocate(Timers(MAX_NUMBER_OF_TIMERS),  stat=alloc_failed)

 if( alloc_failed .ne. 0 ) then
   call libsmf_exit(TIM_OUT,1,'>>> ERROR: Unable to allocate memory for Timers in init_profiling!')
 endif

 ! clear the whole timer array -------------------
 do i=1,MAX_NUMBER_OF_TIMERS
    Timers(i)%id = 0
    Timers(i)%root_id = 0
    Timers(i)%started = .FALSE.
    Timers(i)%start = 0.0d0
    Timers(i)%total = 0.0d0
    Timers(i)%title = ''
 end do

 TopTimer = 0

 ! add standard timers --------------------------------
 TOTAL_TIMER            = add_timer(0,'Total time')

end subroutine init_profiling

!===============================================================================
!-------------------------------------------------------------------------------
!===============================================================================

subroutine finalize_profiling

 use smf_profiling_dat

 implicit none
 ! -----------------------------------------------------------------------------

 ! destroy allocated memory
 if( allocated(Timers) ) then
    deallocate(Timers)
 end if

end subroutine finalize_profiling

!===============================================================================
!-------------------------------------------------------------------------------
!===============================================================================

subroutine write_timing

 use smf_profiling_dat

 implicit none
 integer        :: total,d,h,m,s,ms
 ! -----------------------------------------------------------------------------

 write(TIM_OUT,10)
 write(TIM_OUT,20)
 write(TIM_OUT,30)
 call write_timer(TOTAL_TIMER,0)
 write(TIM_OUT,30)

 ! total time -------------------
 total = 0
 d     = 0
 h     = 0
 m     = 0
 s     = 0
 ms    = 0
 if( TOTAL_TIMER .gt. 0 ) then
    total = Timers(TOTAL_TIMER)%total * 1000d0
    ms = mod(total,1000)
    total = total / 1000
    s = mod(total,60)
    total = total / 60
    m = mod(total,60)
    total = total / 60
    h = mod(total,24)
    d = total / 24
 end if
 write(TIM_OUT,40) d,h,m,s,ms
 write(TIM_OUT,50)

 return

10 format(/,'>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> [profiling] <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<')
20 format(  ' code part                                                    time [s]  time [%]')
30 format(  '--------------------------------------------------------------------------------')
40 format(  ' Total execution time: ',I2,' days ',I2.2,':',I2.2,':',I2.2,'.',I3.3)
50 format(  '>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<')

end subroutine write_timing

!===============================================================================
!-------------------------------------------------------------------------------
!===============================================================================

recursive subroutine write_timer(timer_id,level)

 use smf_profiling_dat
 use smf_utils

 implicit none
 integer,intent(in) :: timer_id
 integer,intent(in) :: level
 ! -----------------------------------------------
 real(SMFDP)                    :: total_time
 real(SMFDP)                    :: timer_time
 real(SMFDP)                    :: timer_time_perc
 integer                        :: i
 character(SMF_MAX_TIMER_LINE)  :: space
 ! -----------------------------------------------------------------------------

 if( (timer_id .gt. TopTimer)  .or. (timer_id .le. 0) ) then
    call libsmf_exit(TIM_OUT,1,'>>> ERROR: Illegal timer_id in write_timer!')
 end if

 space(:) = ' '

 ! write timer itself
 total_time = Timers(TOTAL_TIMER)%total
 timer_time = Timers(timer_id)%total
 if( total_time .gt. 0.0d0 ) then
    timer_time_perc = timer_time*100.0/total_time
 else
    timer_time_perc = 0.0d0
 end if

 write(TIM_OUT,10) space(1:level*2),trim(Timers(timer_id)%title), &
                    space(1:80-22-1-len_trim(Timers(timer_id)%title)-level*2),timer_time,timer_time_perc

 ! write all childs
 do i=1,MAX_NUMBER_OF_TIMERS
    if( Timers(i)%root_id .eq. timer_id ) then
        call write_timer(i,level+1)
    end if
 end do

 return

10 format(1x,a,a,a,F12.2,4x,F6.2)

end subroutine write_timer

!===============================================================================
!-------------------------------------------------------------------------------
!===============================================================================

integer function add_timer(root_id,title)

 use smf_profiling_dat
 use smf_utils

 implicit none
 integer,intent(in)         :: root_id
 character(*),intent(in)    :: title
 ! -----------------------------------------------------------------------------

 ! put timer to array
 ! do we have empty slot
 if( TopTimer .ge. MAX_NUMBER_OF_TIMERS ) then
    call libsmf_exit(TIM_OUT,1,'>>> ERROR: Too many timers! Increase MAX_NUMBER_OF_TIMERS!')
 end if

 if( (root_id .gt. TopTimer)  .or. (root_id .lt. 0) ) then
    call libsmf_exit(TIM_OUT,1,'>>> ERROR: Illegal timer root ID in add_timer!')
 end if

 TopTimer = TopTimer + 1
 add_timer = TopTimer

 Timers(TopTimer)%id = TopTimer
 Timers(TopTimer)%root_id = root_id 
 Timers(TopTimer)%title = title 

end function add_timer

!===============================================================================
!-------------------------------------------------------------------------------
!===============================================================================

subroutine start_timer(timer_id)

 use smf_profiling_dat
 use smf_utils

 implicit none
 integer,intent(in)    :: timer_id
 ! -----------------------------------------------------------------------------

 if( (timer_id .gt. TopTimer)  .or. (timer_id .le. 0) ) then
    write(TIM_OUT,10) timer_id
    call libsmf_exit(TIM_OUT,1,'>>> ERROR: Illegal timer_id in start_timer!')
 end if

 if( Timers(timer_id)%started .eqv. .true. ) then
    write(TIM_OUT,20) timer_id,trim(Timers(timer_id)%title)
    call libsmf_exit(TIM_OUT,1,'>>> ERROR: Timer is already started!')
 end if

 Timers(timer_id)%started = .true.
 Timers(timer_id)%start = rtime()

 return

 10 format('>>> TIMER START: Timer ID ',I6,' is not legal!')
 20 format('>>> TIMER START: Timer ',I6,' (',A,') was already started!')

end subroutine start_timer

!===============================================================================
!-------------------------------------------------------------------------------
!===============================================================================

subroutine stop_timer(timer_id)

 use smf_profiling_dat
 use smf_utils

 implicit none
 integer,intent(in)    :: timer_id
 ! -----------------------------------------------------------------------------

 if( (timer_id .gt. TopTimer)  .or. (timer_id .le. 0) ) then
    write(TIM_OUT,10) timer_id
    call libsmf_exit(TIM_OUT,1,'>>> ERROR: Illegal timer_id in stop_timer!')
 end if

 if( Timers(timer_id)%started .eqv. .false. ) then
    write(TIM_OUT,20) timer_id,trim(Timers(timer_id)%title)
    call libsmf_exit(TIM_OUT,1,'>>> ERROR: Timer was not started!')
 end if

 Timers(timer_id)%started = .false.
 Timers(timer_id)%total = Timers(timer_id)%total + rtime() - Timers(timer_id)%start
 Timers(timer_id)%start = 0.0

 return

 10 format('>>> TIMER STOP: Timer ID ',I6,' is not legal!')
 20 format('>>> TIMER STOP: Timer ',I6,' (',A,') was not started!')

end subroutine stop_timer

!===============================================================================
!-------------------------------------------------------------------------------
!===============================================================================

subroutine step_timing(istep,nsteps)

 use smf_profiling_dat
 use smf_utils

 implicit none
 integer,intent(in) :: istep
 integer,intent(in) :: nsteps
 ! -----------------------------------------------
 real(SMFDP)           :: start_time
 real(SMFDP)           :: current_time
 real(SMFDP)           :: time_per_step
 real(SMFDP)           :: time_completion
 ! -----------------------------------------------------------------------------

 if( istep > 0 ) then
    ! print timing info
    start_time = Timers(TOTAL_TIMER)%start
    current_time = rtime()
    time_per_step = (current_time-start_time)/istep
    time_completion = time_per_step*(nsteps-istep)/60
    write(TIM_OUT,10) time_per_step, time_completion
 end if

 return

10 format('Time per step: ',f7.2,' [s]               Estimated completion in: ',f8.2,' [min]')

end subroutine step_timing

!===============================================================================
!-------------------------------------------------------------------------------
!===============================================================================

end module smf_profiling
