PROJECT(mineserver)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
CMAKE_POLICY(SET CMP0014 OLD)

#
# Project version
#
SET(${PROJECT_NAME}_MAJOR_VERSION 0)
SET(${PROJECT_NAME}_MINOR_VERSION 0)
SET(${PROJECT_NAME}_PATCH_LEVEL 0)

#
# set default build to Debug
#
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug
    CACHE STRING "Choose the type of build, options are: Debug, Profile, Release"
    FORCE
  )
ENDIF()

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
  SET(CMAKE_CXX_FLAGS "-Werror -W -Wall -Wno-unused -pedantic")
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

FIND_PACKAGE(Boost COMPONENTS system filesystem signals REQUIRED)

SET(mineserver_source
  src/app.cpp
  src/mineserver/game.cpp
  src/mineserver/game/player.cpp
  src/mineserver/network/server.cpp
  src/mineserver/network/client.cpp
  src/mineserver/network/protocol/notch/parser.cpp
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
  src/mineserver/network/protocol/notch/packet/0xFE.cpp
  src/mineserver/network/protocol/notch/packet/0xFF.cpp
)
SOURCE_GROUP(${PROJECT_NAME} FILES ${mineserver_source})

INCLUDE_DIRECTORIES(src)
INCLUDE_DIRECTORIES(vendor)

ADD_SUBDIRECTORY(src)

SET(TARGET mineserver)
MESSAGE(STATUS "Target: ${TARGET}")
ADD_EXECUTABLE(${TARGET} ${${TARGET}_source})

TARGET_LINK_LIBRARIES(mineserver
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_SIGNALS_LIBRARY}
)
