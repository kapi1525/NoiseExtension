project(
    'Noise',
    'cpp', 'c',
    version: '1.2.0',
    license: 'MIT',
    default_options: [
        'warning_level=1',
        'cpp_std=c++17',
        'c_std=c11',
        'prefix=' + meson.project_source_root() / 'MFX',    # Install prefix
        'b_lto=true',                                       # Enable lto
        'b_lto_mode=thin',                                  # thin lto apparently is better
    ],
    meson_version: '>=1.1',
)

# FIXME: This setup is also insane, less than visual studio but, this should realy be simplified.

# Used by SDK meson.build file
ext_author = 'Kacper Bugla'
ext_company = 'Kacper Bugla'
ext_build = 23

ext_examples_path = meson.current_source_dir() / 'Examples'
ext_help_path = meson.current_source_dir() + '/Help'



fs = import('fs')

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


if runtime_build
    # runtime builds use minified json
    darkext_json = custom_target('minify_json',
        build_by_default: true,
        input: files('Noise/DarkExt.json'),
        output: 'DarkExt.PostMinify.json',
        command: [jsonminify, '@INPUT@', '@OUTPUT@'],
    )
else
    darkext_json = files('Noise/DarkExt.json')
endif

ext_source += custom_target('embed_json',
    input: darkext_json,
    output: 'DarkExt.json.h',
    command: [bin2hpp, '@INPUT@', '@OUTPUT@', 'DarkExtJSON', 'DarkExtJSON_len'],
)

if host_machine.system() == 'windows'
    ext_source += import('windows').compile_resources(
        'Noise\Ext.rc',
        args: sdk_rc_args,
        depend_files: [
            'Noise\Resource.h',
            'Noise\Icon.png',
        ],
        include_directories: sdk_include,
    )
endif


ext = build_target(
    meson.project_name(),
    ext_source,
    target_type: sdk_ext_target_type,
    dependencies: darkedif_sdk,
    include_directories: ext_include,
    name_suffix: sdk_ext_name_suffix,
    install: sdk_can_simply_install,
    install_dir: install_prefix / ext_install_path,
)

if host_machine.system() == 'wasi'
    # javascript wrapper that loads the webassembly

    ext = custom_target(meson.project_name() + '_js',
        input: [ext, sdk_js_files],
        output: meson.project_name() + '.js',
        env: {
            'EXTWASMPATH': ext.full_path(),
            'OUTJSPATH': meson.current_build_dir() / 'Noise.js',
        },
        command: [npm, '--prefix', npm_package_root, 'run', 'build'],
        build_by_default: true,
        install: sdk_can_simply_install,
        install_dir: install_prefix / ext_install_path,
    )
endif


p7zip = find_program('7za', '7z', required: false)        # 7zip, p7zip on linux/mac

if host_machine.system() == 'android'
    install_emptydir(install_prefix / ext_install_path)

    target_zip = install_prefix / ext_install_path / meson.project_name() + '.zip'
    ext_filename = fs.name(ext.full_path())

    # Before adding a new file, the existing ones need to be deleted, 7zip can create duplicates for some reason
    meson.add_install_script(p7zip, 'd', target_zip, 'app' / 'src' / 'main' / 'java' / 'Extensions' / '*')
    meson.add_install_script(p7zip, 'd', target_zip, 'app' / 'src' / 'main' / 'jniLibs' / ext_android_arch / '*')

    # Add java and build native files to archive, then move them into correct paths
    meson.add_install_script(p7zip, 'a', target_zip, meson.project_source_root() / 'Lib' / 'Android' / ext_android_java_filename, ext.full_path())
    meson.add_install_script(p7zip, 'rn', target_zip, ext_android_java_filename, 'app' / 'src' / 'main' / 'java' / 'Extensions' / ext_android_java_filename)
    meson.add_install_script(p7zip, 'rn', target_zip, ext_filename, 'app' / 'src' / 'main' / 'jniLibs' / ext_android_arch / ext_filename)
endif

install_subdir(ext_examples_path, install_dir: install_prefix)
install_subdir(ext_help_path, install_dir: install_prefix)

