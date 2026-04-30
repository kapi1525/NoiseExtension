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
    'Shared/SurfaceMultiPlat.cpp',
)


# Defines
# Common for C++ and RC file
sdk_defines_common = [
    'CONFIG=' + config,
    # EDITOR and RUN_ONLY are not defined, use EditorBuild and RuntimeBuild defines instead
    'EditorBuild=' + editor_build.to_int().to_string(),
    'RuntimeBuild=' + runtime_build.to_int().to_string(),
    'UniBuild=' + unicode_build.to_int().to_string(),
    'MacBuild=0',

    'PROJECT_NAME=DE_STRIFY(' + ext_name + ')',
    'PROJECT_NAME_UNDERSCORES=DE_STRIFY(' + ext_name.underscorify() + ')',
    'PROJECT_TARGET_NAME=DE_STRIFY(' + ext_target_name + ')',
    'PROJECT_TARGET_NAME_UNDERSCORES=DE_STRIFY(' + ext_target_name.underscorify() + ')',
    'EXTENSION_VERSION=' + ext_version.to_string(),
    'EXTENSION_FANCY_VERSION=DE_STRIFY(' + ext_fancy_version + ')',

    'AUTHOR_NAME=DE_STRIFY(' + ext_author + ')',
    'COMPANY_NAME=DE_STRIFY(' + ext_company + ')',

    # FIXME:
    'TEXT_OEFLAG_EXTENSION=' + ext_has_oeflag_text.to_string(),
    'WNDPROC_OEFLAG_EXTENSION=' + ext_has_oeflag_wndproc.to_string(),
    'PAUSABLE_EXTENSION=' + ext_pausable.to_int().to_string(),
    'DARKEDIF_DISPLAY_TYPE=' + ext_de_display_type.to_string(),

    'MMF2EXTS_COMMIT_SHA=DE_STRIFY(' + fs.read('../MMF2ExtsCommit.txt') + ')',

    'USE_DARKEDIF_UPDATE_CHECKER=' + use_de_update_checker.to_int().to_string(),
    'USE_DARKEDIF_FUSION_DEBUGGER=' + use_de_fusion_debugger.to_int().to_string(),
    'USE_DARKEDIF_UC_TAGGING=' + use_de_update_checker_tagging.to_int().to_string(),
]

if get_option('debug')
    sdk_defines_common += '_DEBUG'
else
    sdk_defines_common += 'NDEBUG'
endif




sdk_defines = []
sdk_defines += sdk_defines_common



# Additional build arguments
sdk_cpp_args = []
sdk_link_args = []


# Dependencies
sdk_deps = []

# Threads are not supported by wasi yet
if host_machine.system() != 'wasi'
    sdk_deps += dependency('threads')
endif


# Installing
ext_install_path = ''


# Platform specific stuff
if windows_build
    subdir('Windows')
elif android_build
    subdir('Android')
elif wasm_build
    subdir('Html')
else
    error('Unsuported system!')
endif


# Add all defines to build arguments
foreach def : sdk_defines
    sdk_cpp_args += '-D' + def
endforeach




