cmake_minimum_required(VERSION 3.22)
project(GatorAVL)

set(CMAKE_CXX_STANDARD 14)

add_executable(GatorAVL main.cpp Node.cpp Node.h AVLTree.cpp AVLTree.h)
