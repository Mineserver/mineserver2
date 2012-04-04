#
# CMake config
#
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
CMAKE_POLICY(SET CMP0014 OLD)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

#
# Project name
#
PROJECT(mineserver)

#
# Project version
#

# Get the git revision location for the branch we're on
if(EXISTS "${${PROJECT_NAME}_SOURCE_DIR}/.git/HEAD")
  file(STRINGS ${${PROJECT_NAME}_SOURCE_DIR}/.git/HEAD GIT_HEAD_LOC REGEX ".*")
  #file(GIT_HEAD_LOC ${${PROJECT_NAME}_SOURCE_DIR}/.git/HEAD REGEX ".*")
  string(LENGTH ${GIT_HEAD_LOC} HEAD_LEN)
  math(EXPR LEN "${HEAD_LEN} - 5")
  string(SUBSTRING ${GIT_HEAD_LOC} 5 ${LEN} GIT_HEAD)
endif(EXISTS "${${PROJECT_NAME}_SOURCE_DIR}/.git/HEAD")

# Get the git revision we're on for the version string
if(EXISTS "${${PROJECT_NAME}_SOURCE_DIR}/.git/${GIT_HEAD}")
  #read_from_file(${${PROJECT_NAME}_SOURCE_DIR}/.git/${GIT_HEAD} ".*" VERSION_STR)
  file(STRINGS ${${PROJECT_NAME}_SOURCE_DIR}/.git/${GIT_HEAD} VERSION_STR REGEX ".*")
  # Get the length of the string
  string(LENGTH ${VERSION_STR} VERSION_LEN)
  # Subtract 7 from the string's length
  math(EXPR VERSION_NUM_LEN "${VERSION_LEN} - ${VERSION_LEN} + 7")
  # Extract the value from the string
  string(SUBSTRING ${VERSION_STR} 0 ${VERSION_NUM_LEN} VERSION_GIT)
endif(EXISTS "${${PROJECT_NAME}_SOURCE_DIR}/.git/${GIT_HEAD}")

# Set the actual version strings, these are used inside the program later
SET(${PROJECT_NAME}_MAJOR_VERSION 2) # Version Major
SET(${PROJECT_NAME}_MINOR_VERSION 0) # Version Minor
SET(${PROJECT_NAME}_PATCH_LEVEL 0)   # Version patch

# the rest is automatic
SET(${PROJECT_NAME}_VERSION_SIMPLE "${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_LEVEL}")
SET(${PROJECT_NAME}_VERSION_COMPLETE "${${PROJECT_NAME}_VERSION_SIMPLE}-${VERSION_GIT}")

#
# set default build to Debug
#
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug
    CACHE STRING "Choose the type of build, options are: Debug, Profile, Release"
    FORCE
  )
ENDIF()

# Add an optional variable for using run-cc.pl for building, Perl will be checked below regardless of this setting
option(USE_RUN_CC_PL "Use run-cc.pl for building" ON)

#
# Find perl for run-cc.pl
#
find_program(PERL perl)

#
# Use run-cc.pl
#
if(PERL AND USE_RUN_CC_PL)
  set(CMAKE_CXX_COMPILE_OBJECT "${PERL} ${${PROJECT_NAME}_SOURCE_DIR}/run-cc.pl -q ${CMAKE_CXX_COMPILE_OBJECT}")
  set(CMAKE_CXX_LINK_EXECUTABLE "${PERL} ${${PROJECT_NAME}_SOURCE_DIR}/run-cc.pl -q ${CMAKE_CXX_LINK_EXECUTABLE}")
  set(CMAKE_CXX_CREATE_SHARED_MODULE "${PERL} ${${PROJECT_NAME}_SOURCE_DIR}/run-cc.pl -q ${CMAKE_CXX_CREATE_SHARED_MODULE}")
endif(PERL AND USE_RUN_CC_PL)

#
# Configure paths
#
SET(CONFIG_DIR_BIN bin/)
SET(CONFIG_DIR_ETC etc/${PROJECT_NAME}/)
SET(CONFIG_DIR_LIB lib/${PROJECT_NAME}/)

