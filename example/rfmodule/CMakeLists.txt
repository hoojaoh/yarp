# Copyright (C) 2006-2019 Istituto Italiano di Tecnologia (IIT)
# All rights reserved.
#
# This software may be modified and distributed under the terms of the
# BSD-3-Clause license. See the accompanying LICENSE file for details.

cmake_minimum_required(VERSION 3.5)
project(module)

find_package(YARP COMPONENTS OS REQUIRED)

add_executable(module main.cpp)
target_link_libraries(module PRIVATE YARP::YARP_OS YARP::YARP_init)
