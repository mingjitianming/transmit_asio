find_package(OpenCV REQUIRED)

set(PLUGIN_MESSAGE_DIR "")
file(GLOB_RECURSE MSG_PROTOS ${FACTORY_INCLUDE_DIR}/plugins/plugin_proto/*.proto)
foreach(file ${MSG_PROTOS})
        protobuf_generate_cpp(PROTO_PLUGIN_SRCS PROTO_PLUGIN_HDRS DESCRIPTORS PROTO_DESCS ${file})
        get_filename_component(dir ${PROTO_PLUGIN_HDRS} DIRECTORY)
        set(PLUGIN_MESSAGE_DIR ${dir})
endforeach()

add_library(plugins SHARED ""
            )

target_sources(plugins
            PRIVATE
            plugins/plc_transmist.cpp
            plugins/init_write.cpp
            ${PROTO_PLUGIN_SRCS}
            
            )
target_include_directories(plugins
            PUBLIC
            $<BUILD_INTERFACE:${CMAKE_DIR}/include>
            $<BUILD_INTERFACE:${FACTORY_INCLUDE_DIR}>
            $<BUILD_INTERFACE:${Protobuf_INCLUDE_DIRS}>
            $<BUILD_INTERFACE:${PROTO_MESSAGE_DIR}>
            $<BUILD_INTERFACE:${PLUGIN_MESSAGE_DIR}>
            PRIVATE
            $<BUILD_INTERFACE:${SPDLOG_INCLUDE_DIR}>

            PUBLIC
            $<INSTALL_INTERFACE:include>
            $<INSTALL_INTERFACE:include/factory>
            $<INSTALL_INTERFACE:include/message>
            $<INSTALL_INTERFACE:include/message/plugins>
            PRIVATE
            $<INSTALL_INTERFACE:3rd/spdlog/include>
            )
target_link_libraries(plugins
${OpenCV_LIBRARIES})

# add_library(plugins_module MODULE
#             plugin_factory.cpp
#             plugins/plc_transmist.cpp
#             plugins/init_write.cpp)
# target_include_directories(plugins_module
#             PUBLIC
#             $<BUILD_INTERFACE:${CMAKE_DIR}/include>
#             $<BUILD_INTERFACE:${FACTORY_INCLUDE_DIR}>
#             PRIVATE
#             $<BUILD_INTERFACE:${SPDLOG_INCLUDE_DIR}>

#             PUBLIC
#             $<INSTALL_INTERFACE:include>
#             $<INSTALL_INTERFACE:include/factory>
#             PRIVATE
#             $<INSTALL_INTERFACE:3rd/spdlog/include>
#             )
# target_link_libraries(plugins_module
# ${OpenCV_LIBRARIES})
install(FILES ${PROTO_PLUGIN_HDRS}
        DESTINATION include/message/plugins)
install(TARGETS plugins
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION ${INSTALL_LIBDIR} COMPONENT lib
        ARCHIVE DESTINATION ${INSTALL_LIBDIR} COMPONENT lib
        RUNTIME DESTINATION ${INSTALL_BINDIR} COMPONENT bin
        )

