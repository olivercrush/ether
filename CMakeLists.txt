cmake_minimum_required(VERSION 3.20)
project(game-engine C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW3 REQUIRED glfw3)
pkg_check_modules(GLEW REQUIRED glew)
pkg_check_modules(CGLM REQUIRED cglm)

add_executable(game-engine
    src/main.c
    src/shader.c
    src/dds.c
)

target_include_directories(game-engine PRIVATE
    include
    ${GLFW3_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${CGLM_INCLUDE_DIRS}
)

target_compile_options(game-engine PRIVATE
    -g -O0
)

target_link_libraries(game-engine PRIVATE
    ${GLFW3_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${CGLM_LIBRARIES}
    m
)

set_target_properties(game-engine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
