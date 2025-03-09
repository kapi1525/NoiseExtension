project(
    'Noise',
    'cpp', 'c',
    version: '1.2.0',
    license: 'MIT',
    default_options: {
        'cpp_std':          'c++17',
        'c_std':            'c11',
        'warning_level':    '1',
        'prefix':           meson.project_source_root() / 'MFX',    # Install prefix
        'b_lto':            true,                                   # Enable lto
        'b_lto_mode':       'thin',                                 # thin lto apparently is better
    },
    meson_version: '>=1.2',
)


sdk = subproject(
    'DarkEdif',
    default_options: {
        'editor_build': get_option('editor_build'),
        'ext_version':  meson.project_version(),
        'ext_build':    23,
        'ext_author':   'Kacper Bugla',
        'ext_company':  'Kacper Bugla',
    },
    required: true,
)

source = []
include = []
subdir('src')

deps = [
    sdk.get_variable('darkedif_dep')
]



ext = build_target(
    meson.project_name(),
    source,
    include_directories: include,
    dependencies: deps,
    target_type: sdk.get_variable('ext_build_type'),
    name_suffix: sdk.get_variable('ext_file_suffix'),
    install: sdk.get_variable('ext_simple_install'),
    install_dir: get_option('prefix') / sdk.get_variable('ext_install_path'),
)

if host_machine.system() == 'wasi'
    ext_js = meson.project_name() + '.js'

    # javascript wrapper that loads the webassembly
    ext = custom_target('js ext wrapper',
        input: [ext, sdk.get_variable('sdk_js_files')],
        output: ext_js,
        env: {
            'EXTWASMPATH': ext.full_path(),
            'OUTJSPATH': meson.current_build_dir() / ext_js,
        },
        command: sdk.get_variable('npm_build_command'),
        build_by_default: true,
        install: sdk.get_variable('ext_simple_install_js'),
        install_dir: get_option('prefix') / sdk.get_variable('ext_install_path'),
    )
endif


# Android extensions are packaged in a zip file, 7zip is needed to do that.

# TODO: Simplify?
if host_machine.system() == 'android'
    p7zip = find_program('7za', '7z', required: false)        # 7zip, p7zip on linux/mac

    install_emptydir(get_option('prefix') / sdk.get_variable('ext_install_path'))

    target_zip = get_option('prefix') / sdk.get_variable('ext_install_path') / meson.project_name() + '.zip'
    ext_filename = import('fs').name(ext.full_path())

    # Before adding a new file, the existing ones need to be deleted, 7zip can create duplicates for some reason
    meson.add_install_script(p7zip, 'd', target_zip, 'app' / 'src' / 'main' / 'java' / 'Extensions' / '*')
    meson.add_install_script(p7zip, 'd', target_zip, 'app' / 'src' / 'main' / 'jniLibs' / sdk.get_variable('ext_android_arch') / '*')

    # Add java and build native files to archive, then move them into correct paths
    meson.add_install_script(p7zip, 'a', target_zip, sdk.get_variable('ext_android_java_filepath'), ext.full_path())
    meson.add_install_script(p7zip, 'rn', target_zip, sdk.get_variable('ext_android_java_filename'), 'app' / 'src' / 'main' / 'java' / 'Extensions' / sdk.get_variable('ext_android_java_filename'))
    meson.add_install_script(p7zip, 'rn', target_zip, ext_filename, 'app' / 'src' / 'main' / 'jniLibs' / sdk.get_variable('ext_android_arch') / ext_filename)
endif

# Install examples and help file
install_subdir(meson.current_source_dir() / 'Examples', install_dir: get_option('prefix'))
install_subdir(meson.current_source_dir() / 'Help', install_dir: get_option('prefix'))