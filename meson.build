project(
    'Noise',
    'cpp', 'c',
    version: '1.2.0',
    license: 'MIT',
    default_options: ['warning_level=1', 'cpp_std=c++17', 'c_std=c11', 'prefix=' + meson.project_source_root()],
    meson_version: '>=1.1',
)

# Used by SDK meson.build file
ext_author = 'Kacper Bugla'
ext_company = 'Kacper Bugla'
ext_build = 22

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
        args: sdk_args_rc,
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
)

if host_machine.system() == 'wasi'
    # Hack: Manualy start the linker because meson uses arguments not recognized by wasm-ld
    # https://github.com/mesonbuild/meson/pull/11862
    cpp_compiler = find_program('cpp', 'clang++')

    ext_wasm = custom_target(meson.project_name() + '_wasm',
        build_by_default: true,
        input: ext.extract_all_objects(recursive: true),
        output: meson.project_name() + '.wasm',
        command: [cpp_compiler, '--target=wasm32-wasi', '-Wl,--no-entry', '@INPUT@', '-o', '@OUTPUT@'],
    )

    # javascript wrapper that loads the webassembly
    npm = find_program('npm')
    ext = custom_target(meson.project_name() + '_js',
        build_by_default: true,
        input: [ext_wasm, files('Lib/Html/Noise.ts')],  # meson uses this to determine if this needs to be run.
        output: meson.project_name() + '.js',
        command: [npm, '--prefix', meson.current_source_dir() / 'Lib' / 'Html', 'run', 'build', '--', '--outfile=' + meson.current_build_dir() / 'Noise.js', '--alias:Noise.wasm=' + ext_wasm.full_path()],
    )
endif

copy = find_program('cp', 'xcopy', required: false) # TODO: xcopy on windows requires /y flag
p7zip = find_program('7za', required: false)        # 7zip, p7zip on linux/mac

install_emptydir(install_prefix / ext_install_path)

if host_machine.system() != 'android'
    meson.add_install_script(copy, ext.full_path(), install_prefix / ext_install_path)
else
    target_zip = install_prefix / ext_install_path / meson.project_name() + '.zip'
    ext_filename = fs.name(ext.full_path())

    # Before adding a new file, the existing ones need to be deleted, 7zip can create duplicates for some reason
    meson.add_install_script(p7zip, 'd', target_zip, meson.project_name() / 'app' / 'src' / 'main' / 'java' / 'Extensions' / '*')
    meson.add_install_script(p7zip, 'd', target_zip, meson.project_name() / 'app' / 'src' / 'main' / 'jniLibs' / ext_android_arch / '*')

    # Add java and build native files to archive, then move them into correct paths
    meson.add_install_script(p7zip, 'a', target_zip, meson.project_source_root() / 'Lib' / 'Android' / ext_android_java_filename, ext.full_path())
    meson.add_install_script(p7zip, 'rn', target_zip, ext_android_java_filename, meson.project_name() / 'app' / 'src' / 'main' / 'java' / 'Extensions' / ext_android_java_filename)
    meson.add_install_script(p7zip, 'rn', target_zip, ext_filename, meson.project_name() / 'app' / 'src' / 'main' / 'jniLibs' / ext_android_arch / ext_filename)
endif

install_subdir(ext_examples_path, install_dir: install_prefix)
install_subdir(ext_help_path, install_dir: install_prefix)

