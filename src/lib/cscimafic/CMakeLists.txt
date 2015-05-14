# ==============================================================================
# SciMaFic CMake File
# ==============================================================================

# objects in library -----------------------------------------------------------
SET(CSCIMAFIC_SRC
        SciMaFicMainHeader.cpp

    # maths --------------------------------------
        maths/DynamicArray.cpp
        maths/SimplePoint.cpp
        maths/Point.cpp
        maths/SimpleVector.cpp
        maths/Vector.cpp
        maths/SimpleSquareMatrix.cpp
        maths/Matrix.cpp
        maths/SimpleTransformation.cpp
        maths/Transformation.cpp
        maths/FortranRow.cpp
        maths/FortranMatrix.cpp

    # files --------------------------------------
        files/XYZGradient.cpp
        files/XYZHessian.cpp
        files/XYZStructure.cpp

    # chemistry ----------------------------------
        chemistry/Element.cpp
        chemistry/PeriodicTable.cpp
        chemistry/PeriodicTableData.cpp
        )

IF(LAPACK_ENABLED)
    SET(CSCIMAFIC_SRC ${CSCIMAFIC_SRC}

    # maths --------------------------------------
        maths/Lapack.cpp

    # physics ------------------------------------
        physics/PrincipalAxes.cpp
    )
ENDIF(LAPACK_ENABLED)

# create static library --------------------------------------------------------
IF(LIBS_STATIC)
    ADD_LIBRARY(cscimafic_static STATIC ${CSCIMAFIC_SRC})
    SET_TARGET_PROPERTIES(cscimafic_static PROPERTIES
                            OUTPUT_NAME cscimafic
                            CLEAN_DIRECT_OUTPUT 1)
ENDIF(LIBS_STATIC)

# create shared library --------------------------------------------------------
IF(LIBS_SHARED)
    ADD_DEFINITIONS(-DSCIMAFIC_BUILDING_DLL)
    ADD_LIBRARY(cscimafic_shared SHARED ${CSCIMAFIC_SRC})
    TARGET_LINK_LIBRARIES(cscimafic_shared ${SYSTEM_LIBS})
    SET_TARGET_PROPERTIES(cscimafic_shared PROPERTIES
                            OUTPUT_NAME cscimafic
                            CLEAN_DIRECT_OUTPUT 1
                            VERSION ${SCIMAFIC_VERSION})
    INSTALL(TARGETS cscimafic_shared
            DESTINATION lib)
ENDIF(LIBS_SHARED)

