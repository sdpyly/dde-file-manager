cmake_minimum_required(VERSION 3.10)

set(DESKTOP_PLUGIN_DIR "${PROJECT_SOURCE_PATH}/plugins/common")

# add sub dir for business plugins
add_subdirectory(dfmplugin-burn)
add_subdirectory(dfmplugin-preview)
add_subdirectory(dfmplugin-bookmark)
add_subdirectory(dfmplugin-tag)

add_subdirectory(core/dfmplugin-propertydialog)
