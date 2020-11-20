add_library(plugins SHARED
            plugin_factory.cpp
            plugins/plc_transmist.cpp
            plugins/init_write.cpp)
target_include_directories(plugins
            PUBLIC
            ${CMAKE_DIR}/include
            ${FACTORY_INCLUDE_DIR}
            PRIVATE
            ${SPDLOG_INCLUDE_DIR}
            )
message(STATUS ${FACTORY_INCLUDE_DIR})