cmake_minimum_required(VERSION 3.17)

set(TARGET_NAME screenrecorder)
project(${TARGET_NAME})

find_package(Qt5 COMPONENTS Multimedia REQUIRED)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCES)
set(SOURCES
    main.cpp
    imageprovider.h
    imageprovider.cpp
    resources/resources.qrc
)

add_library(${TARGET_NAME} SHARED ${SOURCES})

target_link_libraries(${TARGET_NAME}
    Qt5::Multimedia
)

# find_path(AVCODEC_INCLUDE_DIR libavcodec/avcodec.h)
# find_library(AVCODEC_LIBRARY avcodec)

# find_path(AVFORMAT_INCLUDE_DIR libavformat/avformat.h)
# find_library(AVFORMAT_LIBRARY avformat)

# find_path(AVUTIL_INCLUDE_DIR libavutil/avutil.h)
# find_library(AVUTIL_LIBRARY avutil)

# find_path(AVDEVICE_INCLUDE_DIR libavdevice/avdevice.h)
# find_library(AVDEVICE_LIBRARY avdevice)
