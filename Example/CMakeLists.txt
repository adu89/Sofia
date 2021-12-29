cmake_minimum_required(VERSION 3.21.0)
project(Example)

file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
)

add_executable(${PROJECT_NAME})

target_sources(
    ${PROJECT_NAME} PRIVATE ${SOURCES}
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        ${CMAKE_SOURCE_DIR}/Sofia/src
        ${PROJECT_SOURCE_DIR}/Sofia/3rd/spdlog/include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Sofia
)

target_compile_definitions(${PROJECT_NAME} 
    PRIVATE 
        SF_ENABLE_ASSERTS=1
)