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

sdk_js_files = files('package.json', 'tsconfig.json', 'js/Noise.ts')

# Install javascript dependencies
npm = find_program('npm')
npm_package_root = meson.current_source_dir()

run_command(npm, '--prefix', npm_package_root, 'i', '--save-dev',
    check: true,
)



# Installing

sdk_can_simply_install = false
ext_install_path = 'Data' / 'Runtime' / 'Html5'