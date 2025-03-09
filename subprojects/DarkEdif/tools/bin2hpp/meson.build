# Converts a file to a header that can be included with the aplication.
bin2hpp_exe = executable(
    'bin2hpp',
    files('bin2hpp.cpp'),
    native: true,
    build_by_default: false,
)

bin2hpp = generator(
    bin2hpp_exe,
    arguments: ['@INPUT@', '@OUTPUT@', '@EXTRA_ARGS@'],
    output: '@PLAINNAME@.h',
)