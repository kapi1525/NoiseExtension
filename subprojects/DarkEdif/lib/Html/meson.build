# Only html/wasm/wasi

ext_file_suffix = 'wasm'
ext_build_type = 'executable'


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

npm_build_command = [npm, '--prefix', npm_package_root, 'run', 'build']



# Installing

ext_simple_install = false
ext_simple_install_js = true
ext_install_path = 'Data' / 'Runtime' / 'Html5'