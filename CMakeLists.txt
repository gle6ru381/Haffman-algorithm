cmake_minimum_required(VERSION 3.5)

project(HCompress LANGUAGES C)

add_executable(HCompress main.c vector.c vector.h readText.c readText.h htree.c htree.h)
