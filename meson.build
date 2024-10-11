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



if host_machine.system() == 'windows'
    ext_source += import('windows').compile_resources(
        'Noise\Ext.rc',
        args: sdk_args_rc,
        depend_files: [
            'Noise\Resource.h',
            'Noise\Icon.png',
            'Noise\DarkExt.json',
        ],
        include_directories: sdk_include,
    )
endif


ext = shared_library(
    meson.project_name(),
    ext_source,
    dependencies: darkedif_sdk,
    include_directories: ext_include,
    install: true,
    name_prefix: '',
    name_suffix: 'mfx',
)


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

#     # Hack: Manualy start the linker because meson uses arguments not recognized by wasm-ld
#     # https://github.com/mesonbuild/meson/pull/11862
#     cpp_compiler = find_program('cpp', 'clang++')
#     runtime_ext_wasm = custom_target('runtime_ext_wasm',
#         build_by_default: true,
#         input: runtime_ext.extract_all_objects(recursive: true),
#         output: meson.project_name() + '.wasm',
#         command: [cpp_compiler, wasm_wasi_target, '-Wl,--no-entry', '@INPUT@', '-o', '@OUTPUT@'],
#     )


#     # out_js = meson.current_build_dir() / meson.project_name() + '.js.in'
#     # javascript wrapper that loads the webassembly
#     npm = find_program('npm')
#     html_ext_wrapper = custom_target('html_ext_wrapper',
#         build_by_default: true,
#         input: [runtime_ext_wasm, files('Lib/Html/Noise.ts')],  # meson uses this to determine if this needs to be run.
#         output: meson.project_name() + '.js',
#         command: [npm, '--prefix', meson.current_source_dir() / 'Lib' / 'Html', 'run', 'build', '--', '--outfile=' + meson.current_build_dir() / 'Noise.js', '--alias:Noise.wasm=' + runtime_ext_wasm.full_path()],
#     )
# endif