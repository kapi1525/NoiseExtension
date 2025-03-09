# Only android

ext_file_suffix = 'so'


# Additional build arguments

if meson.get_compiler('cpp').get_id() == 'clang'
    sdk_cpp_args += [
        '-fvisibility=hidden',
        '-fsigned-char',
        '-fPIC',
        '-fasm-blocks',
        '-Wno-unknown-pragmas',
        '-Wno-unused-const-variable',
        '-Wno-missing-braces',
    ]
endif


# Installing

# Android zip file contents:
# Extname/app/src/main
# |- java/Extensions/CRunExtname.java
# |- jniLibs/arch/libExtname.so

ext_simple_install = false
ext_install_path = 'Data' / 'Runtime' / 'Android'

if host_machine.cpu_family() == 'aarch64'
    ext_android_arch = 'arm64-v8a'
elif host_machine.cpu_family() == 'arm'
    ext_android_arch = 'armeabi-v7a'
elif host_machine.cpu_family() == 'x86'
    ext_android_arch = 'x86'
elif host_machine.cpu_family() == 'x86_64'
    ext_android_arch = 'x86_64'
endif

ext_android_java_filename = 'CRun' + meson.project_name() + '.java'
ext_android_java_filepath = meson.current_source_dir() / ext_android_java_filename
