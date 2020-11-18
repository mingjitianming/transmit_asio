add_library(plugins
            plugins/plc_transmist.cpp)
target_include_directories(plugins
            PUBLIC
            ${FACTORY_INCLUDE_DIR}
            )
message(STATUS ${FACTORY_INCLUDE_DIR})