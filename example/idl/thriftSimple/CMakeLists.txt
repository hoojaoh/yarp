# Copyright (C) 2006-2019 Istituto Italiano di Tecnologia (IIT)
# All rights reserved.
#
# This software may be modified and distributed under the terms of the
# BSD-3-Clause license. See the accompanying LICENSE file for details.

cmake_minimum_required(VERSION 3.5)
project(thriftSimple_example)

set(CMAKE_CXX_FLAGS "-Weverything -Wno-c++98-compat -Wno-padded")

find_package(YARP COMPONENTS OS idl_tools REQUIRED)

#compile definition file to generate source code into the desired directory
yarp_idl_to_dir(INPUT_FILES demo.thrift
                OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
                SOURCES_VAR THRIFT_SOURCES
                HEADERS_VAR THRIFT_HEADERS
                INCLUDE_DIRS_VAR THRIFT_INCLUDE_DIRS
                VERBOSE)

# Create the server executable that implements the interface
add_executable(demoServer DemoServer.cpp
                          ${THRIFT_SOURCES}
                          ${THRIFT_HEADERS})
target_include_directories(demoServer PRIVATE ${THRIFT_INCLUDE_DIRS})
target_link_libraries(demoServer PRIVATE YARP::YARP_OS
                                         YARP::YARP_init)

# Create a fancier YARP-module server that implements the interface
add_executable(demoServerModule DemoServerModule.cpp
                                ${THRIFT_SOURCES}
                                ${THRIFT_HEADERS})
target_include_directories(demoServerModule PRIVATE ${THRIFT_INCLUDE_DIRS})
target_link_libraries(demoServerModule PRIVATE YARP::YARP_OS
                                               YARP::YARP_init)

# Create a test client executable
add_executable(demoClient DemoClient.cpp
                          ${THRIFT_SOURCES}
                          ${THRIFT_HEADERS})
target_include_directories(demoClient PRIVATE ${THRIFT_INCLUDE_DIRS})
target_link_libraries(demoClient PRIVATE YARP::YARP_OS
                                         YARP::YARP_init)

