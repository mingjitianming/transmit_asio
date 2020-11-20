cmake_minimum_required(VERSION 3.15)
project(transport_asio
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




set(FACTORY_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include/factory)
set(CMAKE_DIR ${CMAKE_CURRENT_LIST_DIR})
set(ASIO_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/3rd/asio/include)
set(SPDLOG_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/3rd/spdlog/include)


# add_library(service
#             src/service.cpp)
# add_executable(test
#                 src/main.cpp
#                 )
# target_link_libraries(test
#                 pthread)

add_subdirectory(src)
add_subdirectory(examples)


