# ==============================================================================
# SciMaFic CMake File
# ==============================================================================

INCLUDE_DIRECTORIES(lib/cscimafic/maths SYSTEM)
INCLUDE_DIRECTORIES(lib/cscimafic/files SYSTEM)
INCLUDE_DIRECTORIES(lib/cscimafic/chemistry SYSTEM)
INCLUDE_DIRECTORIES(lib/cscimafic/physics SYSTEM)

# include subdirectories -------------------------------------------------------
ADD_SUBDIRECTORY(lib)
