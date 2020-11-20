add_library(server SHARED "")
add_library(client SHARED "")

find_package(yaml-cpp REQUIRED)

add_subdirectory(factory)

target_sources(server
            PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/session.cpp
            ${CMAKE_CURRENT_LIST_DIR}/server.cpp 
            ${CMAKE_CURRENT_LIST_DIR}/handle_method.cpp
            )

target_include_directories(server
            PUBLIC
            ${FACTORY_INCLUDE_DIR}
            ${ASIO_INCLUDE_DIR}
            ${CMAKE_DIR}/include
            PRIVATE
            ${SPDLOG_INCLUDE_DIR}
            )
target_link_libraries(server
            plugins
            yaml-cpp
            pthread
        )

target_sources(client 
            PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/client.cpp 
            ${CMAKE_CURRENT_LIST_DIR}/handle_method.cpp
            )
target_include_directories(client
            PUBLIC
            ${FACTORY_INCLUDE_DIR}
            ${ASIO_INCLUDE_DIR}
            ${CMAKE_DIR}/include
            PRIVATE
            ${SPDLOG_INCLUDE_DIR}
            )

target_link_libraries(client
            plugins
            yaml-cpp
            pthread
        )