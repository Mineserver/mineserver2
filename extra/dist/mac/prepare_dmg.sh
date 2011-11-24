#!/bin/sh

DO() {
  echo "${@}";
  "${@}";
}

if [ "$#" -lt 3 ]; then
  echo "Usage: $0 <path to .app> <path to .dmg template> <path to output .dmg>";
  exit;
fi;

APP=${1};
DMG=${2};
OUT=${3};

if [ ! -d ${APP} ]; then
  echo "Error: ${APP} is not a directory";
  exit;
fi;

TMP=$(mktemp -d $(pwd)/_mineserver.build.dmg.XXXX);

DO cp -a ${DMG} ${TMP}/uncompressed.dmg;

DO mkdir ${TMP}/mount;

DO hdiutil attach -mount required -mountpoint ${TMP}/mount ${TMP}/uncompressed.dmg;

DO rm -r ${TMP}/mount/Mineserver2.app;
DO cp -a ${APP} ${TMP}/mount/Mineserver2.app;

DO hdiutil detach ${TMP}/mount;

DO hdiutil convert -format UDBZ -o ${OUT} ${TMP}/uncompressed.dmg;

DO rm -r ${TMP};
