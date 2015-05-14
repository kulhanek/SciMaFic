# ==============================================================================
# SciMaFic CMake File
# ==============================================================================

# this is required for scimafic library ------------------------------------------
INCLUDE_DIRECTORIES(cscimafic SYSTEM)

# include subdirectories -------------------------------------------------------
ADD_SUBDIRECTORY(cscimafic)
IF(FORTRAN_ENABLED)
    ADD_SUBDIRECTORY(fscimafic)
ENDIF(FORTRAN_ENABLED)

