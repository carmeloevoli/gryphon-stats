project(GRYPHON CXX)
cmake_minimum_required(VERSION 3.6)

set( CMAKE_VERBOSE_MAKEFILE off )
set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" )
set( CMAKE_CXX_COMPILER "/usr/local/bin/g++-10" )
set( CMAKE_CXX_FLAGS "-O3 -ftree-vectorize -std=c++11 -fopenmp -DOPENMP -DTHREADS=16" )
set( GRYPHON_INCLUDES )
set( GRYPHON_LIBRARIES )

set (CMAKE_CXX_STANDARD 11)
cmake_policy(SET CMP0048 NEW)

# include
include_directories( "${CMAKE_SOURCE_DIR}" )
include_directories( external/plog/include/ )

# GSL (external)
find_package(GSL)
if(GSL_FOUND)
    set(HAVE_LIBGSL 1)
    list(APPEND GRYPHON_INCLUDES ${GSL_INCLUDE_DIR})
    list(APPEND GRYPHON_LIBRARIES ${GSL_LIBRARIES})
else(GSL_FOUND)
    message(FATAL_ERROR "Require GSL: set GSL_HOME")
endif(GSL_FOUND)

# copy data files in build
#file(GLOB GRYPHON_DATA "data/*.txt")
#file(COPY ${GRYPHON_DATA} DESTINATION ${PROJECT_BINARY_DIR}/data)

# create the output dir
#file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/output)

# add source files
set( GRYPHON_SRCS
	src/Chi2.cpp
	src/Data.cpp
	src/ProgressBar.cpp
	src/Utilities.cpp
	)

# make library
include_directories (include ${GRYPHON_INCLUDES})
add_library( GRYPHON_LIB ${GRYPHON_SRCS} ${GRYPHON_INCLUDES} )

# make executables
add_executable(gryphon src/main.cpp)
target_link_libraries (gryphon GRYPHON_LIB ${GRYPHON_LIBRARIES})

add_executable(nuclei projs/nuclei_fluctuations.cpp)
target_link_libraries (nuclei GRYPHON_LIB ${GRYPHON_LIBRARIES})

# show summary
message (STATUS "CMAKE_SYSTEM .......... = ${CMAKE_SYSTEM}")
message (STATUS "BUILD_SHARED_LIBS ..... = ${BUILD_SHARED_LIBS}")
message (STATUS "CMAKE_CXX_COMPILER .... = ${CMAKE_CXX_COMPILER}")
message (STATUS "CMAKE_CXX_FLAGS ....... = ${CMAKE_CXX_FLAGS}")
message (STATUS "CMAKE_INCLUDE_PATH .... = ${CMAKE_INCLUDE_PATH}")
message (STATUS "GRYPHON_INCLUDES ...... = ${GRYPHON_INCLUDES}")
message (STATUS "GRYPHON_LIBRARIES ..... = ${GRYPHON_LIBRARIES}")
