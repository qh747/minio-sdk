cmake_minimum_required(VERSION 3.14)

project(inih LANGUAGES C CXX)
set(target INIReader)

add_library(${target} STATIC
    ini.c
    cpp/INIReader.cpp
)

target_compile_definitions(${target} PRIVATE
    INI_STATIC_LIB
    INI_STATIC_LIB_BUILDING
)

#Library
install(TARGETS ${target}
    EXPORT "${target}-export" COMPONENT dev
    RUNTIME DESTINATION ${INSTALL_BIN} COMPONENT runtime
    LIBRARY DESTINATION ${INSTALL_STATIC} COMPONENT runtime
    ARCHIVE DESTINATION ${INSTALL_LIB} COMPONENT dev
)

# Installiere Header-Dateien
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/cpp/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)
install(
    FILES ${CMAKE_CURRENT_SOURCE_DIR}/ini.h
    DESTINATION include
)
