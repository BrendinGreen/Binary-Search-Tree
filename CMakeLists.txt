cmake_minimum_required(VERSION 3.7)
project(Lab9)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES BST_Test_Driver.cpp WordPair.cpp ElementAlreadyExistsInBSTException.cpp ElementDoesNotExistInBSTException.cpp BSTNode.h BST.h)
add_executable(Lab9 ${SOURCE_FILES})