add_library(server SHARED
            ${CMAKE_CURRENT_LIST_DIR}/session.cpp
            ${CMAKE_CURRENT_LIST_DIR}/server.cpp 
            ${CMAKE_CURRENT_LIST_DIR}/handle_method.cpp
            )
target_include_directories(server
            PUBLIC
            ${FACTORY_INCLUDE_DIR}
            ${ASIO_INCLUDE_DIR}
            ${CMAKE_DIR}/include
            )

find_package(yaml-cpp REQUIRED)

add_subdirectory(factory)

target_link_libraries(server
            plugins
            yaml-cpp
            pthread
        )