# Only html/wasm/wasi

sdk_ext_name_suffix = 'wasm'
sdk_ext_target_type = 'executable'


# Additional linker arguments

sdk_link_args += [
    '-Wl,--no-entry',
]

sdk_js_files = files('package.json', 'tsconfig.json', 'js/Noise.ts')

# Install javascript dependencies
npm = find_program('npm')
npm_package_root = meson.current_source_dir()

run_command(npm, '--prefix', npm_package_root, 'i', '--save-dev',
    check: true,
)



# Installing

sdk_can_simply_install = false
sdk_can_simply_install_js = true
ext_install_path = 'Data' / 'Runtime' / 'Html5'