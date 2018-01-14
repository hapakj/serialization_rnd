cmake_minimum_required (VERSION 3.3)

set(PROJECT_NAME "Serialization_Test")
project(${PROJECT_NAME})

include(compiler_flags.cmake)

set(SOURCE_FILES
    main.cpp
    scene_graph.h
)
  
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/glm)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../3rdparty/cereal/include)

set_target_properties(${PROJECT_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../out")


