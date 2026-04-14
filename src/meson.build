# Source files
source += files(
    'ace/Actions.cpp',
    'ace/Expressions.cpp',
    'Extension.cpp',
)

if sdk.get_variable('windows_build')
    source += files(
        'Edittime.cpp',
        'Properties.cpp',
    )
else
    # Ace call table
    source += custom_target('ACECallTable',
        input: files(
            # Order matters!
            'Extension.cpp',
            'Extension.hpp',
        ),
        output: 'Temp_ACECallTable.hpp',
        command: sdk.get_variable('acecalltablegen_cmd'),
    )
endif

include += include_directories('.')