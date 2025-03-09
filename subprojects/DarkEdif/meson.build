project(
    'DarkEdif',
    'cpp', 'c',
    version: '19',
    license: 'MIT',
    default_options: {
        'cpp_std':          'c++17',
        'c_std':            'c11',
        'warning_level':    '1',
        'b_lto':            true,       # Enable lto
        'b_lto_mode':       'thin',     # thin lto apparently is better
    },
    meson_version: '>=1.2',
)

subdir('tools')



# Build config

# Only windows builds are unicode
unicode_build = host_machine.system() == 'windows'

editor_build = get_option('editor_build')
runtime_build = not editor_build
debug_build = get_option('debug')

config = 'Runtime'
if editor_build
    config = 'Edittime'
endif

if unicode_build
    config += ' Unicode'
endif

# All platforms except wasm are built as shared_module.
ext_build_type = 'shared_module'


sdk_source = []
sdk_include = []
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
    'EXTENSION_VERSION=' + get_option('ext_build').to_string(),
]

if not debug_build
    sdk_defines_common += 'NDEBUG'
endif

sdk_defines_project = [
    'PROJECT_NAME=STRIFY(' + meson.project_name() + ')',
    'PROJECT_NAME_UNDERSCORES=STRIFY(' + meson.project_name().underscorify() + ')',
    'EXTENSION_FANCY_VERSION=STRIFY(' + meson.project_version() + ')',
    'AUTHOR_NAME=STRIFY(' + get_option('ext_author') + ')',
    'COMPANY_NAME=STRIFY(' + get_option('ext_company') + ')',
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

if editor_build
    sdk_defines += sdk_defines_editor
else
    sdk_defines += sdk_defines_runtime
endif
ext_install_path = ''



# Additional build arguments
sdk_cpp_args = []
sdk_link_args = []


# Platform specific stuff
subdir('lib')
subdir('inc')



# Add all defines to build arguments
foreach def : sdk_defines
    sdk_cpp_args += '-D' + def
endforeach

darkedif_dep = declare_dependency(
    sources: sdk_source,
    include_directories: sdk_include,
    dependencies: sdk_deps,
    compile_args: sdk_cpp_args,
    link_args: sdk_link_args,
)
