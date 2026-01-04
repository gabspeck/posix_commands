cmake_minimum_required(VERSION 4.1)
project(posix_commands C)

set(CMAKE_C_STANDARD 99)

add_executable(true true.c)
add_executable(false false.c)
