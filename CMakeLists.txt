cmake_minimum_required(VERSION 3.17)

project(spork)

if ("${CMAKE_HOST_SYSTEM_NAME}" STREQUAL "Darwin")
    set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH}
        /usr/local/opt/qt/lib/cmake
    )
endif()

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
