add_library(plugins SHARED
            plugin_factory.cpp
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
message(STATUS ${FACTORY_INCLUDE_DIR})

install(TARGETS plugins
        EXPORT ${PROJECT_NAME}Targets
        LIBRARY DESTINATION ${INSTALL_LIBDIR} COMPONENT lib
        ARCHIVE DESTINATION ${INSTALL_LIBDIR} COMPONENT lib
        RUNTIME DESTINATION ${INSTALL_BINDIR} COMPONENT bin
        )