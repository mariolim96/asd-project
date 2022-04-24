cmake_minimum_required(VERSION 3.16)
project(progetto2 C)

set(CMAKE_C_STANDARD 99)

add_executable(progetto2 main.c fly.c fly.h users.c users.h heap.c heap.h linkedlist.c linkedlist.h menu.c menu.h)