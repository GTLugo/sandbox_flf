# ===================================================
# SETUP
# ===================================================
cmake_minimum_required(VERSION 3.16)
project(sandbox VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 23)
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
    src/test_world.cpp
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

# Copy resources folder into output dir
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

#target_compile_options(${TARGET_NAME} PRIVATE
#    $<$<CXX_COMPILER_ID:MSVC>:/W3 /WX>
#    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
#    )

# ===================================================
# INCLUDING & LINKING
# ===================================================
# Define the include DIRs
target_include_directories(${TARGET_NAME} PUBLIC "src" "include")

# Precompiled Headers
target_precompile_headers(${TARGET_NAME} PUBLIC "src/sandbox_pch.hpp")

# ===================================================
# SUBMODULES
# ===================================================

# ---- FLUGEL FRAMEWORK ----
# RENDERING API - MULTIPLE CAN BE SELECTED
# > OpenGL, (Planned: Vulkan, D3D11)
if(WIN32)
  set(FLUGEL_RENDERING_API OPENGL #[[VULKAN]])
else()
  set(FLUGEL_RENDERING_API OPENGL #[[VULKAN]])
endif()
add_subdirectory(vendor/flugel)
target_link_libraries(${TARGET_NAME} PUBLIC flugel)
# --------------------------