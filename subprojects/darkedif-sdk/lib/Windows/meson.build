# Only windows

sdk_ext_name_suffix = 'mfx'



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

sdk_defines_rc = [
    'KPX_MAGICNUMBER=200',
    'EXTENSION_FANCY_VERSION_RC=' + meson.project_version().replace('.', ',').split('-')[0] + ',' + ext_version.to_string(),
]
sdk_defines_rc += sdk_defines_common

if unicode_build
    sdk_defines += sdk_defines_unicode
    sdk_defines_rc += sdk_defines_unicode
endif



# Additional build arguments

if meson.get_compiler('cpp').get_id() not in ['msvc', 'clang-cl']
    warning('Unsupported compiler: "' + meson.get_compiler('cpp').get_id() + '", expect problems.')
endif

sdk_cpp_args += [
    '/Zc:__cplusplus',
    '/permissive',      # TODO: Make this not needed, though probably not worth the effort
]

if meson.get_compiler('cpp').get_id() == 'clang-cl'
    sdk_cpp_args += [
        # Hide some unnecessary warnings
        '-Wno-unused-private-field',
        '-Wno-unknown-pragmas',
        '-Wno-unused-const-variable',
        '-Wno-overloaded-virtual',
    ]
endif


# Linker arguments

if meson.get_compiler('cpp').get_linker_id() not in ['link', 'lld-link']
    warning('Unsupported linker: "' + meson.get_compiler('cpp').get_linker_id() + '", expect problems.')
endif

sdk_link_args += [
    '/LARGEADDRESSAWARE',
    '/NOIMPLIB',
]


# rc arguments

sdk_rc_args = []
foreach def : sdk_defines_rc
    if meson.get_compiler('cpp').get_id() == 'clang-cl'
        # llvm-windres, cant check it, assume its always used with clang-cl
        sdk_rc_args += '-D' + def
    else
        # rc.exe
        sdk_rc_args += '/D' + def
    endif
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