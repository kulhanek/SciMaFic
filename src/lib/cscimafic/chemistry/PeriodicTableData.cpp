//==============================================================================
//    Copyright 2008      Jakub Stepan
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

#include <PeriodicTable.hpp>
#include <SmallColor.hpp>

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

const char* CPeriodicTable::Symbols[] = {
    "Vir",
    "H",
    "He",
    "Li",
    "Be",
    "B",
    "C",
    "N",
    "O",
    "F",
    "Ne",
    "Na",
    "Mg",
    "Al",
    "Si",
    "P",
    "S",
    "Cl",
    "Ar",
    "K",
    "Ca",
    "Sc",
    "Ti",
    "V",
    "Cr",
    "Mn",
    "Fe",
    "Co",
    "Ni",
    "Cu",
    "Zn",
    "Ga",
    "Ge",
    "As",
    "Se",
    "Br",
    "Kr",
    "Rb",
    "Sr",
    "Y",
    "Zr",
    "Nb",
    "Mo",
    "Tc",
    "Ru",
    "Rh",
    "Pd",
    "Ag",
    "Cd",
    "In",
    "Sn",
    "Sb",
    "Te",
    "I",
    "Xe",
    "Cs",
    "Ba",
    "La",
    "Ce",
    "Pr",
    "Nd",
    "Pm",
    "Sm",
    "Eu",
    "Gd",
    "Tb",
    "Dy",
    "Ho",
    "Er",
    "Tm",
    "Yb",
    "Lu",
    "Hf",
    "Ta",
    "W",
    "Re",
    "Os",
    "Ir",
    "Pt",
    "Au",
    "Hg",
    "Tl",
    "Pb",
    "Bi",
    "Po",
    "At",
    "Rn",
    "Fr",
    "Ra",
    "Ac",
    "Th",
    "Pa",
    "U",
    "Np",
    "Pu",
    "Am",
    "Cm",
    "Bk",
    "Cf",
    "Es",
    "Fm",
    "Md",
    "No",
    "Lr",
    "Rf"
};

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

const char* CPeriodicTable::Names[] = {
    "Virtual",
    "Hydrogen",
    "Helium",
    "Lithium",
    "Beryllium",
    "Boron",
    "Carbon",
    "Nitrogen",
    "Oxygen",
    "Fluorine",
    "Neon",
    "Sodium",
    "Magnesium",
    "Aluminium",
    "Silicon",
    "Phosphorus",
    "Sulfur",
    "Chlorine",
    "Argon",
    "Potassium",
    "Calcium",
    "Scandium",
    "Titanium",
    "Vanadium",
    "Chromium",
    "Manganese",
    "Iron",
    "Cobalt",
    "Nickel",
    "Copper",
    "Zinc",
    "Gallium",
    "Germanium",
    "Arsenic",
    "Selenium",
    "Bromine",
    "Krypton",
    "Rubidium",
    "Strontium",
    "Yttrium",
    "Zirconium",
    "Niobium",
    "Molybdenum",
    "Technetium",
    "Ruthenium",
    "Rhodium",
    "Palladium",
    "Silver",
    "Cadmium",
    "Indium",
    "Tin",
    "Antimony",
    "Tellurium",
    "Iodine",
    "Xenon",
    "Caesium",
    "Barium",
    "Lanthanum",
    "Cerium",
    "Praseodymium",
    "Neodymium",
    "Promethium",
    "Samarium",
    "Europium",
    "Gadolinium",
    "Terbium",
    "Dysprosium",
    "Holmium",
    "Erbium",
    "Thulium",
    "Ytterbium",
    "Lutetium",
    "Hafnium",
    "Tantalum",
    "Wolfram",
    "Rhenium",
    "Osmium",
    "Iridium",
    "Platinum",
    "Gold",
    "Mercury",
    "Thallium",
    "Lead",
    "Bismuth",
    "Polonium",
    "Astatine",
    "Radon",
    "Francium",
    "Radium",
    "Actinium",
    "Thorium",
    "Protactinium",
    "Uranium",
    "Neptunium",
    "Plutonium",
    "Americium",
    "Curium",
    "Berkelium",
    "Californium",
    "Einsteinium",
    "Fermium",
    "Mendelevium",
    "Nobelium",
    "Lawrencium",
    "Rutherfordium",
};

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

