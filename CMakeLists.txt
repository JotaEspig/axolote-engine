cmake_minimum_required(VERSION 3.15)

execute_process(
    COMMAND python3 ${CMAKE_SOURCE_DIR}/scripts/get_version.py ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE PROJECT_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
message("Axolote version: ${PROJECT_VERSION}")
project(axolote-engine VERSION ${PROJECT_VERSION} LANGUAGES C CXX)

# CMake settings
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if (UNIX)
    add_custom_target(
        copy-compile-commands ALL
        ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}
    )
endif (UNIX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${FLAGS} -g3 -fsanitize=address,undefined")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${FLAGS} -O3")

set(FLAGS "-Wall")
if (CMAKE_COMPILER_IS_GNUXX)
    set(FLAGS "${FLAGS} -Wextra")
endif (CMAKE_COMPILER_IS_GNUXX)


# Flags
option(CMAKE_BUILD_TYPE "Build type" Release)
option(DEBUG "Enable debug mode" ON)
option(BUILD_TESTS "Build tests" ON)
if (DEBUG)
    message("DEBUG MODE ON")
    add_definitions(-DDEBUG)
else()
    message("DEBUG MODE OFF")
endif()


# Find packages
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm REQUIRED)
find_package(Doxygen OPTIONAL_COMPONENTS dot)

find_package(assimp CONFIG REQUIRED)


# =-=-=-=-=-=-= DOCS =-=-=-=-=-=-=
if (DOXYGEN_FOUND)
    message("Doxygen found. You can use `make docs`")

    # Configure Doxyfile template
    set(DOXYGEN_PROJECT_NAME ${PROJECT_NAME})
    set(DOXYGEN_PROJECT_NUMBER ${PROJECT_VERSION})
    set(DOXYGEN_INPUT ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)
    set(DOXYGEN_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/docs)
    set(DOXYGEN_RECURSIVE YES)
    # Add other Doxygen variables as needed
    configure_file(${CMAKE_SOURCE_DIR}/Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)

    add_custom_target(
        docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
else (DOXYGEN_FOUND)
    message("Doxygen not found. Documentation target 'docs' will not be available.")
endif (DOXYGEN_FOUND)


# =-=-=-=-=-=-= LIBRARY =-=-=-=-=-=-=
# Use GNUInstallDirs to define standard installation paths
include(GNUInstallDirs)

# Source files
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(
    SOURCE_FILES
    ${SOURCE_DIR}/assimp.cpp
    ${SOURCE_DIR}/camera.cpp
    ${SOURCE_DIR}/camera_renderer.cpp
    ${SOURCE_DIR}/glad/glad.c
    ${SOURCE_DIR}/gl/ebo.cpp
    ${SOURCE_DIR}/gl/framebuffer.cpp
    ${SOURCE_DIR}/gl/shader.cpp
    ${SOURCE_DIR}/gl/texture.cpp
    ${SOURCE_DIR}/gl/vao.cpp
    ${SOURCE_DIR}/gl/vbo.cpp
    ${SOURCE_DIR}/gmesh.cpp
    ${SOURCE_DIR}/gmodel.cpp
    ${SOURCE_DIR}/instancing.cpp
    ${SOURCE_DIR}/light.cpp
    ${SOURCE_DIR}/mesh.cpp
    ${SOURCE_DIR}/model.cpp
    ${SOURCE_DIR}/object3d.cpp
    ${SOURCE_DIR}/scene.cpp
    ${SOURCE_DIR}/scene_context.cpp
    ${SOURCE_DIR}/scene_renderer.cpp
    ${SOURCE_DIR}/utils.cpp
    ${SOURCE_DIR}/utils/grid.cpp
    ${SOURCE_DIR}/utils/line.cpp
    ${SOURCE_DIR}/window.cpp

    ${CMAKE_SOURCE_DIR}/external/stb/stb.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/src/imgui.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/src/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/src/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/src/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/src/imgui_impl_opengl3.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/src/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/src/imgui_widgets.cpp
)

# Adding axolote shared library
add_library(axolote SHARED ${SOURCE_FILES})
add_library(axolote::axolote ALIAS axolote) # Add alias for modern CMake usage

target_compile_definitions(axolote PUBLIC GLAD_GLAPI_EXPORT PRIVATE GLAD_GLAPI_EXPORT_BUILD)

# Public Header files for installation and usage
target_include_directories(
    axolote
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/external/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/external/imgui/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> # Headers will be installed here
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src # Private headers/sources if any
        ${CMAKE_SOURCE_DIR}/external/stb # STB is likely implementation detail
        ${CMAKE_SOURCE_DIR}/external/imgui/src # ImGui sources are implementation detail
)

# Libraries
target_link_libraries(
    axolote
    PUBLIC
        OpenGL::GL
        glfw
        glm::glm
        assimp::assimp
    PRIVATE
        # Link libraries needed only internally by axolote
)

if (UNIX AND NOT APPLE)
    target_link_libraries(axolote PUBLIC stdc++)
endif()

# Set properties for shared library versioning
set_target_properties(axolote PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Define Windows properties for DLL export/import
if(WIN32)
  set_target_properties(axolote PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()


# =-=-=-=-=-=-= INSTALLATION =-=-=-=-=-=-=
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# Install Targets (library)
install(TARGETS axolote
    EXPORT axoloteTargets # Export the target for CMake package config
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT Runtime # DLLs on Windows
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Libraries # .so or .lib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT Development # .lib on Windows, .a
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # For headers associated with target
)

# Install Public Headers
# Install headers from include directory
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/axolote/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/axolote COMPONENT Development)
# Install necessary external headers (adjust paths as needed)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/external/imgui/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/imgui COMPONENT Development)


# --- CMake Package Configuration ---

# Generate the axoloteTargets.cmake file
# This file contains the imported target definition for axolote::axolote
export(EXPORT axoloteTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/axoloteTargets.cmake"
    NAMESPACE axolote:: # Use a namespace for the imported targets
)

# Create the ConfigVersion file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/axoloteConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion # Or SameMajorVersion, ExactVersion etc.
)

# Create the main Config file (axoloteConfig.cmake)
# This file finds dependencies and includes the Targets file
configure_package_config_file(
    "${CMAKE_SOURCE_DIR}/cmake/config.cmake.in" # Input template file (Create this!)
    "${CMAKE_CURRENT_BINARY_DIR}/cmake/axoloteConfig.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/axolote" # Standard location
    PATH_VARS CMAKE_INSTALL_INCLUDEDIR CMAKE_INSTALL_LIBDIR # Variables to make absolute in config file
)

# Install the generated CMake configuration files
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/cmake/axoloteConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake/axoloteConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/axolote"
    COMPONENT Development
)

