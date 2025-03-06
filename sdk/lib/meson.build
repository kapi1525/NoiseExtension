# Common


# Build config

# Only windows builds are unicode
unicode_build = host_machine.system() == 'windows'

editor_build = get_option('editor_build')
runtime_build = not editor_build

config = 'Runtime'
if editor_build
    config = 'Edittime'
endif

if unicode_build
    config += ' Unicode'
endif


# All platforms except wasm are built as shared_module.
sdk_ext_target_type = 'shared_module'


# Source files

sdk_source = files(
    'Shared/DarkEdif.cpp',
    'Shared/Edif.cpp',
    'Shared/Edif.General.cpp',
    'Shared/Edif.Runtime.cpp',
    'Shared/json.cpp',
    'Shared/ObjectSelection.cpp',
)


# Includes

sdk_include = include_directories(
    'Shared',
    '..' / 'inc',
    '..' / 'inc' / 'Shared',
)


# Dependencies

sdk_deps = []

# Threads are not supported by wasi yet
if host_machine.system() != 'wasi'
    sdk_deps += dependency('threads')
endif


# Defines

sdk_defines_common = [
    'CONFIG=' + config,
    'EditorBuild=' + editor_build.to_int().to_string(),
    'RuntimeBuild=' + runtime_build.to_int().to_string(),
    'UniBuild=' + unicode_build.to_int().to_string(),
    'MacBuild=0',
    'EXTENSION_VERSION=' + ext_build.to_string(),
]

if not get_option('debug')
    sdk_defines_common += 'NDEBUG'
endif

sdk_defines_project = [
    'PROJECT_NAME=STRIFY(' + meson.project_name() + ')',
    'PROJECT_NAME_UNDERSCORES=STRIFY(' + meson.project_name().underscorify() + ')',
    'EXTENSION_FANCY_VERSION=STRIFY(' + meson.project_version() + ')',
    'AUTHOR_NAME=STRIFY(' + ext_author + ')',
    'COMPANY_NAME=STRIFY(' + ext_company + ')',
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


sdk_defines = []
sdk_defines += sdk_defines_common
sdk_defines += sdk_defines_project

if get_option('editor_build')
    sdk_defines += sdk_defines_editor
else
    sdk_defines += sdk_defines_runtime
endif


# Additional build arguments

sdk_cpp_args = []


# Linker arguments

sdk_link_args = []


# Ace call table

if host_machine.system() != 'windows'
    acecalltable = custom_target('ACECallTable_Macro.hpp',
        input: files(
            # Order matters!
            meson.current_source_dir() / 'Shared' / 'ACECallTable_Macro.hpp',
            meson.project_source_root() / 'src/Extension.cpp',
            meson.project_source_root() / 'src/Extension.hpp',
        ),
        output: 'Temp_ACECallTable.hpp',
        command: [acecalltablegen, '@INPUT@', '@OUTPUT@'],
        build_by_default: true,
    )

    sdk_source += acecalltable
endif


# Installing

install_prefix = get_option('prefix')
ext_install_path = ''


# Platform specific stuff
if host_machine.system() == 'windows'
    subdir('Windows')
elif host_machine.system() == 'android'
    subdir('Android')
elif host_machine.system() == 'wasi'
    subdir('Html')
else
    error('Unsuported system!')
endif


# Add all defines to build arguments
foreach def : sdk_defines
    sdk_cpp_args += '-D' + def
endforeach




darkedif_sdk = declare_dependency(
    sources: sdk_source,
    include_directories: sdk_include,
    dependencies: sdk_deps,
    compile_args: sdk_cpp_args,
    link_args: sdk_link_args,
)
