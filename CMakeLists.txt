cmake_minimum_required(VERSION 2.8.4)
project(lesh)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/cmd/cd_cmd.c
    src/cmd/cd_cmd.h
    src/executer.c
    src/executer.h
    src/general.c
    src/general.h
    src/getline.c
    src/getline.h
    src/hash.c
    src/hash.h
    src/lesh_perl.c
    src/lesh_perl.h
    src/main.c
    src/parser.c
    src/parser.h
    src/stdafx.c
    src/stdafx.h)

add_executable(lesh ${SOURCE_FILES})