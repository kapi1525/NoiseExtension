project(
    'DarkEdif',
    'cpp',
    version: '20.0',
    default_options: {
        'cpp_std':       'c++17',
        # Workaround for: https://github.com/mesonbuild/meson/issues/5590
        'build.cpp_std': 'c++17',
        'warning_level': '1',
    },
    meson_version: '>=1.4',
)

fs = import('fs')

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

message('Build config: ' + config)


windows_build = host_machine.system() == 'windows'
android_build = host_machine.system() == 'android'
wasm_build = host_machine.system() == 'wasi'

if editor_build and not windows_build
    error('Editor .mfx can only target windows!')
endif


ext_name          = get_option('ext_name')
ext_target_name   = get_option('ext_target_name')
if ext_target_name == ''
    ext_target_name = ext_name
endif
ext_author        = get_option('ext_author')
ext_company       = get_option('ext_company')
ext_version       = get_option('ext_version')
ext_fancy_version = get_option('ext_fancy_version')

extension_cpp_file = fs.read(get_option('extension_cpp_path'))
extension_hpp_file = fs.read(get_option('extension_hpp_path'))
edittime_cpp_file = fs.read(get_option('edittime_cpp_path'))

ext_has_oeflag_text = extension_hpp_file.contains('OEFLAGS::TEXT')
ext_has_oeflag_wndproc = extension_hpp_file.contains('OEFLAGS::WINDOW_PROC')
ext_pausable = get_option('ext_pausable').enabled()

ext_de_display_type = 0
foreach i : [
                'OEFLAGS::SPRITES',
                'OEFLAGS::ANIMATIONS',
                'OEFLAGS::QUICK_DISPLAY',
                'OEFLAGS::BACKGROUND',
                'OEFLAGS::MOVEMENTS',
                'OEFLAGS::SIMPLE_DISPLAY_EXT',
                'OEFLAGS::MANUAL_DISPLAY_EXT',
            ]
    if extension_hpp_file.contains(i)
        ext_de_display_type = 1
        break
    endif
endforeach

if ext_de_display_type == 1
    if extension_hpp_file.contains('OEFLAGS::SIMPLE_DISPLAY_EXT')
        ext_de_display_type = 2
    elif extension_hpp_file.contains('OEFLAGS::MANUAL_DISPLAY_EXT')
        ext_de_display_type = 3
    endif
    message('Detected DarkEdif display type: ' + ext_de_display_type.to_string())
endif


# Only ever enabled for editor builds, if auto, gets enabled if 'DarkEdif::SDKUpdater::RunUpdateNotifs(' is present in Edititme.cpp
use_de_update_checker = (get_option('use_de_update_checker').auto() and editor_build and edittime_cpp_file.contains('DarkEdif::SDKUpdater::RunUpdateNotifs(')) or (get_option('use_de_update_checker').enabled() and editor_build)
use_de_update_checker_tagging = get_option('use_de_update_checker_tagging').enabled()
# If auto, gets enabled if 'DarkEdif::FusionDebugger' is present in 'Extension.hpp'
use_de_fusion_debugger = (get_option('use_de_fusion_debugger').auto() and extension_hpp_file.contains('DarkEdif::FusionDebugger')) or get_option('use_de_fusion_debugger').enabled()

if use_de_update_checker
    message('DarkEdif update checker enabled')
endif
if use_de_update_checker_tagging
    message('DarkEdif update checker tagging enabled')
endif
if use_de_fusion_debugger
    message('DarkEdif fusion debugger enabled')
endif




subdir('tools')
subdir('inc')
subdir('lib')



darkedif_sdk_dep = declare_dependency(
    sources: sdk_source,
    include_directories: sdk_include,
    dependencies: sdk_deps,
    compile_args: sdk_cpp_args,
    link_args: sdk_link_args,
)