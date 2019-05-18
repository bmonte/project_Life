cmake_minimum_required(VERSION 3.5)
project (Canvas VERSION 1.0.0 LANGUAGES CXX )

#=== FINDING PACKAGES ===#

#--------------------------------
# This is for old cmake versions
set (CMAKE_CXX_STANDARD 14)
#--------------------------------

#=== SETTING VARIABLES ===#
# Compiling flags
set( GCC_COMPILE_FLAGS "-Wall -Wextra -pedantic -ansi -O3" )
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS} ${PREPROCESSING_FLAGS}" )

#Include dir
include_directories( include ../lib )

#=== Main App ===
#Can manually add the sources using the set command as follows:
#set(SOURCES src/canvas.cpp)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")

add_executable(canvas ${SOURCES})
