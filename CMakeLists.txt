cmake_minimum_required(VERSION 3.14)
project(cheetah)
set(CMAKE_VERBOSE_MAKEFILE ON)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
else ()
    add_definitions(-DDEBUG=0)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(LIB_PREFIX "/usr/local/lib")

find_package(Threads REQUIRED)

find_package(cppzmq)
set(ZMQ_LIB "${LIB_PREFIX}/libzmq.a")

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

set ( SOURCES
        main.cc
        Monitor.cc)

set ( HEADERS
        Monitor.h)

set(PROJECT_SRCS ${SOURCES})
set(PROJECT_HDRS ${HEADERS})

add_executable(cheetah
        ${PROJECT_SRCS}
        ${PROJECT_HDRS})

target_link_libraries(cheetah
        PRIVATE
        crypto
        ssl
        ${CMAKE_THREAD_LIBS_INIT}
        ${ZMQ_LIB})