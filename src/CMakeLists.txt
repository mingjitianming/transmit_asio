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
            $<BUILD_INTERFACE:${FACTORY_INCLUDE_DIR}>
            $<BUILD_INTERFACE:${ASIO_INCLUDE_DIR}>
            $<BUILD_INTERFACE:${CMAKE_DIR}/include>
            PRIVATE
            $<BUILD_INTERFACE:${SPDLOG_INCLUDE_DIR}>

            PUBLIC
            $<INSTALL_INTERFACE:include/factory>
            $<INSTALL_INTERFACE:3rd/asio/include>
            $<INSTALL_INTERFACE:include>
            PRIVATE
            $<INSTALL_INTERFACE:3rd/spdlog/include>
            
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
            $<BUILD_INTERFACE:${FACTORY_INCLUDE_DIR}>
            $<BUILD_INTERFACE:${ASIO_INCLUDE_DIR}>
            $<BUILD_INTERFACE:${CMAKE_DIR}/include>
            PRIVATE
            $<BUILD_INTERFACE:${SPDLOG_INCLUDE_DIR}>

            PUBLIC
            $<INSTALL_INTERFACE:include/factory>
            $<INSTALL_INTERFACE:3rd/asio/include>
            $<INSTALL_INTERFACE:include>
            PRIVATE
            $<INSTALL_INTERFACE:3rd/spdlog/include>
            )

target_link_libraries(client
            plugins
            yaml-cpp
            pthread
        )

install(TARGETS client server
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION ${INSTALL_LIBDIR} COMPONENT lib
        ARCHIVE DESTINATION ${INSTALL_LIBDIR} COMPONENT lib
        RUNTIME DESTINATION ${INSTALL_BINDIR} COMPONENT bin
        )