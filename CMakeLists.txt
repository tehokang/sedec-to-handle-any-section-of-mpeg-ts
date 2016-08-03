# Specify the minimum version for CMake
cmake_minimum_required(VERSION 2.8)

set(CHIP_CORE "x86") # x86, mipsel, arm
set(TOOLCHAIN_VER "4.8-1.0")

if ("${CHIP_CORE}" MATCHES "x86" )
	set(CMAKE_C_COMPILER /usr/bin/gcc)
	set(CMAKE_CXX_COMPILER /usr/bin/g++)
elseif ("${CHIP_CORE}" MATCHES "mipsel")
	set(CMAKE_C_COMPILER /opt/toolchains/stbgcc-${TOOLCHAIN_VER}/bin/mipsel-linux-gcc)
	set(CMAKE_CXX_COMPILER /opt/toolchains/stbgcc-${TOOLCHAIN_VER}/bin/mipsel-linux-g++)
elseif ("${CHIP_CORE}" MATCHES "arm")
	set(CMAKE_C_COMPILER /opt/toolchains/stbgcc-${TOOLCHAIN_VER}/bin/arm-linux-gcc)
	set(CMAKE_CXX_COMPILER /opt/toolchains/stbgcc-${TOOLCHAIN_VER}/bin/arm-linux-g++)
endif()

# Project's name
set(project_name damoa)
project(${project_name} CXX)

# Set the output folder where your program will be created
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/out/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

if ("${build}" MATCHES "debug")
	set (CMAKE_BUILD_TYPE "debug")
else ("${build}" MATCHES "debug")
	set (CMAKE_BUILD_TYPE "release")
endif ("${build}" MATCHES "debug")

message("COMPILER : " ${CMAKE_CXX_COMPILER})
message("CMAKE_SOURCE_DIR : " ${CMAKE_SOURCE_DIR})
message("CHIP_CORE : " ${CHIP_CORE})
message("CMAKE_MAKE_PROGRAM : " ${CMAKE_MAKE_PROGRAM})
message("WORKING_DIRECTORY : " ${CMAKE_CURRENT_BINARY_DIR})
message("CMAKE_BUILD_TOOL : " ${CMAKE_BUILD_TOOL})
message("CMAKE_COMMAND : " ${CMAKE_COMMAND})
message("LIBRARY_OUTPUT_PATH : " ${LIBRARY_OUTPUT_PATH})

# The following folder will be included
add_subdirectory(sedec)
add_subdirectory(examples/decoder)
add_subdirectory(examples/encoder)
