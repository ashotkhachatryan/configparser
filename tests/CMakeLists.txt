set(SRC_FILES
    test.cpp
)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src)
link_directories(${PROJECT_BINARY_DIR}/lib)

add_executable(test ${SRC_FILES})
target_link_libraries(test -lconfig_parser)
