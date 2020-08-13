cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 14)

project(Minisql)

file(GLOB SRC */*.*)

add_executable(Minisql ${SRC} common/Data.cpp common/Data.h index/BTree.cpp index/BTree.h index/IndexManager.cpp index/IndexManager.h)

