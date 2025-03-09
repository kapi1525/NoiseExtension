# common
subdir('Shared')

# platform specific
if host_machine.system() == 'windows'
    subdir('Windows')
elif host_machine.system() == 'android'
    subdir('Android')
elif host_machine.system() == 'wasi'
    subdir('Html')
else
    error('Unsuported system!')
endif