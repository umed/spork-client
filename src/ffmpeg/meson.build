avformat_dep = dependency('libavformat')
avdevice_dep = dependency('libavdevice')
avutil_dep = dependency('libavutil')

screencapture_lib = shared_library('screencapture',
    ['screen_recorder.cpp'],
    dependencies: [avformat_dep, avdevice_dep, avutil_dep, fmt_dep],
    install: true)
