cmake_minimum_required(VERSION 2.8.5)
project(axolote-engine)

# CMake settings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

# Find packages
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)


# =-=-=-=-=-=-= LIBRARY =-=-=-=-=-=-=
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# Source files
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(
    SOURCE_FILES
    ${SOURCE_DIR}/camera.cpp
    ${SOURCE_DIR}/mesh.cpp
    ${SOURCE_DIR}/shader.cpp
    ${SOURCE_DIR}/texture.cpp
    ${SOURCE_DIR}/vao.cpp
    ${SOURCE_DIR}/vbo.cpp
    ${SOURCE_DIR}/ebo.cpp
    ${SOURCE_DIR}/window.cpp
    ${SOURCE_DIR}/entity.cpp
    ${SOURCE_DIR}/model.cpp
    ${SOURCE_DIR}/utils.cpp

    ${CMAKE_SOURCE_DIR}/external/stb/stb.cpp
    ${CMAKE_SOURCE_DIR}/external/glad/src/glad.c
)

# Adding axolote shared library
add_library(axolote SHARED ${SOURCE_FILES})

# Libraries
target_link_directories(
    axolote
    PRIVATE
    ${CMAKE_SOURCE_DIR}/external/assimp
    ${OPENGL_INCLUDE_DIRS}
)
target_link_libraries(
    axolote
    PRIVATE
    ${OPENGL_LIBRARIES} glfw assimp stdc++
)

# Header files
target_include_directories(
    axolote
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/include
)


# =-=-=-=-=-=-= TESTS =-=-=-=-=-=-=
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/tests/bin)

# Source files
set(
    TEST_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/tests/main.cpp
)

# Adding executables for testing
add_executable(tests ${TEST_SOURCE_FILES})

# Libraries
target_link_directories(
    tests
    PRIVATE
    ./lib
)
target_link_libraries(
    tests
    PRIVATE
    axolote
    ${OPENGL_LIBRARIES} glfw stdc++
)

# Header files
target_include_directories(
    tests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)