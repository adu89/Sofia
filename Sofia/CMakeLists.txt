cmake_minimum_required(VERSION 3.21.0)
project(Sofia)

file(GLOB_RECURSE SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_library(${PROJECT_NAME})

target_sources(
    ${PROJECT_NAME} PUBLIC ${SOURCES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/3rd/spdlog/include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        D2D1
        Dwrite
)