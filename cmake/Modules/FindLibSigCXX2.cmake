# - Try to find libsigc++-2.0
# Once done this will define
#
#  LIBSIGCXX2_FOUND - System has libsigc++2
#  LIBSIGCXX2_INCLUDE_DIRS - The libsigc++2 include directories
#  LIBSIGCXX2_LIBRARIES - The libraries needed to use libsigc++2

# Copyright (c) 2008, Michael Wild <themiwi at users.sf.net>
#
# Redistribution and use is allowed according to the terms of the BSD  
# license.

if (NOT WIN32)
   # use pkg-config to get the directories and then use these values
   # in the FIND_PATH() and FIND_LIBRARY() calls
   find_package( PkgConfig REQUIRED )
   pkg_check_modules( _sigcxx2  REQUIRED sigc++-2.0 )
endif (NOT WIN32)

# find sigc++/sigc++.h
find_path( LIBSIGCXX2_sigcxx_h_DIR sigc++/sigc++.h
   PATHS ${_sigcxx2_INCLUDE_DIRS}
   PATH_SUFFIXES sigc++-2.0
   DOC "Include directory for sigc++.h"
   )

# find sigc++config.h
find_path( LIBSIGCXX2_sigcxxconfig_h_DIR sigc++config.h
   /usr/include/libsigc++-2.0/include
   PATHS ${_sigcxx2_INCLUDE_DIRS}
   DOC "Include directory for sigc++config.h"
   )

# combine the two paths
set( LIBSIGCXX2_INCLUDE_DIRS ${LIBSIGCXX2_sigcxx_h_DIR} ${LIBSIGCXX2_sigcxxconfig_h_DIR} )

# find the sigc-2.0 library
find_library( LIBSIGCXX2_LIBRARIES
   NAMES sigc-2.0 ${_sigcxx2_LIBRARIES}
   PATHS ${_sigcxx2_LIBRARY_DIRS}
   DOC "Libraries for libsigc++2"
   )

# let find_package_handle_standard_args handle all the boilerplate stuff
include( FindPackageHandleStandardArgs )
find_package_handle_standard_args(
   LibSigCXX2 LIBSIGCXX2_LIBRARIES LIBSIGCXX2_sigcxx_h_DIR  
   LIBSIGCXX2_sigcxxconfig_h_DIR
   )

# mark these cache entries as advanced
mark_as_advanced( LIBSIGCXX2_LIBRARIES LIBSIGCXX2_sigcxx_h_DIR
   LIBSIGCXX2_sigcxxconfig_h_DIR LIBSIGCXX2_INCLUDE_DIR
   )

