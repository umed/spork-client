avformat_dep = dependency('libavformat')
avdevice_dep = dependency('libavdevice')
avutil_dep = dependency('libavutil')
swscale_dep = dependency('libswscale')

qt5 = import('qt5')
qt5_screenrecorder_dep = dependency('qt5', modules: ['Core', 'Multimedia', 'Qml', 'Gui'])

inc_dirs = include_directories('.')

moc_files = qt5.preprocess(moc_headers: 'videoproducer.h',
                           include_directories: inc_dirs,
                           dependencies: qt5_screenrecorder_dep)

deps = [avformat_dep, avdevice_dep, avutil_dep, swscale_dep, fmt_dep, qt5_screenrecorder_dep]

sources = ['recorder.cpp', 'videoproducer.cpp', moc_files]

lib = shared_library('screenrecorder', sources, dependencies: deps, include_directories: inc_dirs, install: true)

screenrecorder_dep = declare_dependency(dependencies: deps, include_directories: inc_dirs, link_with: lib)
