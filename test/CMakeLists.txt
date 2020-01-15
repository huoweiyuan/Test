# cmake_minimum_required(VERSION 3.13)
project(avl)
set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_BUILD_TYPE "Debug")

#add_executable(avl
#avl.cc)

#add_executable(linkedbinarytree
#linkedbinarytree.cc)

#add_executable(calculate
#calculate.cc)

add_executable(binarysearchtree
binarysearchtree.cc)
