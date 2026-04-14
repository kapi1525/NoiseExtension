# Only android

sdk_ext_name_suffix = 'so'

sdk_android_ndk = meson.get_compiler('cpp').get_define('__NDK_MAJOR__', prefix: '#include <android/ndk-version.h>').to_int()


# TODO: Port over ndk api check


# Additional build arguments
sdk_cpp_args += [
    '-fvisibility=hidden',
    '-fsigned-char',
    '-fPIC',
    '-fasm-blocks',
    '-Wno-unknown-pragmas',
    '-Wno-unused-const-variable',
    '-Wno-missing-braces',
]

# https://github.com/SortaCore/MMF2Exts/commit/230872148bb7520075548b74951fab5710d21a47
# https://developer.android.com/guide/practices/page-sizes#compile-16-kb-alignment
if sdk_android_ndk > 22 and sdk_android_ndk < 28 and (host_machine.cpu_family() == 'x86_64' or host_machine.cpu_family() == 'aarch64')
    sdk_link_args += [
        '-Wl,-z,common-page-size=16384',
    ]
elif sdk_android_ndk <= 22
    error('Android NDK 22 and lower is not supported!')
endif

sdk_link_args += [
    '-static-libstdc++',
]

# TODO: Link with correct renderer .so

sdk_deps += meson.get_compiler('cpp').find_library('log')


# Installing

# Android zip file contents:
# Extname/app/src/main
# |- java/Extensions/CRunExtname.java
# |- jniLibs/arch/libExtname.so

sdk_can_simply_install = false
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


ext_android_java_wrapper = configure_file(
    input: 'CRunExt.java',
    output: 'CRun' + ext_target_name + '.java',
    configuration: {
        'ext_name': ext_name,
        'ext_target_name': ext_target_name,
    }
)