cmake_minimum_required(VERSION 2.8)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(project_name sedec)
project(${project_name} CXX)

if ("${CMAKE_BUILD_TYPE}" MATCHES "release")
	set(CMAKE_CXX_FLAGS_RELEASE "-O2")
else ("${CMAKE_BUILD_TYPE}" MATCHES "debug")
	set(CMAKE_CXX_FLAGS_DEBUG "-DCONFIG_DEBUG -O -g")
endif ("${CMAKE_BUILD_TYPE}" MATCHES "release")

set(rootdir ${CMAKE_SOURCE_DIR}/sedec)
set(sources 
	${rootdir}/src/ait_section.cc
	${rootdir}/src/ait_section_transcoder.cc
	${rootdir}/src/application.cc
	${rootdir}/src/application_descriptor.cc
	${rootdir}/src/application_name_descriptor.cc
	${rootdir}/src/application_recording_descriptor.cc
	${rootdir}/src/application_usage_descriptor.cc
	${rootdir}/src/bit_readwriter.cc
	${rootdir}/src/connection_requirement_descriptor.cc
	${rootdir}/src/descriptor.cc
	${rootdir}/src/descriptor_factory.cc
	${rootdir}/src/parental_rating_descriptor.cc
	${rootdir}/src/section.cc
	${rootdir}/src/simple_application_boundary_descriptor.cc
	${rootdir}/src/simple_application_location_descriptor.cc
	${rootdir}/src/transport_protocol_descriptor.cc
)

include_directories(
	${rootdir}/include
)

add_definitions(-std=c++11 -fexceptions)

add_library(${project_name} SHARED ${sources})

# Version configuration
set(version_major 0)
set(version_minor 1)
set(version_patch 1)

set_target_properties(
	${project_name} 
	PROPERTIES 
	VERSION "${version_major}.${version_minor}.${version_patch}" 
	SOVERSION "${version_major}"
)
