cmake_minimum_required(VERSION 3.14)
project(graph_C C)

set(CMAKE_C_STANDARD 99)

add_executable(graph_C main.c graph.c graph.h)