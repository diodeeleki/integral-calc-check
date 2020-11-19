#/*-------------------------------------------------------------------------
#    Copyright diode 2020.
#    Use, modification and distribution are subject to the
#    Boost Software License, Version 1.0.  (See accompanying file
#    LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#*///-----------------------------------------------------------------------

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS_DEBUG "/O0 /Wall")
    set(CMAKE_CXX_FLAGS_RELEASE "/O2 /Wall")
else()
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 -s -Wall -Wextra")
endif()
    
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(exsample ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_link_libraries(exsample icc)
