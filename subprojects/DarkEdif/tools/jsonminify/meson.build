# minifies a json file
jsonminify_exe = executable(
    'jsonminify',
    files('jsonminify.cpp'),
    native: true,
    build_by_default: false,
)

jsonminify = generator(
    jsonminify_exe,
    arguments: ['@INPUT@', '@OUTPUT@'],
    output: '@PLAINNAME@',
)