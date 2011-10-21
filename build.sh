#!/bin/sh

if [ "x${CXX}" = "x" ]; then CXX="c++"; fi;

find src -name '*.cpp' | sort | while read SRC; do
  OBJ="obj/"$(echo ${SRC} | sed -e 's#^src/##; s#/#_#g; s#.cpp$#.o#;');
  echo "${SRC} -> ${OBJ}";
  if [ ! -e ${OBJ} -o ${SRC} -nt ${OBJ} ]; then
    echo "Building...";
    ${CXX} -Isrc -c -O0 -g -o ${OBJ} ${SRC};
  fi;
done;

${CXX} -Isrc -O0 -g -o bin/app obj/app.o obj/mineserver_*.o -lboost_system
