cmake_minimum_required(VERSION 2.10)
project(jsoncpp)

include_directories(.)

set(JSONCPP_SRCS
        json_reader.cpp
        json_value.cpp
        json_writer.cpp)

add_library(jsoncpp STATIC ${JSONCPP_SRCS})
