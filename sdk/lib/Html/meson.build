# Only html/wasm/wasi

sdk_ext_name_suffix = 'wasm'
sdk_ext_target_type = 'executable'


# Additional linker arguments

sdk_link_args += [
    '-Wl,--no-entry',
]

if not get_option('debug')
    sdk_link_args += [
        '-Wl,--strip-debug'
    ]
endif


# Install javascript dependencies
npm = find_program('npm')
npm = [npm, '--prefix', meson.current_source_dir()]

run_command(npm, 'i', '--save-dev',
    check: true,
)



sdk_base_wasm_ext_wrapper = meson.current_source_dir() / 'CRunWasmExtWrapper.ts'



sdk_js_ext_wrapper_env = {
    'ENTRY': sdk_base_wasm_ext_wrapper,
    'TOTYPECHECK': ' '.join([sdk_base_wasm_ext_wrapper, meson.current_source_dir() / '*.ts']),
    'NODE_PATH': meson.current_source_dir(),    # esbuild uses this by default to search for extra dependencies
    'EXTNAME': meson.project_name(),
    'EXTWASMPATH': 'REPLACE',
    'OUTPUTPATH': 'REPLACE',
}


sdk_js_ext_wrapper_kwargs = {
    'command': [npm, 'run', 'build'],
    'build_always_stale': true,
    'build_by_default': true,
    'install': true,
    'install_dir': install_prefix / ext_install_path,
}



# Installing

sdk_can_simply_install = false
ext_install_path = 'Data' / 'Runtime' / 'Html5'