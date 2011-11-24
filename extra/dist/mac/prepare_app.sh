#!/bin/sh

DO() {
  echo "${@}";
  "${@}";
}

if [ "$#" -lt 3 ]; then
  echo "Usage: $0 <path to binary> <path to .app template> <path to output .app>";
  exit;
fi;

BIN=${1};
APP=${2};
OUT=${3};

if [ ! -x "${BIN}" ]; then
  echo "Error: ${BIN} is not an executable file";
  exit;
fi;

if [ ! -d "${APP}" ]; then
  echo "Error: ${APP} is not a directory";
  exit;
fi;

if [ -e "${OUT}" ]; then
  echo "Error: ${OUT} already exists";
  exit;
fi;

TMP=$(mktemp -d $(pwd)/_mineserver.build.app.XXXX);

DO rm -r ${TMP};
DO cp -a ${APP} ${TMP};
DO cp -a ${BIN} ${TMP}/Contents/MacOS/mineserver2;

DO install_name_tool -change libboost_filesystem.dylib @executable_path/../Resources/lib/libboost_filesystem.dylib ${TMP}/Contents/MacOS/mineserver2;
DO install_name_tool -change libboost_signals.dylib @executable_path/../Resources/lib/libboost_signals.dylib ${TMP}/Contents/MacOS/mineserver2;
DO install_name_tool -change libboost_system.dylib @executable_path/../Resources/lib/libboost_system.dylib ${TMP}/Contents/MacOS/mineserver2;
DO install_name_tool -change libboost_thread.dylib @executable_path/../Resources/lib/libboost_thread.dylib ${TMP}/Contents/MacOS/mineserver2;

DO mv ${TMP} ${OUT};
