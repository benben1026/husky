# Copyright 2016 Husky Team
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
# http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


project(husky)
cmake_minimum_required(VERSION 3.0.2)

# CMake Options
set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS_DEBUG "-g")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -w")
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wno-deprecated-declarations")
endif()

# Dependencies
include(cmake/dep.cmake)
include(cmake/utils.cmake)
include(cmake/external.cmake)

# Boost Libraries
find_package(Threads)
find_package(Boost 1.58.0 COMPONENTS system filesystem regex thread program_options date_time chrono)

# External Includes
set(EXTERNAL_INCLUDE ${Boost_INCLUDE_DIRS} ${ZMQ_INCLUDE_DIR} ${GLOG_INCLUDE})

# External Libraries
set(EXTERNAL_LIB ${ZMQ_LIBRARY} ${TCMALLOC_LIBRARY} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} ${GLOG_LIBRARY})

# libhdfs3
if(LIBHDFS3_FOUND)
    list(APPEND EXTERNAL_INCLUDE ${LIBHDFS3_INCLUDE_DIR})
    list(APPEND EXTERNAL_LIB ${LIBHDFS3_LIBRARY})
    add_definitions(-DWITH_HDFS)
endif(LIBHDFS3_FOUND)

# MongoDB
if(MONGOCLIENT_FOUND)
    list(APPEND EXTERNAL_INCLUDE ${MONGOCLIENT_INCLUDE_DIR})
    list(APPEND EXTERNAL_LIB ${RT_LIBRARY} ${MONGOCLIENT_LIBRARY})
    add_definitions(-DWITH_MONGODB)
endif(MONGOCLIENT_FOUND)

# Thrift
if(THRIFT_FOUND)
    list(APPEND EXTERNAL_INCLUDE ${THRIFT_INCLUDE_DIR})
    list(APPEND EXTERNAL_LIB ${THRIFT_LIBRARY})
    add_definitions(-DWITH_THRIFT)
endif(THRIFT_FOUND)

if(WIN32)
    list(APPEND EXTERNAL_LIB wsock32 ws2_32)
endif()

add_subdirectory(base)
add_subdirectory(core)
add_subdirectory(io)
add_subdirectory(lib)
add_subdirectory(examples)
add_subdirectory(master)
add_subdirectory(test)
add_subdirectory(benchmarks)

# libhusky.a
set(husky-objs $<TARGET_OBJECTS:channel-objs> $<TARGET_OBJECTS:base-objs> $<TARGET_OBJECTS:core-objs> ${io-objs} ${lib-objs})
add_library(husky STATIC ${husky-objs})
