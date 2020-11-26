find_package(OpenCV REQUIRED)
add_library(plugins SHARED
            plugins/plc_transmist.cpp
            plugins/init_write.cpp)
target_include_directories(plugins
            PUBLIC
            $<BUILD_INTERFACE:${CMAKE_DIR}/include>
            $<BUILD_INTERFACE:${FACTORY_INCLUDE_DIR}>
            PRIVATE
            $<BUILD_INTERFACE:${SPDLOG_INCLUDE_DIR}>

            PUBLIC
            $<INSTALL_INTERFACE:include>
            $<INSTALL_INTERFACE:include/factory>
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

install(TARGETS plugins
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION ${INSTALL_LIBDIR} COMPONENT lib
        ARCHIVE DESTINATION ${INSTALL_LIBDIR} COMPONENT lib
        RUNTIME DESTINATION ${INSTALL_BINDIR} COMPONENT bin
        )

