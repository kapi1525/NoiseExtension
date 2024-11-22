# Only html/wasm/wasi

sdk_ext_name_suffix = 'wasm'


# Additional linker arguments

sdk_link_args += [
    '--no-entry',
]


# Install javascript dependencies
npm = find_program('npm')
npm_package_root = meson.project_source_root() / 'Lib' / 'Html'

run_command(npm, '--prefix', npm_package_root, 'i', '--save-dev',
    check: true,
)


# C bindings for imports/exports from/into js land

# Used to create a C header with all wasm imports and exports defined in .wit file.
# wit_bindgen = find_program('wit-bindgen')

# sdk_source += custom_target('wit_c_bindings',
#     input: meson.project_source_root() / 'Lib' / 'Html' / 'sdk.wit',
#     output: [
#         'wasm_ext.c',
#         'wasm_ext.h',
#         'wasm_ext_component_type.o',
#     ],
#     command: [wit_bindgen, 'c', '@INPUT@', '--out-dir', meson.current_build_dir()],
#     build_by_default: true,
# )


# Installing

ext_install_path = 'Data' / 'Runtime' / 'Html5'