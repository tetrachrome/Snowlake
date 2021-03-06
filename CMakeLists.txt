#!/bin/bash
#
# The MIT License (MIT)
#
# Copyright (c) 2020 Tomiko
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


# Set minimum CMake version.
cmake_minimum_required(VERSION 3.10)


# Project.
project(Snowlake CXX)


# Release mode.
set(CMAKE_BUILD_TYPE Release ... FORCE)


# Compiler.
set(CMAKE_CXX_COMPILER "clang++" CACHE STRING "")


# Linker.
set(CMAKE_LINKER "/usr/bin/lld-10")
set(CMAKE_EXE_LINKER_FLAGS "-Xlinker -v")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=/usr/bin/lld")


message(STATUS "C Compiler executable: ${CMAKE_C_COMPILER}")
message(STATUS "CXX Compiler executable: ${CMAKE_CXX_COMPILER}")
message(STATUS "Linker executable: ${CMAKE_LINKER}")
message(STATUS "Is compiler GNU CXX: ${CMAKE_COMPILER_IS_GNUCXX}")


set(CMAKE_MACOSX_RPATH 1)


# General compiler flags.
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++17 -g -w")
else ()
    set(CMAKE_CXX_FLAGS "\
        -std=c++17 \
        -g \
        -Wall \
        -Wno-c++98-compat \
        -Wno-padded \
        -Wno-c++98-compat-pedantic \
        -Wno-format-nonliteral \
        -Wno-c99-extensions \
        -Wno-extra-semi \
        -Wno-exit-time-destructors \
        -Wno-covered-switch-default \
        "
    )
endif (CMAKE_COMPILER_IS_GNUCXX)


# Linker options.
# Suppressing passing -rdynamic.
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")


# Reset per-target ar/ranlib flags.
if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(CMAKE_CXX_ARCHIVE_CREATE "<CMAKE_AR> rvs -o <TARGET> <LINK_FLAGS> <OBJECTS>")
endif ()


# Find googletest static library.
find_library(LIBGTEST_LIBRARY NAMES "gtest"
    PATHS "/usr/local/lib/gtest/"
    PATH_SUFFIXES "lib" "lib32" "lib64")

message("gtest library path found: " ${LIBGTEST_LIBRARY})


# Find googletest headers.
find_path(LIBGTEST_INCLUDE_DIR NAMES "gtest"
    PATHS
    "/opt/local/include"
    "/usr/local/include"
    "/usr/include"
    )


# Paths.
include_directories(SYSTEM ${LIBGTEST_INCLUDE_DIR})
include_directories("${CMAKE_SOURCE_DIR}/src/")
set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(UNITTESTS_DIR ${PROJECT_SOURCE_DIR}/unittests)
set(TESTS_DIR ${PROJECT_SOURCE_DIR}/tests)


# Sub-directories.
ADD_SUBDIRECTORY(${SRC_DIR})
ADD_SUBDIRECTORY(${UNITTESTS_DIR})
ADD_SUBDIRECTORY(${TESTS_DIR})


### THE END ###