const float CPeriodicTable::Masses[] = {
    1.00794, // Vir
    1.00794, // H
    4.002602, // He
    6.941, //   Li
    9.012182, //Be
    10.811, //  B
    12.0107, // C
    14.0067, // N
    15.9994, // O
    18.9984032, //  F
    20.1797, // Ne
    22.98976928, // Na
    24.3050, // Mg
    26.9815386, //  Al
    28.0855, // Si
    30.973762, //   P
    32.065, //  S
    35.453, //  Cl
    39.948, //  Ar
    39.0983, // K
    40.078, //  Ca
    44.955912, //   Sc
    47.867, //  Ti
    50.9415, // V
    51.9961, // Cr
    54.938045, //   Mn
    55.845, //  Fe
    58.933195, //   Co
    58.6934, // Ni
    63.546, //  Cu
    65.38, //   Zn
    69.723, //  Ga
    72.64, //   Ge
    74.92160, //    As
    78.96, //   Se
    79.904, //  Br
    83.798, //  Kr
    85.4678, // Rb
    87.62, //   Sr
    88.90585, //    Y
    91.224, //  Zr
    92.906, //  Nb
    95.96, //   Mo
    98., // Tc
    101.07, //  Ru
    102.905, // Rh
    106.42, //  Pd
    107.8682, //    Ag
    112.411, // Cd
    114.818, // In
    118.710, // Sn
    121.760, // Sb
    127.60, //  Te
    126.904, // I
    131.293, // Xe
    132.9054519, // Cs
    137.327, // Ba
    138.90547, //   La
    140.116, // Ce
    140.90765, //   Pr
    144.242, // Nd
    145., //    Pm
    150.36, //  Sm
    151.964, // Eu
    157.25, //  Gd
    158.92535, //   Tb
    162.500, // Dy
    164.930, // Ho
    167.259, // Er
    168.93421, //   Tm
    173.054, // Yb
    174.9668, //    Lu
    178.49, //  Hf
    180.94788, //   Ta
    183.84, //  W
    186.207, // Re
    190.23, //  Os
    192.217 , //    Ir
    195.084, // Pt
    196.966569, //  Au
    200.59, //  Hg
    204.3833, //    Tl
    207.2, //   Pb
    208.98040, //   Bi
    210., //    Po
    210., //    At
    220., //    Rn
    223., //    Fr
    226., //    Ra
    227., //    Ac
    232.03806, //   Th
    231.03588, //   Pa
    238.02891   , //    U
    237., //    Np
    244., //    Pu
    243., //    Am
    247., //    Cm
    247., //    Bk
    251., //    Cf
    252., //    Es
    257., //    Fm
    258., //    Md
    259., //    No
    262., //    Lr
    261., //    Rf
};

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

