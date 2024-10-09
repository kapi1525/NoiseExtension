
# Only windows builds are unicode
unicode = false

if host_machine.system() == 'windows'
    unicode = true
endif

config = 'Runtime'
if get_option('editor_build') and host_machine.system() == 'windows'
    config = 'Edittime'
endif

if unicode
    config += ' Unicode'
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

sdk_defines_common = [
    'CONFIG=' + config,
    'EditorBuild=' + get_option('editor_build').to_int().to_string(),
    'RuntimeBuild=' + (not get_option('editor_build')).to_int().to_string(),
    'UniBuild=' + unicode.to_int().to_string(),
    'MacBuild=0',
    'PROJECT_NAME=STRIFY(' + meson.project_name() + ')',
    'AUTHOR_NAME=STRIFY(Kacper Bugla)',         # TODO
    'COMPANY_NAME=STRIFY(Kacper Bugla)',        # TODO
    'EXTENSION_VERSION=22',                     # TODO
    'YEAR=STRIFY(2024)',                        # TODO
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

if unicode
    sdk_defines += sdk_defines_unicode
endif

if get_option('editor_build') and host_machine.system() == 'windows'
    sdk_defines += sdk_defines_editor
else
    sdk_defines += sdk_defines_runtime
endif

if host_machine.system() == 'windows'
    sdk_defines += sdk_defines_windows
endif



sdk_args = []

sdk_args_windows_msvc = [
    '/Zc:__cplusplus',
]


if host_machine.system() == 'windows' and meson.get_compiler('cpp').get_id() == 'msvc'
    sdk_args += sdk_args_windows_msvc
endif

foreach def : sdk_defines
    sdk_args += '-D' + def
endforeach


sdk_link_args = []

sdk_link_args_windows_link = [
    '/LARGEADDRESSAWARE'
]


if host_machine.system() == 'windows' and meson.get_compiler('cpp').get_linker_id() == 'link'
    sdk_link_args += sdk_link_args_windows_link
endif



darkedif_sdk = declare_dependency(
    sources: sdk_source,
    include_directories: sdk_include,
    dependencies: sdk_deps,
    compile_args: sdk_args,
    link_args: sdk_link_args,
)