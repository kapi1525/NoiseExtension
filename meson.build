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

# Used by SDK meson.build file
ext_author = 'Kacper Bugla'
ext_company = 'Kacper Bugla'
ext_build = 23

ext_examples_path = meson.current_source_dir() / 'Examples'
ext_help_path = meson.current_source_dir() + '/Help'



subdir('sdk')

source = []
include = []
subdir('src')



ext = build_target(
    meson.project_name(),
    source,
    target_type: sdk_ext_target_type,
    dependencies: darkedif_sdk,
    include_directories: include,
    name_suffix: sdk_ext_name_suffix,
    install: sdk_can_simply_install,
    install_dir: install_prefix / ext_install_path,
)

# TODO: Fix wasm builds on windows, acecalltablegen fails to compile for some reason
if host_machine.system() == 'wasi'
    ext_js_out = meson.project_name() + '.js'

    # javascript wrapper that loads the webassembly
    ext_js = custom_target('js ext wrapper',
        depend_files: sdk_js_files,
        depends: ext,
        output: ext_js_out,
        env: {
            'EXTWASMPATH': ext.full_path(),
            'OUTJSPATH': meson.current_build_dir() / ext_js_out,
        },
        command: [npm, '--prefix', npm_package_root, 'run', 'build'],
        build_by_default: true,
        install: true,
        install_dir: install_prefix / ext_install_path,
    )

    rm = find_program('rm', required: false)
    if rm.found()
        # Dumb hack: .wasm file gets installed even though it has install: false
        # Probably a meson bug or intended "feature". just remove that file for now
        meson.add_install_script(rm, '-f', install_prefix / ext_install_path / 'Noise.wasm')
    elif build_machine.system() == 'windows' and (cmd = find_program('cmd', required: false)).found()
        # On windows del command is not a program so start a cmd.
        meson.add_install_script(cmd, '/c', '"del /q ' + (install_prefix / ext_install_path / 'Noise.wasm') + '.txt"')
    endif
endif


# Android extensions are packaged in a zip file, 7zip is needed to do that.
p7zip = find_program('7za', '7z', required: false)        # 7zip, p7zip on linux/mac

# TODO: Simplify?
if host_machine.system() == 'android'
    install_emptydir(install_prefix / ext_install_path)

    target_zip = install_prefix / ext_install_path / meson.project_name() + '.zip'
    ext_filename = import('fs').name(ext.full_path())

    # Before adding a new file, the existing ones need to be deleted, 7zip can create duplicates for some reason
    meson.add_install_script(p7zip, 'd', target_zip, 'app' / 'src' / 'main' / 'java' / 'Extensions' / '*')
    meson.add_install_script(p7zip, 'd', target_zip, 'app' / 'src' / 'main' / 'jniLibs' / ext_android_arch / '*')

    # Add java and build native files to archive, then move them into correct paths
    meson.add_install_script(p7zip, 'a', target_zip, ext_android_java_filepath, ext.full_path())
    meson.add_install_script(p7zip, 'rn', target_zip, ext_android_java_filename, 'app' / 'src' / 'main' / 'java' / 'Extensions' / ext_android_java_filename)
    meson.add_install_script(p7zip, 'rn', target_zip, ext_filename, 'app' / 'src' / 'main' / 'jniLibs' / ext_android_arch / ext_filename)
endif

# Install examples and help file
install_subdir(ext_examples_path, install_dir: install_prefix)
install_subdir(ext_help_path, install_dir: install_prefix)