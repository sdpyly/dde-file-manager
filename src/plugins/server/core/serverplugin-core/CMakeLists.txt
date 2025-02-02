cmake_minimum_required(VERSION 3.10)

project(serverplugin-core)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

FILE(GLOB_RECURSE SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.json"
    "${DFM_DBUS_XML_DIR}/org.deepin.filemanager.server.DeviceManager.xml"
    "${DFM_DBUS_XML_DIR}/org.deepin.filemanager.server.OperationsStackManager.xml"
    )
# TODO: tag manager
find_package(Qt5 COMPONENTS
    Core
    DBus
    REQUIRED)

# DBus: DeviceManager
qt5_generate_dbus_interface(
    devicemanagerdbus.h
    ${DFM_DBUS_XML_DIR}/org.deepin.filemanager.server.DeviceManager.xml
    OPTIONS -M -S
)

qt5_add_dbus_adaptor(SRC_FILES ${DFM_DBUS_XML_DIR}/org.deepin.filemanager.server.DeviceManager.xml
    devicemanagerdbus.h DeviceManagerDBus)

# DBus: OperationsStackManager
qt5_generate_dbus_interface(
    operationsstackmanagerdbus.h
    ${DFM_DBUS_XML_DIR}/org.deepin.filemanager.server.OperationsStackManager.xml
    OPTIONS -M -S
)

qt5_add_dbus_adaptor(SRC_FILES ${DFM_DBUS_XML_DIR}/org.deepin.filemanager.server.OperationsStackManager.xml
    operationsstackmanagerdbus.h OperationsStackManagerDbus)

add_library(${PROJECT_NAME}
    SHARED
    ${SRC_FILES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ../../)

target_link_libraries(${PROJECT_NAME}
    DFM::base
    DFM::framework
    Qt5::Core
    Qt5::DBus
)

#install library file
install(TARGETS
    ${PROJECT_NAME}
    LIBRARY
    DESTINATION
    ${DFM_PLUGIN_FILEMANAGER_CORE_DIR}
)
