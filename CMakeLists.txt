cmake_minimum_required(VERSION 3.26)

project(main)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cpp src/*.hpp src/*.h)

add_executable(main ${sources})
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "TIQ Rich Presence")

set_property(TARGET main PROPERTY CXX_STANDARD 20)

target_link_directories(main PUBLIC "${PROJECT_SOURCE_DIR}/src/lib/")
target_link_libraries(main discord_game_sdk)
