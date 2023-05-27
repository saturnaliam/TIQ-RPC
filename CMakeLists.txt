cmake_minimum_required(VERSION 3.26)

project(main)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

file(GLOB SOURCES
${PROJECT_SOURCE_DIR}/src/include/*.h
${PROJECT_SOURCE_DIR}/src/include/*.cpp
${PROJECT_SOURCE_DIR}/src/discord/*.h
${PROJECT_SOURCE_DIR}/src/discord/*.cpp
${PROJECT_SOURCE_DIR}/src/main.cpp)

add_executable(main ${SOURCES})
target_link_directories(main PUBLIC "${PROJECT_SOURCE_DIR}/src/lib/")
target_link_libraries(main discord_game_sdk)
