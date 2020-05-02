cmake_minimum_required(VERSION 3.5)

project(HCompress LANGUAGES C)

add_executable(HCompress  src/input.h src/input.c src/main.c src/vector.c src/vector.h src/readText.c src/readText.h src/htree.c src/htree.h src/byte.c src/byte.h)
