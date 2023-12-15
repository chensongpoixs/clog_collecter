project(common)
cmake_minimum_required(VERSION 2.8)
MESSAGE(STATUS "#########################")

file(GLOB ALL_CXX_SRCS
        ./*.cpp  ./*.cc
        ./*.h
        ./cclient_msg/*.cc
        ./cclient_msg/*.h
        ./cclient_msg/*.cpp
        )

add_library(${PROJECT_NAME} ${ALL_CXX_SRCS})
target_link_libraries(${PROJECT_NAME} )