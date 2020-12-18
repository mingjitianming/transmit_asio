cmake_minimum_required(VERSION 3.15)
project(transmit
        LANGUAGES CXX
        VERSION 1.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE "Debug")

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++17" COMPILER_SUPPORTS_CXX17)
if(COMPILER_SUPPORTS_CXX17)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++17 support. Please use a different C++ compiler.")
endif()


# set output dir 
include(GNUInstallDirs)
# set build output dir
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
#set install output dir
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install)
set(INSTALL_LIBDIR ${CMAKE_INSTALL_LIBDIR} CACHE PATH "Installation directory for libraries")
set(INSTALL_BINDIR ${CMAKE_INSTALL_BINDIR} CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR} CACHE PATH "Installation directory for header files")
set(INSTALL_CMAKEDIR share/cmake/${PROJECT_NAME} CACHE PATH "Installation directory for CMake files")

set(FACTORY_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include/factory)
set(CMAKE_DIR ${CMAKE_CURRENT_LIST_DIR})
set(ASIO_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/3rd/asio/include)
set(SPDLOG_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/3rd/spdlog/include)

add_subdirectory(src)
add_subdirectory(examples)

# create build tree cmake
export(TARGETS client server plugins
       NAMESPACE "${PROJECT_NAME}::"
       FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigBuild.cmake
       )

# create install tree cmake
install(EXPORT ${PROJECT_NAME}Targets
        NAMESPACE "${PROJECT_NAME}::"
        DESTINATION ${INSTALL_CMAKEDIR}
        COMPONENT dev)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION ${INSTALL_CMAKEDIR}
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION ${INSTALL_CMAKEDIR}
)

install(DIRECTORY 
            include 3rd
        DESTINATION .
)
