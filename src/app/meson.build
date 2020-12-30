qt5 = import('qt5')
qt5_dep = dependency('qt5', modules: ['Core', 'Gui', 'Qml', 'Quick', 'Multimedia'])

resources = qt5.preprocess(qresources: 'resources/resources.qrc', dependencies: qt5_dep)

sources = ['imageprovider.cpp', 'main.cpp', resources]

executable('spork', sources, dependencies: [qt5_dep, screenrecorder_dep])