const float CPeriodicTable::vdWRadii[] = {
    1.00,   // "Vir",
    1.09,   // "H",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.40,   // "He",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.82,   // "Li",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Be",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "B",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.70,   // "C",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.55,   // "N",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.52,   // "O",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.47,   // "F",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.54,   // "Ne",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.27,   // "Na",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.73,   // "Mg",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Al",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.10,   // "Si",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.80,   // "P",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.80,   // "S",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.75,   // "Cl",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.88,   // "Ar",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.75,   // "K",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Ca",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Sc",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Ti",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "V",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Cr",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Mn",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Fe",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Co",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.63,   // "Ni",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.40,   // "Cu",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.39,   // "Zn",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.87,   // "Ga",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Ge",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.85,   // "As",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.90,   // "Se",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.85,   // "Br",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.02,   // "Kr",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Rb",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Sr",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Y",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Zr",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Nb",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Mo",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Tc",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Ru",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Rh",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.63,   // "Pd",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.72,   // "Ag",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.58,   // "Cd",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.93,   // "In",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.17,   // "Sn",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Sb",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.06,   // "Te",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.98,   // "I",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.16,   // "Xe",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Cs",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Ba",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "La",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Ce",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Pr",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Nd",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Pm",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Sm",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Eu",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Gd",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Tb",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Dy",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Ho",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Er",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Tm",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Yb",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Lu",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Hf",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Ta",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "W",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Re",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Os",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Ir",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.72,   // "Pt",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.66,   // "Au",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.55,   // "Hg",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.96,   // "Tl",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.02,   // "Pb",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Bi",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Po",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "At",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Rn",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Fr",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Ra",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Ac",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Th",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Pa",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.86,   // "U",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Np",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Pu",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Am",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Cm",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Bk",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Cf",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Es",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Fm",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Md",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "No",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Lr",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    2.00,   // "Rf",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
};


//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

const float CPeriodicTable::Electronegativity[] = {
    // source: http://environmentalchemistry.com/yogi/periodic/electronegativity.html
    2.20, //   0 Vir
    2.20, //   1 H
    0.00, //   2 He
    0.98, //   3 Li
    1.57, //   4 Be
    2.04, //   5 B
    2.55, //   6 C
    3.04, //   7 N
    3.44, //   8 O
    3.98, //   9 F
    0.00, //  10 Ne
    0.93, //  11 Na
    1.31, //  12 Mg
    1.61, //  13 Al
    1.90, //  14 Si
    2.19, //  15 P
    2.58, //  16 S
    3.16, //  17 Cl
    0.00, //  18 Ar
    0.82, //  19 K
    1.00, //  20 Ca
    1.36, //  21 Sc
    1.54, //  22 Ti
    1.63, //  23 V
    1.66, //  24 Cr
    1.55, //  25 Mn
    1.83, //  26 Fe
    1.88, //  27 Co
    1.91, //  28 Ni
    1.90, //  29 Cu
    1.65, //  30 Zn
    1.81, //  31 Ga
    2.01, //  32 Ge
    2.18, //  33 As
    2.55, //  34 Se
    2.96, //  35 Br
    0.00, //  36 Kr
    0.82, //  37 Rb
    0.95, //  38 Sr
    1.22, //  39 Y
    1.33, //  40 Zr
    1.60, //  41 Nb
    2.16, //  42 Mo
    1.90, //  43 Tc
    2.20, //  44 Ru
    2.28, //  45 Rh
    2.20, //  46 Pd
    1.93, //  47 Ag
    1.69, //  48 Cd
    1.78, //  49 In
    1.96, //  50 Sn
    2.05, //  51 Sb
    2.10, //  52 Te
    2.66, //  53 I
    0.00, //  54 Xe
    0.79, //  55 Cs
    0.89, //  56 Ba
    1.10, //  57 La
    1.12, //  58 Ce
    1.13, //  59 Pr
    1.14, //  60 Nd
    1.13, //  61 Pm
    1.17, //  62 Sm
    1.20, //  63 Eu
    1.20, //  64 Gd
    1.20, //  65 Tb
    1.22, //  66 Dy
    1.23, //  67 Ho
    1.24, //  68 Er
    1.25, //  69 Tm
    1.10, //  70 Yb
    1.27, //  71 Lu
    1.30, //  72 Hf
    1.50, //  73 Ta
    2.36, //  74 W
    1.90, //  75 Re
    2.20, //  76 Os
    2.20, //  77 Ir
    2.28, //  78 Pt
    2.54, //  79 Au
    2.00, //  80 Hg
    2.04, //  81 Tl
    2.33, //  82 Pb
    2.02, //  83 Bi
    2.00, //  84 Po
    2.20, //  85 At
    0.00, //  86 Rn
    0.70, //  87 Fr
    0.90, //  88 Ra
    1.10, //  89 Ac
    1.30, //  90 Th
    1.50, //  91 Pa
    1.38, //  92 U
    1.36, //  93 Np
    1.28, //  94 Pu
    1.30, //  95 Am
    1.30, //  96 Cm
    1.30, //  97 Bk
    1.30, //  98 Cf
    1.30, //  99 Es
    1.30, // 100 Fm
    1.30, // 101 Md
    1.30, // 102 No
    1.30, // 103 Lr
    1.30  // 104 Rf
};

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

