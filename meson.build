project(
    'ntHash',
    'cpp',
    version: '2.4.0',
    license: 'MIT',
    default_options: [
        'cpp_std=c++17',
        'werror=true',
        'warning_level=3',
        'optimization=3',
        'b_lto=true',
        'b_ndebug=true',
        'cpp_args=-funroll-loops',
    ],
)

add_project_arguments('-march=native', language: 'cpp')

include_dirs = [include_directories('include')]

# Source files for the static library
sources = [
    'src/kmer.cpp',
    'src/seed.cpp',
    'src/adaptive_hash.cpp',
    'src/entropy.cpp',
]

# Static library build
nthash_lib = static_library(
    'nthash',
    sources,
    include_directories: include_dirs,
    install: true,
    install_dir: 'lib',
)

nthash_dep = declare_dependency(
    link_with: nthash_lib,
    include_directories: include_dirs,
)

# Install headers
install_headers('include/nthash/nthash.hpp', install_dir: 'include/nthash')
install_headers('include/nthash/entropy.hpp', install_dir: 'include/nthash')  # your entropy class

# ===================== Executables ===================== #

examples = [
    ['std_benchmark',      'examples/benchmark.cpp'],
    ['adaptive_benchmark', 'examples/adaptive_benchmark.cpp'],
    ['entropy_benchmark',  'examples/entropy_benchmark.cpp'],
    ['normal_benchmark',   'examples/normal_benchmark.cpp'],
]

foreach example : examples
    exe = executable(
        example[0],
        example[1],
        dependencies: nthash_dep,
        include_directories: include_dirs,
        install: true,
    )
endforeach

# ======================= Tests ========================= #

tests = [
    'tests/tests.cpp',
    'tests/adaptive_test.cpp',
]

foreach src : tests
    name = src.split('/')[-1].split('.')[0]
    exe = executable(
        name,
        src,
        dependencies: nthash_dep,
        include_directories: include_dirs,
        install: false,
    )
    test(name, exe)
endforeach

# ====================== Docs =========================== #

doxygen = find_program('doxygen', required: false)
if doxygen.found()
    message('Doxygen found')
    run_target('docs', command: [meson.source_root() + '/update-docs.sh'])
else
    warning('Documentation disabled without doxygen')
endif