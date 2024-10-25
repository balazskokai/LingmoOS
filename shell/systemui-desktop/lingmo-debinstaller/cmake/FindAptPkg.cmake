# - find Library for managing Debian package information
# APTPKG_INCLUDE_DIR - Where to find Library for managing Debian package information header files (directory)
# APTPKG_LIBRARIES - Library for managing Debian package information libraries
# APTPKG_LIBRARY_RELEASE - Where the release library is
# APTPKG_LIBRARY_DEBUG - Where the debug library is
# APTPKG_FOUND - Set to TRUE if we found everything (library, includes and executable)

# Copyright (c) 2010 David Palacio, <dpalacio@uninorte.edu.co>
#
# Redistribution and use is allowed according to the terms of the BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#
# Generated by CModuler, a CMake Module Generator - http://gitorious.org/cmoduler

include(FindPackageHandleStandardArgs)

IF( APTPKG_INCLUDE_DIR AND APTPKG_LIBRARY_RELEASE AND APTPKG_LIBRARY_DEBUG )
    SET(APTPKG_FIND_QUIETLY TRUE)
ENDIF( APTPKG_INCLUDE_DIR AND APTPKG_LIBRARY_RELEASE AND APTPKG_LIBRARY_DEBUG )

FIND_PATH( APTPKG_INCLUDE_DIR apt-pkg/init.h  )

FIND_LIBRARY(APTPKG_LIBRARY_RELEASE NAMES apt-pkg )
FIND_LIBRARY(APTINST_LIBRARY NAMES apt-inst )

# apt-inst is optional these days!
IF ( NOT APTINST_LIBRARY )
    SET( APTINST_LIBRARY "" )
ENDIF( )

FIND_LIBRARY(APTPKG_LIBRARY_DEBUG NAMES apt-pkg apt-pkgd  HINTS /usr/lib/debug/usr/lib/ )

IF( APTPKG_LIBRARY_RELEASE OR APTPKG_LIBRARY_DEBUG AND APTPKG_INCLUDE_DIR )
    SET( APTPKG_FOUND TRUE )
ENDIF( APTPKG_LIBRARY_RELEASE OR APTPKG_LIBRARY_DEBUG AND APTPKG_INCLUDE_DIR )

IF( APTPKG_LIBRARY_DEBUG AND APTPKG_LIBRARY_RELEASE )
    # if the generator supports configuration types then set
    # optimized and debug libraries, or if the CMAKE_BUILD_TYPE has a value
    IF( CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE )
        SET( APTPKG_LIBRARIES optimized ${APTPKG_LIBRARY_RELEASE} ${APTINST_LIBRARY} debug ${APTPKG_LIBRARY_DEBUG} )
    ELSE( CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE )
    # if there are no configuration types and CMAKE_BUILD_TYPE has no value
    # then just use the release libraries
        SET( APTPKG_LIBRARIES ${APTPKG_LIBRARY_RELEASE} ${APTINST_LIBRARY} )
    ENDIF( CMAKE_CONFIGURATION_TYPES OR CMAKE_BUILD_TYPE )
ELSEIF( APTPKG_LIBRARY_RELEASE )
    SET( APTPKG_LIBRARIES ${APTPKG_LIBRARY_RELEASE} ${APTINST_LIBRARY})
ELSE( APTPKG_LIBRARY_DEBUG AND APTPKG_LIBRARY_RELEASE )
    SET( APTPKG_LIBRARIES ${APTPKG_LIBRARY_DEBUG} ${APTINST_LIBRARY} )
ENDIF( APTPKG_LIBRARY_DEBUG AND APTPKG_LIBRARY_RELEASE )

find_package_handle_standard_args(AptPkg DEFAULT_MSG APTPKG_LIBRARIES APTPKG_INCLUDE_DIR)
