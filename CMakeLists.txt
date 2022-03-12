# ===================================================
# SETUP
# ===================================================
cmake_minimum_required(VERSION 3.16)
project(sandbox VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)
set(TARGET_NAME "SANDBOX")
message(STATUS "Configuring: ${PROJECT_NAME}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/$<CONFIG>/${CMAKE_SYSTEM_NAME}")
if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE $<$<OR:$<CONFIG:release>,$<CONFIG:minsizerel>>:TRUE>)
endif()

# ===================================================
# COLLECT FILES
# ===================================================

set(SOURCE_FILES
    src/sandbox.cpp
    src/test_layer.cpp
    )

# ===================================================
# ADD EXECUTABLE TARGET
# ===================================================
add_executable(${TARGET_NAME}
    ${SOURCE_FILES}
    )

set_target_properties(${TARGET_NAME}
    PROPERTIES
    OUTPUT_NAME "${TARGET_NAME}"
    )

add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E remove_directory
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res/${PROJECT_NAME}")
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/res/${PROJECT_NAME}
    "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res/${PROJECT_NAME}")

# Preprocessor Defines
target_compile_definitions(${TARGET_NAME}
    PRIVATE
    $<$<CONFIG:debug>:DEBUG=1>
    $<$<CONFIG:release>:RELEASE=1>
    $<$<CONFIG:relwithdebinfo>:RELDEB=1>
    $<$<CONFIG:minsizerel>:MINREL=1>
    )

# ===================================================
# INCLUDING & LINKING
# ===================================================
# Define the include DIRs
target_include_directories(${TARGET_NAME} PUBLIC "src" "include")

# Precompiled Headers
target_precompile_headers(${TARGET_NAME} PUBLIC "src/sandbox_pch.hpp")

# RENDERING API - MULTIPLE CAN BE ON AT A TIME
# > OpenGL, (Planned: Vulkan, D3D11)
# WINDOWING API - ONLY ONE SHOULD BE ON AT A TIME
# > GLFW, (Planned: SDL2, Win32)
if(WIN32)
  set(FLUGEL_OPENGL ON)
  set(FLUGEL_VULKAN OFF)
  #set(FLUGEL_D3D11  OFF)

  set(FLUGEL_GLFW  ON)
  #set(FLUGEL_SDL   OFF)
  #set(FLUGEL_WIN32 OFF)
else()
  set(FLUGEL_OPENGL ON)
  set(FLUGEL_VULKAN OFF)
  #set(FLUGEL_D3D11  OFF)

  set(FLUGEL_GLFW  ON)
  #set(FLUGEL_SDL   OFF)
  #set(FLUGEL_WIN32 OFF)
endif()
add_subdirectory(vendor/flugel)
target_link_libraries(${TARGET_NAME} PUBLIC flugel)

# ===================================================
# DEPENDENCIES - VCPKG SUGGESTED
# ===================================================
# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
