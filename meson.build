project(
    'Noise',
    'cpp',
    version: '1.2.1',
    license: 'MIT',
    default_options: {
        'cpp_std':       'c++17',
        # Workaround for: https://github.com/mesonbuild/meson/issues/5590
        'build.cpp_std': 'c++17',
        'warning_level': '1',
        'prefix':        meson.project_source_root() / 'MFX',   # Install prefix
    },
    meson_version: '>=1.2',
)

# Used by SDK meson.build file
ext_author = 'Kacper Bugla (kapi1525)'
ext_company = ext_author
ext_build = 27

ext_examples_path = meson.current_source_dir() / 'Examples'
ext_help_path = meson.current_source_dir() / 'Help'



subdir('sdk')

source = []
include = [include_directories('inc')]
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
    ext = custom_target(
        'wasm link',
        input: ext.extract_all_objects(recursive: true),
        output: meson.project_name() + '.raw.wasm',   # Added '.raw' to filename to stop meson from installing it without asking.
        depends: ext,
        command: [find_program('cpp'), '-o', '@OUTPUT@', '@INPUT@', '-fuse-ld='+find_program('cpp_ld').full_path(), sdk_link_args],
    )

    wasm_opt = find_program('wasm-opt', required: false)
    if wasm_opt.found() and get_option('optimization') == '3'
        ext = custom_target(
            'wasm optimize',
            input: ext,
            output: meson.project_name() + '.post_opt.wasm',
            depends: ext,
            command: [wasm_opt, '@INPUT@', '-O4', '-o', '@OUTPUT@'],
        )
    endif


    # javascript wrapper that loads the webassembly
    ext_js_out = meson.project_name() + '.js'

    run_target(
        'ts validate',
        command: [
            npm, 'exec',  '--',
            'tsc',
            meson.current_source_dir() / 'src/html/Noise.ts',
            '-t',
            'esnext',
            '--strict',
            '--module', 'preserve',
            '--moduleResolution', 'bundler',
            '--esModuleInterop',
            '--isolatedModules',
            '--noEmit',
        ],
    )

    custom_target(
        'create js bundle',
        input: [meson.current_source_dir() / 'src/html/Noise.ts'],
        output: ext_js_out,
        command: [
            npm, 'exec', '--prefix', meson.current_source_dir()/'sdk'/'lib'/'Html', '--',
            'esbuild',
            '@INPUT@',
            '--bundle',
            '--target=es6',
            '--loader:.wasm=binary',
            '--alias:Extension.wasm=' + ext.full_path(),
            '--global-name=CRun' + meson.project_name(),
            '--footer:js="CRun' + meson.project_name() + ' = CRun' + meson.project_name() + '.default;"',
            '--outfile=@OUTPUT@',
            '--analyze',
        ],
        build_by_default: true,
        build_always_stale: true,
        depends: ext,
        install: true,
        install_dir: install_prefix / ext_install_path,
    )
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