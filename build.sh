#!/bin/sh

find src -name '*.cpp' | while read SRC; do
  OBJ="obj/"$(echo ${SRC} | sed -e 's#^src/##; s#/#_#g; s#.cpp$#.o#;');
  echo "${SRC} -> ${OBJ}";
  if [ ! -e ${OBJ} -o ${SRC} -nt ${OBJ} ]; then
    c++ -Isrc -c -O0 -g -o ${OBJ} ${SRC};
  fi;
done;

clang++ -g -o bin/app obj/app.o obj/mineserver_network_protocol_notch_packetstream.o obj/mineserver_network_protocol_notch_packet_0x02.o
