# TODO: Completely ditch visual studio and use meson instead.

project(
    'Noise',
    'cpp', 'c',
    version: '1.2.0',
    license: 'MIT',
    default_options: ['warning_level=1', 'cpp_std=c++17', 'c_std=c11'],
    meson_version: '>=1.0',
)



sdk_source = files(
    # 'Lib/Shared/ACECallTable_Macro.cpp',
    'Lib/Shared/DarkEdif.cpp',
    'Lib/Shared/Edif.cpp',
    'Lib/Shared/Edif.General.cpp',
    'Lib/Shared/Edif.Runtime.cpp',
    'Lib/Shared/ObjectSelection.cpp',
    'Lib/Shared/json.cpp',
)

ext_includes = include_directories(
    'Noise',
    'Lib/Shared',
    'Inc',
    'Inc/Shared',
)

ext_source = files(
    'Noise/Extension.cpp',
    'Noise/Properties.cpp',
    'Noise/ACE/Actions.cpp',
    'Noise/ACE/Expressions.cpp',
)

deps = [
    dependency('threads'),
]

defines = [
    '-DCONFIG=Runtime',
    '-DPROJECT_NAME=STRIFY(Noise)',
    '-DPROJECT_NAME_UNDERSCORES=STRIFY(Noise)',
    '-DAUTHOR_NAME=STRIFY(Kacper Bugla)',
    '-DCOMPANY_NAME=STRIFY(Kacper Bugla)',
    '-DEXTENSION_VERSION=22',
    '-DYEAR=STRIFY(2024)',
    '-DUSE_DARKEDIF_FUSION_DEBUGGER=0',
    '-DEditorBuild=0',
    '-DRuntimeBuild=1',
    '-DUniBuild=0',
    '-DMacBuild=0',
    '-DThreadSafeStaticInitIsSafe=1',
]

# FIXME: Broken on linux...
# prebuildtool = custom_target('DarkEdifPreBuildTool',
#     output: 'Temp_ACECallTable.cpp',
#     command:   ['wine', 'DarkEdifPreBuildTool.exe',
#                 '/ProjName="' + meson.project_name() + '"',
#                 '/TargetPlat="Html"', '/TargetArch="wasm32"',
#                 '/MacroInputFile="' + meson.project_source_root() + '\Lib\Shared\ACECallTable_Macro.cpp"',
#                 '/MacroOutputFile="@OUTPUT@"',
#                 '/JSONInputPathToMinify="' + meson.project_source_root() + '\DarkExt.json"',
#                 '/FusionConfigIniPath="' + meson.project_source_root() + 'FusionSDKConfig.ini"'
#         ],
# )

# ext_source += prebuildtool

wasm_wasi_target = '--target=wasm32-wasi'


darkext_json = custom_target('darkext_json',
    input: 'Noise/DarkExt.PostMinify.json',
    output: 'DarkExt.json.h',
    command: ['xxd', '-i', '-n', 'darkExtJSON', '@INPUT@', '@OUTPUT@'],
)

runtime_ext = static_library(
    meson.project_name(),
    ext_source,
    sdk_source,
    darkext_json,
    cpp_args: [wasm_wasi_target, '-fno-exceptions', '-fvisibility=hidden', defines],
    include_directories: ext_includes,
    name_prefix: '',
    # name_suffix: 'wasm',
    dependencies: deps,
)

# Hack: Manualy start the linker because meson uses arguments not recognized by wasm-ld
# https://github.com/mesonbuild/meson/pull/11862
cpp_compiler = find_program('cpp', 'clang++')
runtime_ext_wasm = custom_target('runtime_ext_wasm',
    build_by_default: true,
    input: runtime_ext.extract_all_objects(recursive: true),
    output: meson.project_name() + '.wasm',
    command: [cpp_compiler, wasm_wasi_target, '-Wl,--no-entry', '@INPUT@', '-o', '@OUTPUT@'],
)


# out_js = meson.current_build_dir() / meson.project_name() + '.js.in'
# javascript wrapper that loads the webassembly
npm = find_program('npm')
html_ext_wrapper = custom_target('html_ext_wrapper',
    build_by_default: true,
    input: [runtime_ext_wasm, files('Lib/Html/Noise.ts')],  # meson uses this to determine if this needs to be run.
    output: meson.project_name() + '.js',
    command: [npm, '--prefix', meson.current_source_dir() / 'Lib' / 'Html', 'run', 'build', '--', '--outfile=' + meson.current_build_dir() / 'Noise.js', '--alias:Noise.wasm=' + runtime_ext_wasm.full_path()],
)