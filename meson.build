project('Documents', 'c', version: '0.1', default_options: ['warning_level=3'])

cjson = dependency('libcjson')

source_files = files(
    'src/main.c',
    'src/modules/application/application.c',
    'src/modules/application/prompt/prompt.c',
    'src/modules/common/colors/colors.c',
    'src/modules/common/common-modules.h',
    'src/modules/common/config-management/config-management.c',
    'src/modules/common/log-management/log-management.c',
    'src/modules/common/utils/definitions.h',
    'src/modules/common/utils/utils.c',
)


executable(
    'promptorium',
    sources: source_files,
    install: true,
    dependencies: [cjson],
)
