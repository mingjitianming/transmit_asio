add_library(server SHARED "")
add_library(client SHARED "")

find_package(yaml-cpp REQUIRED)
find_package(Protobuf 3 REQUIRED)

SET(MESSAGE_DIR ${CMAKE_BINARY_DIR}/message)
if(EXISTS "${CMAKE_BINARY_DIR}/message" AND IS_DIRECTORY "${CMAKE_BINARY_DIR}/message")
        SET(PROTO_META_BASE_DIR ${MESSAGE_DIR})
else()
        file(MAKE_DIRECTORY ${MESSAGE_DIR})
        SET(PROTO_META_BASE_DIR ${MESSAGE_DIR})
endif()

LIST(APPEND PROTO_FLAGS -I${CMAKE_SOURCE_DIR}/msg/message)
file(GLOB_RECURSE MSG_PROTOS ${CMAKE_SOURCE_DIR}/msg/message/*.proto)
set(MESSAGE_SRC "")
set(MESSAGE_HDRS "")

foreach(msg ${MSG_PROTOS})
        get_filename_component(FIL_WE ${msg} NAME_WE)

        list(APPEND MESSAGE_SRC "${PROJECT_BINARY_DIR}/message/${FIL_WE}.pb.cc")
        list(APPEND MESSAGE_HDRS "${PROJECT_BINARY_DIR}/message/${FIL_WE}.pb.h")

        add_custom_command(
          OUTPUT "${PROJECT_BINARY_DIR}/message/${FIL_WE}.pb.cc"
                 "${PROJECT_BINARY_DIR}/message/${FIL_WE}.pb.h"
          COMMAND  ${PROTOBUF_PROTOC_EXECUTABLE}
          ARGS --cpp_out  ${PROTO_META_BASE_DIR}
            -I ${CMAKE_SOURCE_DIR}/msg/message
            ${msg}
          DEPENDS ${msg}
          COMMENT "Running C++ protocol buffer compiler on ${msg}"
          VERBATIM
        )
endforeach()
set_source_files_properties(${MESSAGE_SRC} ${MESSAGE_HDRS} PROPERTIES GENERATED TRUE)

add_custom_target(generate_message ALL
                DEPENDS ${MESSAGE_SRC} ${MESSAGE_HDRS}
                COMMENT "generate message target"
                VERBATIM
                )

add_subdirectory(${CMAKE_SOURCE_DIR}/plugins ${CMAKE_BINARY_DIR}/plugins)

target_sources(server
            PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/session.cpp
            ${CMAKE_CURRENT_LIST_DIR}/server.cpp 
            ${CMAKE_CURRENT_LIST_DIR}/handle_method.cpp
            ${MESSAGE_SRC}
            )

target_include_directories(server
            PUBLIC
            $<BUILD_INTERFACE:${FACTORY_INCLUDE_DIR}>
            $<BUILD_INTERFACE:${ASIO_INCLUDE_DIR}>
            $<BUILD_INTERFACE:${CMAKE_DIR}/include>
            $<BUILD_INTERFACE:${Protobuf_INCLUDE_DIRS}>
            $<BUILD_INTERFACE:${MESSAGE_DIR}>
            PRIVATE
            $<BUILD_INTERFACE:${SPDLOG_INCLUDE_DIR}>
            

            PUBLIC
            $<INSTALL_INTERFACE:include/factory>
            $<INSTALL_INTERFACE:3rd/asio/include>
            $<INSTALL_INTERFACE:include>
            $<INSTALL_INTERFACE:include/message>
            $<INSTALL_INTERFACE:include/message/plugins>
            PRIVATE
            $<INSTALL_INTERFACE:3rd/spdlog/include>
            
            )
target_link_libraries(server
            plugins
            yaml-cpp
            pthread
            ${Protobuf_LIBRARIES}
            
        )

target_sources(client 
            PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/client.cpp 
            ${CMAKE_CURRENT_LIST_DIR}/handle_method.cpp
            ${PROTO_SRCS}
            )
target_include_directories(client
            PUBLIC
            $<BUILD_INTERFACE:${FACTORY_INCLUDE_DIR}>
            $<BUILD_INTERFACE:${ASIO_INCLUDE_DIR}>
            $<BUILD_INTERFACE:${CMAKE_DIR}/include>
            $<BUILD_INTERFACE:${Protobuf_INCLUDE_DIRS}>
            $<BUILD_INTERFACE:${PROTO_MESSAGE_DIR}>
            PRIVATE
            $<BUILD_INTERFACE:${SPDLOG_INCLUDE_DIR}>

            PUBLIC
            $<INSTALL_INTERFACE:include/factory>
            $<INSTALL_INTERFACE:3rd/asio/include>
            $<INSTALL_INTERFACE:include>
            $<INSTALL_INTERFACE:include/message>
            $<INSTALL_INTERFACE:include/message/plugins>
            PRIVATE
            $<INSTALL_INTERFACE:3rd/spdlog/include>
            )

target_link_libraries(client
            plugins
            yaml-cpp
            pthread
            ${Protobuf_LIBRARIES}
        )

install(FILES ${MESSAGE_HDRS}
        DESTINATION include/message
        )
install(TARGETS client server
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION ${INSTALL_LIBDIR} COMPONENT lib
        ARCHIVE DESTINATION ${INSTALL_LIBDIR} COMPONENT lib
        RUNTIME DESTINATION ${INSTALL_BINDIR} COMPONENT bin
        )