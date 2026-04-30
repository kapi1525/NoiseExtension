# Only html/wasm/wasi

sdk_ext_name_suffix = 'a'
sdk_ext_target_type = 'static_library'


# Additional linker arguments

sdk_link_args += [
    '-mexec-model=reactor',
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

npm_prefix = meson.current_source_dir()


# default wasm extension wrapper
sdk_base_wasm_ext_wrapper = meson.current_source_dir() / 'CRunWasmExtWrapper.ts'


# Installing
sdk_can_simply_install = false
ext_install_path = 'Data' / 'Runtime' / 'Html5'