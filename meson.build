project(
    'Noise',
    'cpp', 'c',
    version: '1.2.0',
    license: 'MIT',
    default_options: {
        'cpp_std':       'c++17',
        'c_std':         'c11',
        # Workaround for: https://github.com/mesonbuild/meson/issues/5590
        'build.cpp_std': 'c++17',
        'build.c_std':   'c11',
        'warning_level': '1',
        'b_lto':         'true',                                # Enable lto
        'b_lto_mode':    'thin',                                # thin lto apparently is better
        'prefix':        meson.project_source_root() / 'MFX',   # Install prefix
    },
    meson_version: '>=1.2',
)

# Used by SDK meson.build file
ext_author = 'Kacper Bugla'
ext_company = ext_author
ext_build = 23

ext_examples_path = meson.current_source_dir() / 'Examples'
ext_help_path = meson.current_source_dir() / 'Help'



subdir('sdk')

source = []
include = []
subdir('src')
subdir('res')



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

if host_machine.system() == 'wasi'
    ext_js_out = meson.project_name() + '.js'

    wasm_opt = find_program('wasm-opt', required: false)
    if wasm_opt.found() and get_option('optimization') == '3'
        ext = custom_target(
            'optimize',
            input: ext,
            output: meson.project_name() + '.post_opt.wasm',
            depends: ext,
            command: [wasm_opt, '@INPUT@', '-O4', '-o', '@OUTPUT@'],
        )
    endif


    # javascript wrapper that loads the webassembly
    ext_js = custom_target('js ext wrapper',
        depends: ext,
        output: ext_js_out,
        env: sdk_js_ext_wrapper_env + {
            'ENTRY': meson.current_source_dir() / 'src/html/Noise.ts',
            'EXTWASMPATH': ext.full_path(),
            'OUTPUTPATH': meson.current_build_dir() / ext_js_out,
        },
        kwargs: sdk_js_ext_wrapper_kwargs,
    )


    rm = find_program('rm', required: false)
    if rm.found()
        # Dumb hack: .wasm file gets installed even though it has install: false
        # Probably a meson bug or intended "feature". just remove that file for now
        meson.add_install_script(rm, '-f', install_prefix / ext_install_path / 'Noise.wasm')
    elif build_machine.system() == 'windows'
        cmd = find_program('cmd', required: false)
        if cmd.found()
            # On windows del command is not a program so start a cmd.
            meson.add_install_script(cmd, '/c', '"del /q ' + (install_prefix / ext_install_path / 'Noise.wasm') + '.txt"')
        endif
    endif
endif


# Android extensions are packaged in a zip file, 7zip is needed to do that.
p7zip = find_program('7za', '7z', required: false)        # 7zip, p7zip on linux/mac

# TODO: Simplify?
if host_machine.system() == 'android' and p7zip.found()
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
if install_examples
    install_subdir(ext_examples_path, install_dir: install_prefix)
endif
if install_help
    install_subdir(ext_help_path, install_dir: install_prefix)
endif