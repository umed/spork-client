project('spork', 'cpp', default_options: ['cpp_std=c++17'])

fmt_dep = dependency('fmt', required: false)

if not fmt_dep.found()
    fmt_lib = subproject('fmt')
    fmt_dep = fmt_lib.get_variable('fmt_dep')
endif

subdir('src')
