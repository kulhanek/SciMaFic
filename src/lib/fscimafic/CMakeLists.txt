# ==============================================================================
# SciMaFic CMake File
# ==============================================================================

# objects in library -----------------------------------------------------------
SET(FSCIMAFIC_SRC
        sizes.f90
        constants.f90

    # miscellaneous ------------------------------
        misc/utils.f90
        misc/profiling_dat.f90
        misc/profiling_types.f90
        misc/profiling.f90

    # chemistry ----------------------------------
        chemistry/periodic_table_dat.f90
        chemistry/periodic_table.f90

    # physics ----------------------------------
        physics/physical_constants.f90

    # files --------------------------------------
        files/xyzfile_type.f90
        files/xyzfile.f90
        )

# create static library --------------------------------------------------------
IF(LIBS_STATIC)
    ADD_LIBRARY(fscimafic_static STATIC ${FSCIMAFIC_SRC})
    SET_TARGET_PROPERTIES(fscimafic_static PROPERTIES
                            OUTPUT_NAME fscimafic
                            CLEAN_DIRECT_OUTPUT 1)
ENDIF(LIBS_STATIC)

# create shared library --------------------------------------------------------
IF(LIBS_SHARED)
    ADD_LIBRARY(fscimafic_shared SHARED ${FSCIMAFIC_SRC})
    SET_TARGET_PROPERTIES(fscimafic_shared PROPERTIES
                            OUTPUT_NAME fscimafic
                            CLEAN_DIRECT_OUTPUT 1
                            VERSION ${SCIMAFIC_VERSION})
    INSTALL(TARGETS fscimafic_shared
            DESTINATION lib)
ENDIF(LIBS_SHARED)

