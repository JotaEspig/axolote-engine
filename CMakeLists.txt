cmake_minimum_required(VERSION 3.15)
project(axolote-engine)

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
option(
    USE_LOCAL_ASSIMP
    "Should use local assimp library (located in external folder). Does not work on Windows"
    OFF
)
option(DEBUG "Enable debug mode" ON)
option(BUILD_TESTS "Build tests" ON)
if (USE_LOCAL_ASSIMP AND (WIN32 OR MSVC))
    message(FATAL_ERROR "Cannot use local assimp library on Windows")
endif ()
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

set(ASSIMP_LIB assimp)
set(ASSIMP_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/external/include_assimp)
if (NOT USE_LOCAL_ASSIMP)
    find_package(assimp CONFIG REQUIRED)
    set(ASSIMP_LIB assimp::assimp)
endif ()


# =-=-=-=-=-=-= DOCS =-=-=-=-=-=-=
if (DOXYGEN_FOUND)
    message("Doxygen found. You can use `make docs`")

    add_custom_target(
        docs
        COMMAND ${DOXYGEN_EXECUTABLE}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        VERBATIM
    )
else (DOXYGEN_FOUND)
    message("Doxygen not found. You won't be able to use `make docs`")
endif (DOXYGEN_FOUND)


# =-=-=-=-=-=-= LIBRARY =-=-=-=-=-=-=
if (UNIX)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif (UNIX)

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
target_compile_definitions(axolote PUBLIC GLAD_GLAPI_EXPORT PRIVATE GLAD_GLAPI_EXPORT_BUILD)

# Libraries
if (USE_LOCAL_ASSIMP)
    target_link_directories(
        axolote
        PUBLIC
        ${CMAKE_SOURCE_DIR}/external/lib/assimp
    )
endif (USE_LOCAL_ASSIMP)
target_link_libraries(
    axolote
    PUBLIC
    ${OPENGL_LIBRARIES} glfw ${ASSIMP_LIB}
)
if (UNIX)
    target_link_libraries(
        axolote
        PUBLIC
        stdc++
    )
endif (UNIX)

# Header files
target_include_directories(
    axolote
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/include
    ${CMAKE_SOURCE_DIR}/external/imgui/include
    ${ASSIMP_INCLUDE_DIRS}
)


# =-=-=-=-=-=-= TESTS =-=-=-=-=-=-=
if (NOT BUILD_TESTS)
    return()
endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ------ MAIN ------

# Source files
set(
    MAIN_TEST_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/tests/main.cpp
)

# Adding executables for testing
add_executable(main-test ${MAIN_TEST_SOURCE_FILES})
add_dependencies(main-test axolote)
target_compile_definitions(main-test PUBLIC GLAD_GLAPI_EXPORT)
target_compile_definitions(main-test PUBLIC PROJECT_ROOT_FOLDER="${CMAKE_SOURCE_DIR}")

# Libraries
if (UNIX)
    target_link_directories(
        main-test
        PUBLIC
        ./lib
    )
endif (UNIX)
if (USE_LOCAL_ASSIMP)
    target_link_directories(
        axolote
        PUBLIC
        ${CMAKE_SOURCE_DIR}/external/lib/assimp
    )
endif (USE_LOCAL_ASSIMP)
target_link_libraries(
    main-test
    PUBLIC
    axolote
    ${OPENGL_LIBRARIES} glfw ${ASSIMP_LIB}
)
if (UNIX)
    target_link_libraries(
        main-test
        PUBLIC
        stdc++
    )
endif (UNIX)

# Header files
target_include_directories(
    main-test
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/include
    ${CMAKE_SOURCE_DIR}/external/imgui/include
    ${ASSIMP_INCLUDE_DIRS}
)

if (WIN32 OR MSVC)
    add_custom_command(TARGET main-test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_RUNTIME_DLLS:main-test>
        $<TARGET_FILE_DIR:main-test>
        COMMAND_EXPAND_LISTS
    )
endif ()

# ------ WINDOW ------

# Source files
set(
    WINDOW_TEST_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/tests/window.cpp
)

# Adding executables for testing
add_executable(window-test ${WINDOW_TEST_SOURCE_FILES})
add_dependencies(window-test axolote)
target_compile_definitions(window-test PUBLIC GLAD_GLAPI_EXPORT)
target_compile_definitions(window-test PUBLIC PROJECT_ROOT_FOLDER="${CMAKE_SOURCE_DIR}")

# Libraries
if (UNIX)
    target_link_directories(
        window-test
        PUBLIC
        ./lib
    )
endif (UNIX)
if (USE_LOCAL_ASSIMP)
    target_link_directories(
        axolote
        PUBLIC
        ${CMAKE_SOURCE_DIR}/external/lib/assimp
    )
endif (USE_LOCAL_ASSIMP)
target_link_libraries(
    window-test
    PUBLIC
    axolote
    ${OPENGL_LIBRARIES} glfw ${ASSIMP_LIB}
)
if (UNIX)
    target_link_libraries(
        window-test
        PUBLIC
        stdc++
    )
endif (UNIX)

# Header files
target_include_directories(
    window-test
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/include
    ${CMAKE_SOURCE_DIR}/external/imgui/include
    ${ASSIMP_INCLUDE_DIRS}
)

if (WIN32 OR MSVC)
    add_custom_command(TARGET window-test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_RUNTIME_DLLS:window-test>
        $<TARGET_FILE_DIR:window-test>
        COMMAND_EXPAND_LISTS
    )
endif ()

# ------ MODELS_AND_SHADERS ------

# Source files
set(
    MODELS_AND_SHADERS_TEST_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/tests/models_and_shaders.cpp
)

# Adding executables for testing
add_executable(models-and-shaders-test ${MODELS_AND_SHADERS_TEST_SOURCE_FILES})
add_dependencies(models-and-shaders-test axolote)
target_compile_definitions(models-and-shaders-test PUBLIC GLAD_GLAPI_EXPORT)
target_compile_definitions(models-and-shaders-test PUBLIC PROJECT_ROOT_FOLDER="${CMAKE_SOURCE_DIR}")

# Libraries
if (UNIX)
    target_link_directories(
        models-and-shaders-test
        PUBLIC
        ./lib
    )
endif (UNIX)
if (USE_LOCAL_ASSIMP)
    target_link_directories(
        axolote
        PUBLIC
        ${CMAKE_SOURCE_DIR}/external/lib/assimp
    )
endif (USE_LOCAL_ASSIMP)
target_link_libraries(
    models-and-shaders-test
    PUBLIC
    axolote
    ${OPENGL_LIBRARIES} glfw ${ASSIMP_LIB}
)
if (UNIX)
    target_link_libraries(
        models-and-shaders-test
        PUBLIC
        stdc++
    )
endif (UNIX)

# Header files
target_include_directories(
    models-and-shaders-test
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/include
    ${CMAKE_SOURCE_DIR}/external/imgui/include
    ${ASSIMP_INCLUDE_DIRS}
)


if (WIN32 OR MSVC)
    add_custom_command(TARGET models-and-shaders-test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_RUNTIME_DLLS:models-and-shaders-test>
        $<TARGET_FILE_DIR:models-and-shaders-test>
        COMMAND_EXPAND_LISTS
    )
endif ()
