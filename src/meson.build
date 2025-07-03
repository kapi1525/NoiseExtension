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

include += include_directories('.')