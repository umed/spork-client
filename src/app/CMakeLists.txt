cmake_minimum_required(VERSION 3.17)

set(TARGET_NAME app)
project(${TARGET_NAME})

find_package(Qt5 COMPONENTS Core Gui Qml REQUIRED)

# find_path(AVCODEC_INCLUDE_DIR libavcodec/avcodec.h)
# find_library(AVCODEC_LIBRARY avcodec)

# find_path(AVFORMAT_INCLUDE_DIR libavformat/avformat.h)
# find_library(AVFORMAT_LIBRARY avformat)

# find_path(AVUTIL_INCLUDE_DIR libavutil/avutil.h)
# find_library(AVUTIL_LIBRARY avutil)

# find_path(AVDEVICE_INCLUDE_DIR libavdevice/avdevice.h)
# find_library(AVDEVICE_LIBRARY avdevice)
add_executable(${TARGET_NAME} main.cpp resources/resources.qrc)

target_link_libraries(${TARGET_NAME} Qt5::Core Qt5::Gui Qt5::Qml)
