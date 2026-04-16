project(
    'Noise',
    'cpp',
    version: '1.2.1',
    license: 'MIT',
    default_options: {
        'cpp_std':       'c++17',
        'warning_level': '1',
        'prefix':        meson.project_source_root() / 'MFX',   # Install prefix
    },
    meson_version: '>=1.4',
)

fs = import('fs')

ext_version = 27
ext_examples_path = meson.current_source_dir() / 'Examples'
ext_help_path = meson.current_source_dir() / 'Help'


sdk = subproject('darkedif-sdk', default_options: {
    'ext_name': meson.project_name(),
    'ext_author': 'Kacper Bugla (kapi1525)',
    'ext_company': 'Kacper Bugla (kapi1525)',
    'ext_version': ext_version,
    'ext_fancy_version': meson.project_version(),

    'extension_cpp_path': meson.current_source_dir() / 'src' / 'Extension.cpp',
    'extension_hpp_path': meson.current_source_dir() / 'src' / 'Extension.hpp',
    'edittime_cpp_path': meson.current_source_dir() / 'src' / 'Edittime.cpp',
})

source = []
include = [include_directories('inc')]
subdir('src')
subdir('res')



ext = build_target(
    meson.project_name(),
    source,
    target_type: sdk.get_variable('sdk_ext_target_type'),
    dependencies: sdk.get_variable('darkedif_sdk_dep'),
    include_directories: include,
    name_suffix: sdk.get_variable('sdk_ext_name_suffix'),
    install: sdk.get_variable('sdk_can_simply_install'),
    install_dir: get_option('prefix') / sdk.get_variable('ext_install_path'),
)

if host_machine.system() == 'wasi'
    ext = custom_target(
        'wasm link',
        input: ext.extract_all_objects(recursive: true),
        output: meson.project_name() + '.raw.wasm',   # Added '.raw' to filename to stop meson from installing it without asking.
        depends: ext,
        command: [find_program('cpp'), '-o', '@OUTPUT@', '@INPUT@', '-fuse-ld='+find_program('cpp_ld').full_path(), sdk.get_variable('sdk_link_args')],
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
            sdk.get_variable('npm'), 'exec',  '--',
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
            sdk.get_variable('npm'), 'exec', '--prefix', sdk.get_variable('npm_prefix'), '--',
            'esbuild',
            '@INPUT@',
            '--bundle',
            '--target=es6',
            '--loader:.wasm=binary',
            '--alias:Extension.wasm=' + ext.full_path(),
            '--global-name=CRun' + meson.project_name(),
            '--footer:js=CRun' + meson.project_name() + ' = CRun' + meson.project_name() + '.default;',
            '--outfile=@OUTPUT@',
            '--analyze',
        ],
        build_by_default: true,
        build_always_stale: true,
        depends: ext,
        install: true,
        install_dir: get_option('prefix') / sdk.get_variable('ext_install_path'),
    )
endif


# Android extensions are packaged in a zip file, 7zip is needed to do that.
p7zip = find_program('7z', '7zzs', '7zz', '7za', '7zr', required: false)        # 7zip

# TODO: Simplify?
if host_machine.system() == 'android' and p7zip.found()
    install_emptydir(get_option('prefix') / sdk.get_variable('ext_install_path'))

    target_zip = get_option('prefix') / sdk.get_variable('ext_install_path') / meson.project_name() + '.zip'
    ext_filename = fs.name(ext.full_path())

    # Before adding a new file, the existing ones need to be deleted, 7zip can create duplicates for some reason
    meson.add_install_script(p7zip, 'd', target_zip, 'app' / 'src' / 'main' / 'java' / 'Extensions' / '*')
    meson.add_install_script(p7zip, 'd', target_zip, 'app' / 'src' / 'main' / 'jniLibs' / sdk.get_variable('ext_android_arch') / '*')

    # Add java and build native files to archive, then move them into correct paths
    meson.add_install_script(p7zip, 'a', target_zip, sdk.get_variable('ext_android_java_wrapper').full_path(), ext.full_path())
    meson.add_install_script(p7zip, 'rn', target_zip, fs.name(sdk.get_variable('ext_android_java_wrapper')), 'app' / 'src' / 'main' / 'java' / 'Extensions' / fs.name(sdk.get_variable('ext_android_java_wrapper')))
    meson.add_install_script(p7zip, 'rn', target_zip, ext_filename, 'app' / 'src' / 'main' / 'jniLibs' / sdk.get_variable('ext_android_arch') / ext_filename)
endif

# Install examples and help file
if get_option('examples').enabled() or (get_option('examples').auto() and get_option('editor_build'))
    install_subdir(ext_examples_path, install_dir: get_option('prefix'))
endif
if get_option('help').enabled() or (get_option('help').auto() and get_option('editor_build'))
    install_subdir(ext_help_path, install_dir: get_option('prefix'))
endif