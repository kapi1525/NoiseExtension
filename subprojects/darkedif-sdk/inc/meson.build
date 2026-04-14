# Includes

sdk_include = [include_directories(
    '.',
    'Shared',
)]

if windows_build
    sdk_include += include_directories('Windows')
elif android_build
    # sdk_include += include_directories('Android')
elif wasm_build
    # sdk_include += include_directories('Html')
else
    error('Unsupported platform')
endif