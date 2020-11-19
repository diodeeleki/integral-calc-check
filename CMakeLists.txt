#/*-------------------------------------------------------------------------
#    Copyright diode 2020.
#    Use, modification and distribution are subject to the
#    Boost Software License, Version 1.0.  (See accompanying file
#    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#*///-----------------------------------------------------------------------

cmake_minimum_required(VERSION 3.16.3)
project(icc CXX)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message("In-source build is not possible.")
endif()

add_library(icc INTERFACE)
target_compile_features(icc INTERFACE cxx_std_20)#   c++20以上でのコンパイルにしか対応しない

include(GNUInstallDirs)#    下記installで必要な変数定義

target_include_directories(
    icc INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include># ./include
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>#   /usr/local/include
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/exsample)

install(TARGETS icc EXPORT icc-config)

install(
    EXPORT icc-config 
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/icc#   /usr/local/lib/cmake/si
)

install(
    DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/icc/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/icc#   /usr/local/include/si
)
