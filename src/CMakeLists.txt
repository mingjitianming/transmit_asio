add_library(server SHARED
            ${CMAKE_CURRENT_LIST_DIR}/session.cpp
            ${CMAKE_CURRENT_LIST_DIR}/server.cpp 
            )
target_include_directories(server
            PUBLIC
            ${ASIO_DIR}
            ${CMAKE_DIR}/include
            )

add_subdirectory(factory)