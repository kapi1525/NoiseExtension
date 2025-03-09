# Generates ACECallTable_Macro.cpp
# Partial replacement for DarkEdifPreBuildTool.
acecalltablegen_exe = executable(
    'acecalltablegen',
    files('acecalltablegen.cpp'),
    native: true,
    build_by_default: false,
)

acecalltablegen = generator(
    acecalltablegen_exe,
    arguments: ['@INPUT@', '@EXTRA_ARGS@', '@OUTPUT@'],
    output: 'Temp_@PLAINNAME@',
)



# Ace call table
# if host_machine.system() != 'windows'
#     acecalltable = custom_target('Temp_ACECallTable.hpp',
#         input: files(
#             # Order matters!
#             meson.current_source_dir() / 'ACECallTable_Macro.hpp',
#             get_option('ext_cpp'),
#             get_option('ext_hpp'),
#         ),
#         output: 'Temp_ACECallTable.hpp',
#         command: [acecalltablegen, '@INPUT@', '@OUTPUT@'],
#         build_by_default: true,
#     )


#     sdk_source += acecalltable
# endif