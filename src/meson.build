# Source files
source += files(
    'ace/Actions.cpp',
    'ace/Expressions.cpp',
    'Extension.cpp',
)

if host_machine.system() == 'windows'
    source += files(
        'Edittime.cpp',
        'Properties.cpp',
    )
endif

if host_machine.system() != 'windows'
    source += sdk.get_variable('acecalltablegen').process(
        'ACECallTable.hpp',
        extra_args: [
            meson.current_source_dir() / 'Extension.cpp',
            meson.current_source_dir() / 'Extension.hpp'
        ],
    )
endif


include += include_directories('.')



# JSON
if sdk.get_variable('runtime_build')
    # runtime builds use minified json
    darkext_json = sdk.get_variable('jsonminify').process(files('DarkExt.json'))
else
    darkext_json = files('DarkExt.json')
endif

source += sdk.get_variable('bin2hpp').process(darkext_json, extra_args: ['DarkExtJSON', 'DarkExtJSON_len'])



# Windows resources
if host_machine.system() == 'windows'
    source += import('windows').compile_resources(
        'Ext.rc',
        args: sdk.get_variable('sdk_rc_args'),
        depend_files: [
            'Resource.h',
            'Icon.png',
        ],
        include_directories: sdk.get_variable('sdk_include'),
    )
endif