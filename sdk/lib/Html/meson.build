# Only html/wasm/wasi

sdk_ext_name_suffix = 'wasm'
sdk_ext_target_type = 'executable'


# Additional linker arguments

sdk_link_args += [
    '-Wl,--no-entry',
    '-Wl,--stack-first',    # Simplifies finding potential stack overflow errors, https://github.com/WebAssembly/wasi-sdk/issues/551
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


# default wasm extension wrapper
sdk_base_wasm_ext_wrapper = meson.current_source_dir() / 'CRunWasmExtWrapper.ts'


# Installing
sdk_can_simply_install = false
ext_install_path = 'Data' / 'Runtime' / 'Html5'


# default env used to launch npm build script
sdk_js_ext_wrapper_env = {
    'ENTRY': sdk_base_wasm_ext_wrapper,
    'TOTYPECHECK': ' '.join([sdk_base_wasm_ext_wrapper, meson.current_source_dir() / '*.ts']),
    'EXTNAME': meson.project_name(),
    'EXTWASMPATH': 'REPLACE',
    'OUTPUTPATH': 'REPLACE',
}

# kwargs for npm build script custom target
sdk_js_ext_wrapper_kwargs = {
    'command': [npm, 'run', 'build'],
    'build_always_stale': true,
    'build_by_default': true,
    'install': true,
    'install_dir': install_prefix / ext_install_path,
}