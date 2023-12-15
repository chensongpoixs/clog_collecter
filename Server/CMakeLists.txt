project(Server)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
MESSAGE(STATUS "#########################")
SET(CMAKE_BUILD_TYPE Release)
ADD_DEFINITIONS(-std=c++11   -fpermissive )

SET(EXTRA_INC_DIR /home/chensong/dep)


#SET(CMAKE_VERBOSE_MAKEFILE ON)

INCLUDE_DIRECTORIES(
        /usr/local/include
        ${EXTRA_INC_DIR}/boost/include
        ${EXTRA_INC_DIR}/thrift/include
        ${EXTRA_INC_DIR}/protobuf/include

#        ${EXTRA_INC_DIR}/include
#        ${EXTRA_INC_DIR}/include/mysql
        ${PROJECT_SOURCE_DIR}/clib
        ${PROJECT_SOURCE_DIR}/common
        ${PROJECT_SOURCE_DIR}/common/cmsg
        ${PROJECT_SOURCE_DIR}/common/cclient_msg
        ${PROJECT_SOURCE_DIR}/cloud_thrift
        #${PROJECT_SOURCE_DIR}/Robot
)




SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/linux/RenderServer )
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/linux)

LINK_DIRECTORIES(
        /usr/local/lib
        /usr/local/lib64
        /usr/lib64/mysql/
        /usr/lib/x86_64-linux-gnu
        ${PROJECT_SOURCE_DIR}/linux/RenderServer
        ${EXTRA_INC_DIR}/boost/lib
        ${EXTRA_INC_DIR}/thrift/lib
        ${EXTRA_INC_DIR}/protobuf/lib
)

#add_subdirectory(ccloud_game_rtc/client)
#add_subdirectory(clib)
#add_subdirectory(common)
#add_subdirectory(cloud_thrift)
add_subdirectory(gateway)
add_subdirectory(Robot)
add_subdirectory(thrift_test/thrift_test/thrift_test)
