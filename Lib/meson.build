# Only windows builds are unicode
unicode_build = host_machine.system() == 'windows'

editor_build = get_option('editor_build')
runtime_build = not editor_build

if editor_build and host_machine.system() != 'windows'
    error('Editor .mfx can only target windows!')
endif

if not editor_build and host_machine.system() == 'windows' and get_option('debug')
    error('Runtime windows builds cant be debug')
endif


if host_machine.system() == 'windows' and host_machine.cpu_family() != 'x86'
    error('All windows fusion extensions currently should be 32bit, but compiler is for: ' + host_machine.cpu_family())
endif



config = 'Runtime'
if editor_build
    config = 'Edittime'
endif

if unicode_build
    config += ' Unicode'
endif



sdk_ext_target_type = 'shared_module'

if host_machine.system() == 'wasi'
    # hack
    sdk_ext_target_type = 'static_library'
endif



sdk_source_shared = files(
    'Shared/DarkEdif.cpp',
    'Shared/Edif.cpp',
    'Shared/Edif.General.cpp',
    'Shared/Edif.Runtime.cpp',
    'Shared/json.cpp',
    'Shared/ObjectSelection.cpp',
)

sdk_source_windows = files(
    'Windows/Edif.Edittime.cpp',
)

sdk_source = sdk_source_shared

if host_machine.system() == 'windows'
    sdk_source += sdk_source_windows
endif


sdk_include = include_directories(
    'Shared',
    '../Inc',
    '../Inc/Shared',
)



sdk_deps = [
    dependency('threads'),
]

if host_machine.system() == 'windows'
    sdk_deps += meson.get_compiler('cpp').find_library(
        'mmfs2',
        dirs: meson.project_source_root() / 'Lib/Windows',
        required: true
    )
endif



sdk_defines = []
sdk_defines_rc = []

sdk_defines_common = [
    'CONFIG=' + config,
    'EditorBuild=' + editor_build.to_int().to_string(),
    'RuntimeBuild=' + runtime_build.to_int().to_string(),
    'UniBuild=' + unicode_build.to_int().to_string(),
    'MacBuild=0',
    'EXTENSION_VERSION=' + ext_build.to_string(),
]

sdk_defines_project = [
    'PROJECT_NAME=STRIFY(' + meson.project_name() + ')',
    'PROJECT_NAME_UNDERSCORES=STRIFY(' + meson.project_name().underscorify() + ')',
    'AUTHOR_NAME=STRIFY(' + ext_author + ')',
    'COMPANY_NAME=STRIFY(' + ext_company + ')',
    'YEAR=STRIFY(2024)',                        # TODO
]

sdk_defines_project_rc = [
    'KPX_MAGICNUMBER=200',
    'PROJECT_NAME=asStr(' + meson.project_name() + ')',
    'PROJECT_NAME_UNDERSCORES=asStr(' + meson.project_name().underscorify() + ')',
    'AUTHOR_NAME=asStr(' + ext_author + ')',
    'COMPANY_NAME=asStr(' + ext_company + ')',
    'YEAR=asStr(2024)',                        # TODO
    'BUILD_DATE=asStr(2024-10-09T18:14:24.1939030+00:00)',  # todo
]

if not get_option('debug')
    sdk_defines_common += 'NDEBUG'
endif

sdk_defines_unicode = [
    '_UNICODE',
    'UNICODE',
]

sdk_defines_editor = [
    'EDITOR',
    'USE_DARKEDIF_UPDATE_CHECKER=1',            # TODO
    'USE_DARKEDIF_FUSION_DEBUGGER=0',           # TODO
    'USE_DARKEDIF_UC_TAGGING=1',                # TODO
]

sdk_defines_runtime = [
    'RUN_ONLY',
    'USE_DARKEDIF_UPDATE_CHECKER=0',
    'USE_DARKEDIF_FUSION_DEBUGGER=0',
    'USE_DARKEDIF_UC_TAGGING=0',
]

sdk_defines_windows = [
    '_WINDLL',
    'NOMINMAX',
    'WIN32_LEAN_AND_MEAN',
    'STRICT',
    'COXSDK',
    'HWABETA',
    '_CRT_SECURE_NO_WARNINGS',
    '_CRT_SECURE_NO_DEPRECATE',
]


sdk_defines += sdk_defines_common
sdk_defines += sdk_defines_project
sdk_defines_rc += sdk_defines_common
sdk_defines_rc += sdk_defines_project_rc

if unicode_build
    sdk_defines += sdk_defines_unicode
    sdk_defines_rc += sdk_defines_unicode
endif

if get_option('editor_build') and host_machine.system() == 'windows'
    sdk_defines += sdk_defines_editor
    sdk_defines_rc += sdk_defines_editor
else
    sdk_defines += sdk_defines_runtime
    sdk_defines_rc += sdk_defines_runtime
endif

if host_machine.system() == 'windows'
    sdk_defines += sdk_defines_windows
endif



sdk_args = []

sdk_args_windows_msvc = [
    '/Zc:__cplusplus',
]

sdk_args_android_clang = [
    '-fvisibility=hidden',
    '-fsigned-char',
    '-fPIC',
    '-fasm-blocks',
    '-Wno-unknown-pragmas',
    '-Wno-unused-const-variable',
    '-Wno-missing-braces',
]

sdk_args_wasi_clang = [
    '--target=wasm32-wasi'
]


if host_machine.system() == 'windows' and meson.get_compiler('cpp').get_id() == 'msvc'
    sdk_args += sdk_args_windows_msvc
endif

if host_machine.system() == 'android' and meson.get_compiler('cpp').get_id() == 'clang'
    sdk_args += sdk_args_android_clang
endif

if host_machine.system() == 'wasi' and meson.get_compiler('cpp').get_id() == 'clang'
    sdk_args += sdk_args_wasi_clang
endif

foreach def : sdk_defines
    sdk_args += '-D' + def
endforeach


sdk_link_args = []

sdk_link_args_windows_link = [
    '/LARGEADDRESSAWARE',
    '/NOIMPLIB',                # This breaks when useing default meson install, they should add a native way to disable implib.
]

sdk_link_wasi_wasmld = [
    '--no-entry'
]


if host_machine.system() == 'windows' and meson.get_compiler('cpp').get_linker_id() == 'link'
    sdk_link_args += sdk_link_args_windows_link
endif

if host_machine.system() == 'wasi'
    sdk_link_args += sdk_link_wasi_wasmld
endif


sdk_args_rc = []

foreach def : sdk_defines_rc
    sdk_args_rc += '/D' + def
endforeach



if host_machine.system() != 'windows'
    acecalltable = custom_target('ACECallTable_Macro.cpp',
        input: files(
            # Order matters!
            meson.project_source_root() / 'Lib' / 'Shared' / 'ACECallTable_Macro.cpp',
            meson.project_source_root() / meson.project_name() / 'Extension.cpp',
            meson.project_source_root() / meson.project_name() / 'Extension.hpp',
        ),
        output: 'Temp_ACECallTable.cpp',
        command: [acecalltablegen, '@INPUT@', '@OUTPUT@'],
        build_by_default: true,
    )

    sdk_source += acecalltable
endif


darkedif_sdk = declare_dependency(
    sources: sdk_source,
    include_directories: sdk_include,
    dependencies: sdk_deps,
    compile_args: sdk_args,
    link_args: sdk_link_args,
)