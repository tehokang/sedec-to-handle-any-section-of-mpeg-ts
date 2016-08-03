cmake_minimum_required(VERSION 2.8)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(project_name decoder_example)
project(${project_name} CXX)

if ("${CMAKE_BUILD_TYPE}" MATCHES "release")
	set(CMAKE_CXX_FLAGS_RELEASE "-O2")
else ("${CMAKE_BUILD_TYPE}" MATCHES "debug")
	set(CMAKE_CXX_FLAGS_DEBUG "-DCONFIG_DEBUG -O -g")
endif ("${CMAKE_BUILD_TYPE}" MATCHES "release")

set(rootdir ${CMAKE_SOURCE_DIR}/examples/decoder)
set(sources 
	${rootdir}/decoder_sample.cpp
)

include_directories(
	${CMAKE_SOURCE_DIR}/sedec/include
)

add_definitions(-std=c++11 -fexceptions)
link_directories(
	${CMAKE_BINARY_DIR}
)

add_executable(${project_name} ${sources})

add_custom_command(
	TARGET ${project_name}
	POST_BUILD
	COMMAND cp -f ${rootdir}/example_ait.dump ${CMAKE_BINARY_DIR}
)

target_link_libraries(${project_name} sedec)
