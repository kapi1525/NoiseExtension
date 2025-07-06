# JSON
# Include version and commit info
darkext_json = configure_file(
    input: 'DarkExt.json',
    output: 'DarkExt.json.in',
    configuration: {
        'version': 'v' + meson.project_version(),
        'build': ext_build,
        'VCS_TAG': '@VCS_TAG@'
    }
)

darkext_json = vcs_tag(
    input: darkext_json,
    output: 'DarkExt.json',
    fallback: 'v' + meson.project_version(),
)


if runtime_build
    # runtime builds use minified json
    darkext_json = custom_target('minify_json',
        build_by_default: true,
        input: darkext_json,
        output: 'DarkExt.PostMinify.json',
        command: [jsonminify, '@INPUT@', '@OUTPUT@'],
    )
endif

source += custom_target('embed_json',
    input: darkext_json,
    output: 'DarkExt.json.h',
    command: [bin2hpp, '@INPUT@', '@OUTPUT@', 'DarkExtJSON', 'DarkExtJSON_len'],
)

include += include_directories('.')



# Windows resources
if host_machine.system() == 'windows'
    source += import('windows').compile_resources(
        'Ext.rc',
        args: sdk_rc_args,
        depend_files: [
            'Resource.h',
            'Icon.png',
        ],
        include_directories: sdk_include,
    )
endif