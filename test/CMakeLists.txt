cmake_minimum_required(VERSION 3.15)
project(test)
set(transmit_DIR "/home/zmy/project_ws/hk_transport/install/share/cmake/transmit")
find_package(transmit)
find_package(OpenCV REQUIRED)
add_executable(test_server
        ${CMAKE_CURRENT_LIST_DIR}/test_server.cpp
        )

target_link_libraries(test_server
                    transmit::server
                    ${OpenCV_LIBRARIES})


add_executable(test_client
        ${CMAKE_CURRENT_LIST_DIR}/test_client.cpp
        )

target_link_libraries(test_client
                    transmit::client)