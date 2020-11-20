
add_executable(test_server
        ${CMAKE_CURRENT_LIST_DIR}/test_server.cpp
        )

target_include_directories(test_server
        PUBLIC
        ${FACTORY_INCLUDE_DIR}
        )

target_link_libraries(test_server
                    server)