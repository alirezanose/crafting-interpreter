cmake_minimum_required(VERSION 4.3)
project(crafting_interpreter C)

set(CMAKE_C_STANDARD 11)

add_library(crafting_interpreter STATIC library.c)
