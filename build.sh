#!/bin/sh

clang++ -c -g -o obj/packetstream.o src/packetstream.cpp
clang++ -c -g -o obj/app.o src/app.cpp
clang++ -g -o bin/app obj/app.o obj/packetstream.o
