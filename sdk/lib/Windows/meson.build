# Only windows

sdk_ext_name_suffix = 'mfx'


if editor_build and host_machine.system() != 'windows'
    error('Editor .mfx can only target windows!')
endif

if not editor_build and host_machine.system() == 'windows' and get_option('debug')
    error('Runtime windows builds cant be debug')
endif

if host_machine.system() == 'windows' and host_machine.cpu_family() != 'x86'
    error('All windows fusion extensions currently should be 32bit, but compiler is for: ' + host_machine.cpu_family())
endif


# Source files

if editor_build
    sdk_source += files(
        'Edif.Edittime.cpp',
    )
endif


# Dependencies

sdk_deps += meson.get_compiler('cpp').find_library(
    'mmfs2',
    dirs: meson.current_source_dir(),
    required: true
)


# Defines

sdk_defines += [
    '_WINDLL',
    'NOMINMAX',
    'WIN32_LEAN_AND_MEAN',
    'STRICT',
    'COXSDK',
    'HWABETA',
    '_CRT_SECURE_NO_WARNINGS',
    '_CRT_SECURE_NO_DEPRECATE',
]

sdk_defines_unicode = [
    '_UNICODE',
    'UNICODE',
]

sdk_defines_project_rc = [
    'KPX_MAGICNUMBER=200',
    'PROJECT_NAME=asStr(' + meson.project_name() + ')',
    'PROJECT_NAME_UNDERSCORES=asStr(' + meson.project_name().underscorify() + ')',
    'PROJECT_TARGET_NAME=asStr(' + meson.project_name() + ')',
    'PROJECT_TARGET_NAME_UNDERSCORES=asStr(' + meson.project_name().underscorify() + ')',
    'EXTENSION_FANCY_VERSION=asStr(' + meson.project_version() + ')',
    'EXTENSION_FANCY_VERSION_MAJOR=' + meson.project_version().split('.')[0],
    'EXTENSION_FANCY_VERSION_MINOR=' + meson.project_version().split('.')[1],
    'EXTENSION_FANCY_VERSION_PATCH=' + meson.project_version().split('.')[2],
    'AUTHOR_NAME=asStr(' + ext_author + ')',
    'COMPANY_NAME=asStr(' + ext_company + ')',
]

sdk_defines_rc = []
sdk_defines_rc += sdk_defines_common
sdk_defines_rc += sdk_defines_project_rc

if unicode_build
    sdk_defines += sdk_defines_unicode
    sdk_defines_rc += sdk_defines_unicode
endif

if get_option('editor_build')
    sdk_defines_rc += sdk_defines_editor
else
    sdk_defines_rc += sdk_defines_runtime
endif


# Additional build arguments

if meson.get_compiler('cpp').get_id() == 'msvc'
    sdk_cpp_args += [
        '/Zc:__cplusplus',
    ]
endif


# Linker arguments

if meson.get_compiler('cpp').get_linker_id() == 'link'
    sdk_link_args += [
        '/LARGEADDRESSAWARE',
        '/NOIMPLIB',                # This breaks when useing default meson install, they should add a native way to disable implib.
    ]
endif


# rc arguments

sdk_rc_args = []
foreach def : sdk_defines_rc
    sdk_rc_args += '/D' + def
endforeach


# Installing

sdk_can_simply_install = true
if editor_build
    ext_install_path = 'Extensions'
else
    ext_install_path = 'Data' / 'Runtime'
endif

if unicode_build
    ext_install_path = ext_install_path / 'Unicode'
endif