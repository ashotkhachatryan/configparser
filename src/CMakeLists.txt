set(SRC_FILES
    config_parser.cpp
)

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_library(config_parser ${SRC_FILES})
