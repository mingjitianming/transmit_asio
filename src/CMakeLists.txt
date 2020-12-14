add_library(server SHARED "")
add_library(client SHARED "")

find_package(yaml-cpp REQUIRED)
find_package(Protobuf 3 REQUIRED)

# SET(PROTO_META_BASE_DIR ${CMAKE_CURRENT_BINARY_DIR})
# LIST(APPEND PROTO_FLAGS -I${CMAKE_CURRENT_SOURCE_DIR})
# EXECUTE_PROCESS(
#             COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} ${PROTO_FLAGS} --cpp_out=${PROTO_META_BASE_DIR} ${FIL}
#     )

set(PROTO_MESSAGE_DIR "")
# file(GLOB_RECURSE MSG_PROTOS ${CMAKE_SOURCE_DIR}/include/proto/*.proto)
file(GLOB_RECURSE MSG_PROTOS ${CMAKE_SOURCE_DIR}/msg/message/*.proto)
foreach(file ${MSG_PROTOS})
        protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS DESCRIPTORS PROTO_DESCS ${file})
        get_filename_component(dir ${PROTO_HDRS} DIRECTORY)
        set(PROTO_MESSAGE_DIR ${dir})

endforeach()

add_subdirectory(${CMAKE_SOURCE_DIR}/plugins ${CMAKE_BINARY_DIR}/plugins)

target_sources(server
            PRIVATE
            ${CMAKE_CURRENT_LIST_DIR}/session.cpp
            ${CMAKE_CURRENT_LIST_DIR}/server.cpp 
            ${CMAKE_CURRENT_LIST_DIR}/handle_method.cpp
            ${PROTO_SRCS}
            )

target_include_directories(server
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

install(FILES ${PROTO_HDRS}
        DESTINATION include/message
        )
install(TARGETS client server
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION ${INSTALL_LIBDIR} COMPONENT lib
        ARCHIVE DESTINATION ${INSTALL_LIBDIR} COMPONENT lib
        RUNTIME DESTINATION ${INSTALL_BINDIR} COMPONENT bin
        )