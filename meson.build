# TODO: Completely ditch visual studio and use meson instead.

project(
    'Noise',
    'cpp', 'c',
    version: '1.2.0',
    license: 'MIT',
    default_options: ['warning_level=3', 'cpp_std=c++17', 'c_std=c11'],
    meson_version: '>=1.0',
)



sdk_source = files(
    'Lib/Shared/DarkEdif.cpp',
    'Lib/Shared/Edif.cpp',
    'Lib/Shared/Edif.General.cpp',
    'Lib/Shared/Edif.Runtime.cpp',
    'Lib/Shared/ObjectSelection.cpp',
    'Lib/Shared/json.cpp',
)


if(host_machine.system() == 'windows')
    sdk_source += files('Lib/Windows/Edif.Edittime.cpp')
endif

subdir('Tools')

ext_includes = include_directories(
    'Noise',
    'Lib/Shared',
    'Inc',
    'Inc/Shared',
)

ext_source = files(
    'Noise/Extension.cpp',
    'Noise/Properties.cpp',
    'Noise/ACE/Actions.cpp',
    'Noise/ACE/Expressions.cpp',
)

# a lot of defines
common_defines = []
editor_defines = []
runtime_defines = []

unicode = false

if(host_machine.system() == 'windows')
    unicode = true
endif

if(unicode)
    editor_defines += '-DCONFIG=Edittime Unicode'
    runtime_defines += '-DCONFIG=Runtime Unicode'
    common_defines += '-DUniBuild=1'
else
    editor_defines += '-DCONFIG=Edittime'
    runtime_defines += '-DCONFIG=Runtime'
    common_defines += '-DUniBuild=0'
endif

editor_defines += [
    '-DEditorBuild=1',
    '-DRuntimeBuild=0',
    '-DUSE_DARKEDIF_UPDATE_CHECKER=1',
]

runtime_defines += [
    '-DEditorBuild=0',
    '-DRuntimeBuild=1',
    '-DUSE_DARKEDIF_UPDATE_CHECKER=0',
]

common_defines += [
    '-DMacBuild=0',
    '-DPROJECT_NAME=STRIFY(Noise)',
    '-DPROJECT_NAME_UNDERSCORES=STRIFY(Noise)',
    '-DAUTHOR_NAME=STRIFY(Kacper Bugla)',
    '-DCOMPANY_NAME=STRIFY(Kacper Bugla)',
    '-DEXTENSION_VERSION=22',
    '-DYEAR=STRIFY(2024)',
    '-DUSE_DARKEDIF_FUSION_DEBUGGER=0',
]

if(host_machine.system() == 'windows')
    common_defines += [
        '-DUSE_DARKEDIF_UC_TAGGING=1',
        '-DNOMINMAX',
        '-DWIN32_LEAN_AND_MEAN',
        '-DSTRICT',
    ]
endif


mmfs2 = meson.get_compiler('cpp').find_library(
  'mmfs2',
  dirs: meson.project_source_root() / 'Lib' / 'Windows',
  required: true
)

deps = [
    dependency('threads'),
    mmfs2,
]

darkext_json = custom_target('DarkExt.json.h',
    input: 'Noise/DarkExt.json',
    output: 'DarkExt.json.h',
    command: [bin2hpp, '@INPUT@', '@OUTPUT@', 'darkExtJSON', 'darkExtJSON_len'],
)

acecalltable = custom_target('ACECallTable_Macro.cpp',
    input: files(
        # Order matters!
        'Lib/Shared/ACECallTable_Macro.cpp',
        'Noise/Extension.cpp',
        'Noise/Extension.hpp',
    ),
    output: 'Temp_ACECallTable.cpp',
    command: [acecalltablegen, '@INPUT@', '@OUTPUT@'],
    build_by_default: true,
)

if(host_machine.system() == 'windows')
    windows_module = import('windows')
    ext_rc = windows_module.compile_resources(
        'Noise/Ext.rc',
        args: [
            # TODO: Generate these arguments during build time
            '/DCONFIG=Edittime Unicode',
            '/DPROJECT_NAME=asStr(Noise)',
  			'/DAUTHOR_NAME=asStr(Kacper Bugla)',
            '/DCOMPANY_NAME=asStr(Kacper Bugla)',
  			'/DEXTENSION_VERSION=22',
            '/DYEAR=asStr(2024)',
  			'/DUSE_DARKEDIF_UPDATE_CHECKER=1',
  			'/DUSE_DARKEDIF_FUSION_DEBUGGER=0',
  			'/DEditorBuild=1',
            '/DRuntimeBuild=0',
            '/DUniBuild=1',
  			'/DUSE_DARKEDIF_UC_TAGGING=1',
            '/DMacBuild=0',
  			'/DBUILD_DATE=asStr(2024-09-04T17:59:54.9871294+00:00)',
        ],
    )

    if(get_option('debug') == false)
        runtime_ext = shared_library(
            'Runtime_' + meson.project_name(),
            ext_source,
            sdk_source,
            darkext_json,
            acecalltable,
            ext_rc,
            cpp_args: [common_defines, runtime_defines],
            link_args: ['/LARGEADDRESSAWARE'],
            include_directories: ext_includes,
            name_prefix: '',
            name_suffix: 'mfx',
            dependencies: deps,
        )
    endif

    editor_ext = shared_library(
        'Editor_' + meson.project_name(),
        ext_source,
        sdk_source,
        darkext_json,
        acecalltable,
        ext_rc,
        cpp_args: [common_defines, editor_defines],
        link_args: ['/LARGEADDRESSAWARE'],
        include_directories: ext_includes,
        name_prefix: '',
        name_suffix: 'mfx',
        dependencies: deps,
    )
endif

if(host_machine.system() == 'wasi')
    wasm_wasi_target = '--target=wasm32-wasi'

    runtime_ext = static_library(
        meson.project_name(),
        ext_source,
        sdk_source,
        darkext_json,
        acecalltable,
        cpp_args: [wasm_wasi_target, '-fno-exceptions', '-fvisibility=hidden', defines],
        include_directories: ext_includes,
        name_prefix: '',
        # name_suffix: 'wasm',
        dependencies: deps,
    )

    # Hack: Manualy start the linker because meson uses arguments not recognized by wasm-ld
    # https://github.com/mesonbuild/meson/pull/11862
    cpp_compiler = find_program('cpp', 'clang++')
    runtime_ext_wasm = custom_target('runtime_ext_wasm',
        build_by_default: true,
        input: runtime_ext.extract_all_objects(recursive: true),
        output: meson.project_name() + '.wasm',
        command: [cpp_compiler, wasm_wasi_target, '-Wl,--no-entry', '@INPUT@', '-o', '@OUTPUT@'],
    )


    # out_js = meson.current_build_dir() / meson.project_name() + '.js.in'
    # javascript wrapper that loads the webassembly
    npm = find_program('npm')
    html_ext_wrapper = custom_target('html_ext_wrapper',
        build_by_default: true,
        input: [runtime_ext_wasm, files('Lib/Html/Noise.ts')],  # meson uses this to determine if this needs to be run.
        output: meson.project_name() + '.js',
        command: [npm, '--prefix', meson.current_source_dir() / 'Lib' / 'Html', 'run', 'build', '--', '--outfile=' + meson.current_build_dir() / 'Noise.js', '--alias:Noise.wasm=' + runtime_ext_wasm.full_path()],
    )
endif