cmake_minimum_required(VERSION 2.8)
project(webapp)

include_directories(".")
include_directories("./clients/")
include_directories("./handlers/")
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -march=native -Wall -O2")
set(SRC_LIST app.cpp main.cpp configs.cpp log.cpp tcpclient.cpp tcpserver.cpp ext.cpp router.cpp webserver.cpp clients/termoclient.cpp handlers/termohandler.cpp handlers/unknownhandler.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} -lpthread)