SET(EXECUTABLE_OUTPUT_PATH bin)
SET(LIBRARY_OUTPUT_PATH bin)

#
# Set compiler specific build flags
#

# g++
IF(CMAKE_COMPILER_IS_GNUCXX)
  SET(CMAKE_CXX_FLAGS "-W -Wall -Wno-unused")
  SET(CMAKE_CXX_FLAGS_DEBUG "-DDEBUG -O0 -g")
  SET(CMAKE_CXX_FLAGS_PROFILE "-DDEBUG -g -pg")
  SET(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -O3 -s")
ENDIF()

# msvc++
IF(MSVC_IDE)
  SET(CMAKE_CXX_FLAGS "/DWIN32 /D_CONSOLE /DZLIB_WINAPI /fp:fast /EHsc")
  SET(CMAKE_CXX_FLAGS_DEBUG "/DDEBUG /D_DEBUG /MTd /Zi")
  SET(CMAKE_CXX_FLAGS_RELEASE "/MT /D_SECURE_SCL=0")
ENDIF(MSVC_IDE)

# used for the functions below
include(CheckFunctionExists)
include(CheckIncludeFile)
include(CheckTypeSize)
include(CheckLibraryExists)
include(CheckCXXCompilerFlag)

# functions/includes needed during compile
check_function_exists(backtrace HAVE_BACKTRACE)
check_include_file(sys/utsname.h HAVE_SYS_UTSNAME_H)

# our system specific configuration file :P
configure_file(${${PROJECT_NAME}_SOURCE_DIR}/src/sysconfig.h.cmake ${${PROJECT_NAME}_SOURCE_DIR}/src/mineserver/sysconfig.h)

FIND_PACKAGE(Boost COMPONENTS system filesystem signals thread REQUIRED)
FIND_PACKAGE(ZLIB)
FIND_PACKAGE(Iconv)
FIND_PACKAGE(Threads)
FIND_PACKAGE(Noise)

#
# Justasic: TODO: this mess with all the sources needs to be cleaned up into a CMake list compile..
# because making a static list of files is lame and gay.
#

SET(mineserver_source
  src/app.cpp
  src/mineserver/nbt.cpp
  src/mineserver/game.cpp
  src/mineserver/signal.cpp
  src/mineserver/game/player.cpp
  src/mineserver/game/command.cpp
  src/mineserver/localization.cpp
  src/mineserver/network/server.cpp
  src/mineserver/network/client.cpp
  src/mineserver/world/generator/mapgen.cpp
  src/mineserver/world/generator/terrain.cpp
  src/mineserver/world/generator/boime.cpp
  src/mineserver/world/generator/cavegen.cpp
  src/mineserver/world/generator/objectgen.cpp
  src/mineserver/world/generator/collision.cpp
  # These need to be put into a separate .so file or something...
  src/mineserver/network/protocol/notch/protocol.cpp
  src/mineserver/network/protocol/notch/packetstream.cpp
  src/mineserver/network/protocol/notch/packet/0x00.cpp
  src/mineserver/network/protocol/notch/packet/0x01.cpp
  src/mineserver/network/protocol/notch/packet/0x02.cpp
  src/mineserver/network/protocol/notch/packet/0x03.cpp
  src/mineserver/network/protocol/notch/packet/0x04.cpp
  src/mineserver/network/protocol/notch/packet/0x05.cpp
  src/mineserver/network/protocol/notch/packet/0x06.cpp
  src/mineserver/network/protocol/notch/packet/0x07.cpp
  src/mineserver/network/protocol/notch/packet/0x08.cpp
  src/mineserver/network/protocol/notch/packet/0x09.cpp
  src/mineserver/network/protocol/notch/packet/0x0A.cpp
  src/mineserver/network/protocol/notch/packet/0x0B.cpp
  src/mineserver/network/protocol/notch/packet/0x0C.cpp
  src/mineserver/network/protocol/notch/packet/0x0D.cpp
  src/mineserver/network/protocol/notch/packet/0x0E.cpp
  src/mineserver/network/protocol/notch/packet/0x0F.cpp
  src/mineserver/network/protocol/notch/packet/0x10.cpp
  src/mineserver/network/protocol/notch/packet/0x11.cpp
  src/mineserver/network/protocol/notch/packet/0x12.cpp
  src/mineserver/network/protocol/notch/packet/0x13.cpp
  src/mineserver/network/protocol/notch/packet/0x14.cpp
  src/mineserver/network/protocol/notch/packet/0x15.cpp
  src/mineserver/network/protocol/notch/packet/0x16.cpp
  src/mineserver/network/protocol/notch/packet/0x17.cpp
  src/mineserver/network/protocol/notch/packet/0x18.cpp
  src/mineserver/network/protocol/notch/packet/0x19.cpp
  src/mineserver/network/protocol/notch/packet/0x1A.cpp
  src/mineserver/network/protocol/notch/packet/0x1C.cpp
  src/mineserver/network/protocol/notch/packet/0x1D.cpp
  src/mineserver/network/protocol/notch/packet/0x1E.cpp
  src/mineserver/network/protocol/notch/packet/0x1F.cpp
  src/mineserver/network/protocol/notch/packet/0x20.cpp
  src/mineserver/network/protocol/notch/packet/0x21.cpp
  src/mineserver/network/protocol/notch/packet/0x22.cpp
  src/mineserver/network/protocol/notch/packet/0x26.cpp
  src/mineserver/network/protocol/notch/packet/0x27.cpp
  src/mineserver/network/protocol/notch/packet/0x28.cpp
  src/mineserver/network/protocol/notch/packet/0x29.cpp
  src/mineserver/network/protocol/notch/packet/0x2A.cpp
  src/mineserver/network/protocol/notch/packet/0x2B.cpp
  src/mineserver/network/protocol/notch/packet/0x32.cpp
  src/mineserver/network/protocol/notch/packet/0x33.cpp
  src/mineserver/network/protocol/notch/packet/0x34.cpp
  src/mineserver/network/protocol/notch/packet/0x35.cpp
  src/mineserver/network/protocol/notch/packet/0x36.cpp
  src/mineserver/network/protocol/notch/packet/0x3C.cpp
  src/mineserver/network/protocol/notch/packet/0x3D.cpp
  src/mineserver/network/protocol/notch/packet/0x46.cpp
  src/mineserver/network/protocol/notch/packet/0x47.cpp
  src/mineserver/network/protocol/notch/packet/0x64.cpp
  src/mineserver/network/protocol/notch/packet/0x65.cpp
  src/mineserver/network/protocol/notch/packet/0x66.cpp
  src/mineserver/network/protocol/notch/packet/0x67.cpp
  src/mineserver/network/protocol/notch/packet/0x68.cpp
  src/mineserver/network/protocol/notch/packet/0x69.cpp
  src/mineserver/network/protocol/notch/packet/0x6A.cpp
  src/mineserver/network/protocol/notch/packet/0x6B.cpp
  src/mineserver/network/protocol/notch/packet/0x82.cpp
  src/mineserver/network/protocol/notch/packet/0x83.cpp
  src/mineserver/network/protocol/notch/packet/0xC8.cpp
  src/mineserver/network/protocol/notch/packet/0xC9.cpp
  src/mineserver/network/protocol/notch/packet/0xFA.cpp
  src/mineserver/network/protocol/notch/packet/0xFE.cpp
  src/mineserver/network/protocol/notch/packet/0xFF.cpp
)

SOURCE_GROUP(${PROJECT_NAME} FILES ${mineserver_source})

INCLUDE_DIRECTORIES(src)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${ZLIB_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${ICONV_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${NOISE_INCLUDE_DIR})

LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

ADD_SUBDIRECTORY(src)

SET(TARGET mineserver)
MESSAGE(STATUS "Target: ${TARGET}")
ADD_EXECUTABLE(${TARGET} ${${TARGET}_source})

TARGET_LINK_LIBRARIES(mineserver
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SIGNALS_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  ${ZLIB_LIBRARIES}
  ${ICONV_LIBRARIES}
  ${NOISE_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
)
