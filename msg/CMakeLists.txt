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
