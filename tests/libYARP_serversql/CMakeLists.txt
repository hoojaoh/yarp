# Copyright (C) 2006-2019 Istituto Italiano di Tecnologia (IIT)
# All rights reserved.
#
# This software may be modified and distributed under the terms of the
# BSD-3-Clause license. See the accompanying LICENSE file for details.

add_executable(harness_serversql ServerTest.cpp)

target_include_directories(harness_serversql PRIVATE ${hmac_INCLUDE_DIRS})

target_link_libraries(harness_serversql PRIVATE YARP_harness
                                                YARP::YARP_OS
                                                YARP::YARP_serversql)
set_property(TARGET harness_serversql PROPERTY FOLDER "Test")

yarp_parse_and_add_catch_tests(harness_serversql)
