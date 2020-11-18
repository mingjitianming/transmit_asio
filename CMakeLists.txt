cmake_minimum_required(VERSION 3.15)
project(transport_asio
        LANGUAGES CXX
        VERSION 1.0.0)

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++17" COMPILER_SUPPORTS_CXX17)
if(COMPILER_SUPPORTS_CXX17)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++17 support. Please use a different C++ compiler.")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
    include
    ${PROJECT_SOURCE_DIR}/3rd/include
)

set(FACTORY_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include/factory)
set(CMAKE_DIR ${CMAKE_CURRENT_LIST_DIR})
set(ASIO_DIR ${CMAKE_CURRENT_LIST_DIR}/3rd/asio/include)
message(STATUS ${FACTORY_INCLUDE_DIR})

# add_library(service
#             src/service.cpp)
# add_executable(test
#                 src/main.cpp
#                 )
# target_link_libraries(test
#                 pthread)

add_subdirectory(src)

