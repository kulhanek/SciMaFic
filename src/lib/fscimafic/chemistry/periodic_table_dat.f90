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

module smf_periodic_table_dat

use smf_sizes

implicit none

! ------------------------------------------------------------------------------

integer,parameter           :: CPT_NELEMENTS = 110

! symbols ----------------------------------------------------------------------
character(SMF_MAX_SYMBOL)   :: pt_symbols(CPT_NELEMENTS) = (/ &
    'H '    , 'He'    , 'Li'    , 'Be'    , 'B '    , 'C '    , 'N '    , 'O '    , 'F '    , 'Ne'    ,  &
    'Na'    , 'Mg'    , 'Al'    , 'Si'    , 'P '    , 'S '    , 'Cl'    , 'Ar'    , 'K '    , 'Ca'    ,  &
    'Sc'    , 'Ti'    , 'V '    , 'Cr'    , 'Mn'    , 'Fe'    , 'Co'    , 'Ni'    , 'Cu'    , 'Zn'    ,  &
    'Ga'    , 'Ge'    , 'As'    , 'Se'    , 'Br'    , 'Kr'    , 'Rb'    , 'Sr'    , 'Y '    , 'Zr'    ,  &
    'Nb'    , 'Mo'    , 'Tc'    , 'Ru'    , 'Rh'    , 'Pd'    , 'Ag'    , 'Cd'    , 'In'    , 'Sn'    ,  &
    'Sb'    , 'Te'    , 'I '    , 'Xe'    , 'Cs'    , 'Ba'    , 'La'    , 'Ce'    , 'Pr'    , 'Nd'    ,  &
    'Pm'    , 'Sm'    , 'Eu'    , 'Gd'    , 'Tb'    , 'Dy'    , 'Ho'    , 'Er'    , 'Tm'    , 'Yb'    ,  &
    'Lu'    , 'Hf'    , 'Ta'    , 'W '    , 'Re'    , 'Os'    , 'Ir'    , 'Pt'    , 'Au'    , 'Hg'    ,  &
    'Tl'    , 'Pb'    , 'Bi'    , 'Po'    , 'At'    , 'Rn'    , 'Fr'    , 'Ra'    , 'Ac'    , 'Th'    ,  &
    'Pa'    , 'U '    , 'Np'    , 'Pu'    , 'Am'    , 'Cm'    , 'Bk'    , 'Cf'    , 'Es'    , 'Fm'    ,  &
    'Md'    , 'No'    , 'Lr'    , 'Ku'    , '  '    , '  '    , '  '    , '  '    , '  '    , '  '       /)

! masses -----------------------------------------------------------------------
real(SMFDP)                 :: pt_masses(CPT_NELEMENTS) = (/ &
     1.00790,  4.00260,  6.94100,  9.01218, 10.81100, 12.01100, 14.00670, 15.99940, 18.99840, 20.17970,  &
    22.98977, 24.30500, 26.98154, 28.08550, 30.97376, 32.06400, 34.96885, 39.94800, 39.09830, 40.07800,  &
    44.95591, 47.86700, 50.94150, 51.99610, 54.93800, 55.84500, 58.93320, 58.69340, 63.54600, 65.38000,  &
    69.72300, 72.64000, 74.92160, 78.96000, 79.90400, 83.79800, 85.46780, 87.62000, 88.90585, 91.22400,  &
    92.90600, 95.96000, 98.00000,101.07000,102.90500,106.42000,107.86820,112.41100,114.81800,118.71000,  &
   121.76000,127.60000,126.90400,131.29300,132.90545,137.32700,138.90547,140.11600,140.90765,144.24200,  &
   145.00000,150.36000,151.96400,157.25000,158.92535,162.50000,164.93000,167.25900,168.93421,173.05400,  &
   174.96680,178.49000,180.94788,183.84000,186.20700,190.23000,192.21700,194.96480,196.96657,200.59000,  &
   204.38330,207.20000,208.98040,210.00000,210.00000,220.00000,223.00000,226.00000,227.00000,232.03806,  &
   231.03588,238.02891,237.00000,244.00000,243.00000,247.00000,247.00000,251.00000,252.00000,257.00000,  &
   258.00000,259.00000,262.00000,261.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000,  0.00000   /)
! ------------------------------------------------------------------------------

end module smf_periodic_table_dat