const float CPeriodicTable::CovalentRadii[] = {
    0.23,   // "Vir",   http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    0.23,   // "H",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.50,   // "He",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    0.68,   // "Li",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    0.35,   // "Be",    http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    0.83,   // "B",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    0.68,   // "C",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    0.68,   // "N",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    0.68,   // "O",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    0.64,   // "F",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.50,   //"Ne",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    0.97,   //"Na",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.10,   //"Mg",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.35,   //"Al",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.20,   //"Si",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.05,   //"P",      http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.02,   //"S",      http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    0.99,   //"Cl",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.51,   //"Ar",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.33,   //"K",      http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    0.99,   //"Ca",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.44,   //"Sc",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.47,   //"Ti",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.33,   //"V",      http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.35,   //"Cr",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.35,   //"Mn",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.34,   //"Fe",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.33,   //"Co",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.50,   //"Ni",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.52,   //"Cu",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.45,   //"Zn",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.22,   //"Ga",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.17,   //"Ge",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.21,   //"As",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.22,   //"Se",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.21,   //"Br",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.50,   //"Kr",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.47,   //"Rb",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.12,   //"Sr",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.78,   //"Y",      http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.56,   //"Zr",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.48,   //"Nb",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.47,   //"Mo",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.35,   //"Tc",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.40,   //"Ru",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.45,   //"Rh",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.50,   //"Pd",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.59,   //"Ag",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.69,   //"Cd",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.63,   //"In",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.46,   //"Sn",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.46,   //"Sb",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.47,   //"Te",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.40,   //"I",      http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.50,   //"Xe",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.67,   //"Cs",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.34,   //"Ba",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.87,   //"La",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.83,   //"Ce",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.82,   //"Pr",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.81,   //"Nd",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.80,   //"Pm",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.80,   //"Sm",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.99,   //"Eu",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.79,   //"Gd",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.76,   //"Tb",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.75,   //"Dy",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.74,   //"Ho",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.73,   //"Er",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.72,   //"Tm",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.94,   //"Yb",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.72,   //"Lu",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.57,   //"Hf",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.43,   //"Ta",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.37,   //"W",      http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.35,   //"Re",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.37,   //"Os",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.32,   //"Ir",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.50,   //"Pt",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.50,   //"Au",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.70,   //"Hg",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.55,   //"Tl",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.54,   //"Pb",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.54,   //"Bi",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.68,   //"Po",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.21,   //"At",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.50,   //"Rn",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.50,   //"Fr",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.90,   //"Ra",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.88,   //"Ac",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.79,   //"Th",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.61,   //"Pa",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.58,   //"U",      http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.55,   //"Np",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.53,   //"Pu",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.51,   //"Am",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    0.99,   //"Cm",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.54,   //"Bk",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.83,   //"Cf",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.50,   //"Es",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.50,   //"Fm",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.50,   //"Md",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.50,   //"No",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.50,   //"Lr",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
    1.50,   //"Rf",     http://www.ccdc.cam.ac.uk./products/csd/radii/table.php4#symbol
};

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