# Install the exported targets file
install(
    EXPORT axoloteTargets
    NAMESPACE axolote::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/axolote"
    COMPONENT Development
)

# --- End CMake Package Configuration ---


# =-=-=-=-=-=-= TESTS =-=-=-=-=-=-=
if (NOT BUILD_TESTS)
    return()
endif ()

enable_testing() # Enable CTest

# Set output directory for executables consistently
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # For libraries if any tests are libs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib) # For static libs

# Helper function to reduce test target duplication
function(add_axolote_test test_name source_file)
    add_executable(${test_name} ${source_file})
    # Ensure library is built before the test executable
    add_dependencies(${test_name} axolote)

    # Definitions needed by the test executable
    target_compile_definitions(${test_name} PRIVATE GLAD_GLAPI_EXPORT) # If test uses glad directly
    target_compile_definitions(${test_name} PRIVATE PROJECT_ROOT_FOLDER="${CMAKE_SOURCE_DIR}")

    # Link the test against the axolote library and its dependencies
    target_link_libraries(${test_name} PRIVATE axolote::axolote) # Link against the alias

    # Include directories needed by the test source file itself (if any beyond what axolote provides)
    # target_include_directories(${test_name} PRIVATE ...)

    # Add test to CTest
    add_test(NAME ${test_name} COMMAND ${test_name})

    # Copy DLLs on Windows post-build step for the executable
    if (WIN32 OR MSVC)
        add_custom_command(TARGET ${test_name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different # Use copy_if_different
            $<TARGET_RUNTIME_DLLS:${test_name}> # Generator expression for DLLs
            $<TARGET_FILE_DIR:${test_name}>
            COMMAND_EXPAND_LISTS
            COMMENT "Copying runtime dependencies for ${test_name}"
        )
    endif()
endfunction()

# Add tests using the helper function
add_axolote_test(main-test ${CMAKE_SOURCE_DIR}/tests/main.cpp)
add_axolote_test(window-test ${CMAKE_SOURCE_DIR}/tests/window.cpp)
add_axolote_test(models-and-shaders-test ${CMAKE_SOURCE_DIR}/tests/models_and_shaders.cpp)
