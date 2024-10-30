project(
    'Noise',
    'cpp', 'c',
    version: '1.2.0',
    license: 'MIT',
    default_options: ['warning_level=1', 'cpp_std=c++17', 'c_std=c11'],
    meson_version: '>=1.1',
)

# Used by SDK meson.build file
ext_author = 'Kacper Bugla'
ext_company = 'Kacper Bugla'
ext_build = 22



# Contains tools used during build time
subdir('Tools')
# SDK
subdir('Lib')



ext_source = []

ext_source_shared = files(
    'Noise/ACE/Actions.cpp',
    'Noise/ACE/Expressions.cpp',
    'Noise/Extension.cpp',
)

ext_source_windows = files(
    'Noise/Edittime.cpp',
    'Noise/Properties.cpp',
)


ext_source += ext_source_shared
if host_machine.system() == 'windows'
    ext_source += ext_source_windows
endif


ext_include = include_directories('Noise')


if runtime_build
    # runtime builds use minified json
    darkext_json = custom_target('minify_json',
        build_by_default: true,
        input: files('Noise/DarkExt.json'),
        output: 'DarkExt.PostMinify.json',
        command: [jsonminify, '@INPUT@', '@OUTPUT@'],
    )
else
    darkext_json = files('Noise/DarkExt.json')
endif

ext_source += custom_target('embed_json',
    input: darkext_json,
    output: 'DarkExt.json.h',
    command: [bin2hpp, '@INPUT@', '@OUTPUT@', 'DarkExtJSON', 'DarkExtJSON_len'],
)

if host_machine.system() == 'windows'
    ext_source += import('windows').compile_resources(
        'Noise\Ext.rc',
        args: sdk_args_rc,
        depend_files: [
            'Noise\Resource.h',
            'Noise\Icon.png',
        ],
        include_directories: sdk_include,
    )
endif


ext = build_target(
    meson.project_name(),
    ext_source,
    target_type: sdk_ext_target_type,
    dependencies: darkedif_sdk,
    include_directories: ext_include,
    name_suffix: sdk_ext_name_suffix,
)

if host_machine.system() == 'wasi'
    # Hack: Manualy start the linker because meson uses arguments not recognized by wasm-ld
    # https://github.com/mesonbuild/meson/pull/11862
    cpp_compiler = find_program('cpp', 'clang++')

    ext_wasm = custom_target(meson.project_name() + '_wasm',
        build_by_default: true,
        input: ext.extract_all_objects(recursive: true),
        output: meson.project_name() + '.wasm',
        command: [cpp_compiler, '--target=wasm32-wasi', '-Wl,--no-entry', '@INPUT@', '-o', '@OUTPUT@'],
    )

    # javascript wrapper that loads the webassembly
    npm = find_program('npm')
    ext_js = custom_target(meson.project_name() + '_js',
        build_by_default: true,
        input: [ext_wasm, files('Lib/Html/Noise.ts')],  # meson uses this to determine if this needs to be run.
        output: meson.project_name() + '.js',
        command: [npm, '--prefix', meson.current_source_dir() / 'Lib' / 'Html', 'run', 'build', '--', '--outfile=' + meson.current_build_dir() / 'Noise.js', '--alias:Noise.wasm=' + ext_wasm.full_path()],
    )
endif



# TODO: custom script that installs build extension to correct directory in a fusion install
#       this will make meson install work
# meson.add_install_script()


# if(host_machine.system() == 'wasi')
#     wasm_wasi_target = '--target=wasm32-wasi'

#     runtime_ext = static_library(
#         meson.project_name(),
#         ext_source,
#         sdk_source,
#         darkext_json,
#         acecalltable,
#         cpp_args: [wasm_wasi_target, '-fno-exceptions', '-fvisibility=hidden', defines],
#         include_directories: ext_includes,
#         name_prefix: '',
#         # name_suffix: 'wasm',
#         dependencies: deps,
#     )



# endif