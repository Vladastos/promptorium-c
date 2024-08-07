project('Documents', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

cjson = dependency('libcjson')

source_file = files('src/main.c', 'src/modules/module.c')

include_dirs = include_directories('src/modules')

executable('promptorium',
            sources : source_file,
            install : true,
            dependencies : [cjson],)