const CSmallColor<float> CPeriodicTable::Color[] = {
    CSmallColor<float>(0.0,0.5,0.0),  // "Vir",
    CSmallColor<float>(0.0,0.2,0.0),  // "H",
    CSmallColor<float>(0.0,0.0,0.0),  // "He",
    CSmallColor<float>(0.4,0.0,0.3),  // "Li",
    CSmallColor<float>(0.4,0.0,0.3),  // "Be",
    CSmallColor<float>(0.4,0.0,0.3),  // "B",
    CSmallColor<float>(0.4,0.0,0.3),  // "C",
    CSmallColor<float>(0.4,0.0,0.3),  // "N",
    CSmallColor<float>(0.6,0.0,0.0),  // "O",
    CSmallColor<float>(0.4,0.0,0.3),  //"F",
    CSmallColor<float>(0.4,0.0,0.3),  //"Ne",
    CSmallColor<float>(0.4,0.0,0.3),  //"Na",
    CSmallColor<float>(0.4,0.0,0.3),  //"Mg",
    CSmallColor<float>(0.4,0.0,0.3),  //"Al",
    CSmallColor<float>(0.4,0.0,0.3),  //"Si",
    CSmallColor<float>(0.4,0.0,0.3),  //"P",
    CSmallColor<float>(0.4,0.0,0.3),  //"S",
    CSmallColor<float>(0.4,0.0,0.3),  //"Cl",
    CSmallColor<float>(0.4,0.0,0.3),  //"Ar",
    CSmallColor<float>(0.4,0.0,0.3),  //"K",
    CSmallColor<float>(0.5,0.0,0.0),  //"Ca",
    CSmallColor<float>(0.4,0.0,0.3),  //"Sc",
    CSmallColor<float>(0.4,0.0,0.3),  //"Ti",
    CSmallColor<float>(0.4,0.0,0.3),  //"V",
    CSmallColor<float>(0.4,0.0,0.3),  //"Cr",
    CSmallColor<float>(0.4,0.0,0.3),  //"Mn",
    CSmallColor<float>(0.4,0.0,0.3),  //"Fe",
    CSmallColor<float>(0.4,0.0,0.3),  //"Co",
    CSmallColor<float>(0.4,0.0,0.3),  //"Ni",
    CSmallColor<float>(0.4,0.0,0.3),  //"Cu",
    CSmallColor<float>(0.4,0.0,0.3),  //"Zn",
    CSmallColor<float>(0.4,0.0,0.3),  //"Ga",
    CSmallColor<float>(0.4,0.0,0.3),  //"Ge",
    CSmallColor<float>(0.4,0.0,0.3),  //"As",
    CSmallColor<float>(0.4,0.0,0.3),  //"Se",
    CSmallColor<float>(0.4,0.0,0.3),  //"Br",
    CSmallColor<float>(0.4,0.0,0.3),  //"Kr",
    CSmallColor<float>(0.4,0.0,0.3),  //"Rb",
    CSmallColor<float>(0.4,0.0,0.3),  //"Sr",
    CSmallColor<float>(0.4,0.0,0.3),  //"Y",
    CSmallColor<float>(0.4,0.0,0.3),  //"Zr",
    CSmallColor<float>(0.4,0.0,0.3),  //"Nb",
    CSmallColor<float>(0.4,0.0,0.3),  //"Mo",
    CSmallColor<float>(0.4,0.0,0.3),  //"Tc",
    CSmallColor<float>(0.4,0.0,0.3),  //"Ru",
    CSmallColor<float>(0.4,0.0,0.3),  //"Rh",
    CSmallColor<float>(0.4,0.0,0.3),  //"Pd",
    CSmallColor<float>(0.4,0.0,0.3),  //"Ag",
    CSmallColor<float>(0.4,0.0,0.3),  //"Cd",
    CSmallColor<float>(0.4,0.0,0.3),  //"In",
    CSmallColor<float>(0.4,0.0,0.3),  //"Sn",
    CSmallColor<float>(0.4,0.0,0.3),  //"Sb",
    CSmallColor<float>(0.4,0.0,0.3),  //"Te",
    CSmallColor<float>(0.4,0.0,0.3),  //"I",
    CSmallColor<float>(0.4,0.0,0.3),  //"Xe",
    CSmallColor<float>(0.4,0.0,0.3),  //"Cs",
    CSmallColor<float>(0.4,0.0,0.3),  //"Ba",
    CSmallColor<float>(0.4,0.0,0.3),  //"La",
    CSmallColor<float>(0.4,0.0,0.3),  //"Ce",
    CSmallColor<float>(0.4,0.0,0.3),  //"Pr",
    CSmallColor<float>(0.4,0.0,0.3),  //"Nd",
    CSmallColor<float>(0.4,0.0,0.3),  //"Pm",
    CSmallColor<float>(0.4,0.0,0.3),  //"Sm",
    CSmallColor<float>(0.4,0.0,0.3),  //"Eu",
    CSmallColor<float>(0.4,0.0,0.3),  //"Gd",
    CSmallColor<float>(0.4,0.0,0.3),  //"Tb",
    CSmallColor<float>(0.4,0.0,0.3),  //"Dy",
    CSmallColor<float>(0.3,0.0,0.4),  //"Ho",
    CSmallColor<float>(0.4,0.0,0.3),  //"Er",
    CSmallColor<float>(0.4,0.0,0.3),  //"Tm",
    CSmallColor<float>(0.4,0.0,0.3),  //"Yb",
    CSmallColor<float>(0.4,0.0,0.3),  //"Lu",
    CSmallColor<float>(0.4,0.0,0.3),  //"Hf",
    CSmallColor<float>(0.4,0.0,0.3),  //"Ta",
    CSmallColor<float>(0.4,0.0,0.3),  //"W",
    CSmallColor<float>(0.4,0.0,0.3),  //"Re",
    CSmallColor<float>(0.4,0.0,0.3),  //"Os",
    CSmallColor<float>(0.4,0.0,0.3),  //"Ir",
    CSmallColor<float>(0.4,0.0,0.3),  //"Pt",
    CSmallColor<float>(0.4,0.0,0.3),  //"Au",
    CSmallColor<float>(0.4,0.0,0.3),  //"Hg",
    CSmallColor<float>(0.4,0.0,0.3),  //"Tl",
    CSmallColor<float>(0.4,0.0,0.3),  //"Pb",
    CSmallColor<float>(0.4,0.0,0.3),  //"Bi",
    CSmallColor<float>(0.4,0.0,0.3),  //"Po",
    CSmallColor<float>(0.4,0.0,0.3),  //"At",
    CSmallColor<float>(0.4,0.0,0.3),  //"Rn",
    CSmallColor<float>(0.4,0.0,0.3),  //"Fr",
    CSmallColor<float>(0.4,0.0,0.3),  //"Ra",
    CSmallColor<float>(0.4,0.0,0.3),  //"Ac",
    CSmallColor<float>(0.4,0.0,0.3),  //"Th",
    CSmallColor<float>(0.4,0.0,0.3),  //"Pa",
    CSmallColor<float>(0.4,0.0,0.3),  //"U",
    CSmallColor<float>(0.4,0.0,0.3),  //"Np",
    CSmallColor<float>(0.4,0.0,0.3),  //"Pu",
    CSmallColor<float>(0.4,0.0,0.3),  //"Am",
    CSmallColor<float>(0.4,0.0,0.3),  //"Cm",
    CSmallColor<float>(0.4,0.0,0.3),  //"Bk",
    CSmallColor<float>(0.4,0.0,0.3),  //"Cf",
    CSmallColor<float>(0.4,0.0,0.3),  //"Es",
    CSmallColor<float>(0.4,0.0,0.3),  //"Fm",
    CSmallColor<float>(0.4,0.0,0.3),  //"Md",
    CSmallColor<float>(0.4,0.0,0.3),  //"No",
    CSmallColor<float>(0.4,0.0,0.3),  //"Lr",
    CSmallColor<float>(0.4,0.0,0.3),  //"Ku"
};

//==============================================================================
//------------------------------------------------------------------------------
//==============================================================================

