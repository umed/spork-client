cmake_minimum_required(VERSION 3.17)

set(TARGET_NAME app)
project(${TARGET_NAME})

find_package(Qt5 COMPONENTS Core Gui Qml Quick REQUIRED)

set(SOURCES
    main.cpp
    imageprovider.h
    imageprovider.cpp
    resources/resources.qrc
)

add_executable(${TARGET_NAME} ${SOURCES})

target_link_libraries(${TARGET_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
)
