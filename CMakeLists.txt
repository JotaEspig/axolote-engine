cmake_minimum_required(VERSION 2.8.5...3.27.5)
project(axolote-engine)

# Debug mode
set(FLAGS "-Wall -Wextra")
if (DEBUG)
    set(FLAGS "${FLAGS} -g3 -fsanitize=address,undefined")
endif ()

message("using flags: ${FLAGS}")

# CMake settings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS}") 

# Find packages
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(Doxygen OPTIONAL_COMPONENTS dot)


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
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# Source files
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(
    SOURCE_FILES
    ${SOURCE_DIR}/camera.cpp
    ${SOURCE_DIR}/gl/ebo.cpp
    ${SOURCE_DIR}/entity.cpp
    ${SOURCE_DIR}/gmesh.cpp
    ${SOURCE_DIR}/mesh.cpp
    ${SOURCE_DIR}/model.cpp
    ${SOURCE_DIR}/object3d.cpp
    ${SOURCE_DIR}/scene.cpp
    ${SOURCE_DIR}/gl/shader.cpp
    ${SOURCE_DIR}/gl/texture.cpp
    ${SOURCE_DIR}/utils.cpp
    ${SOURCE_DIR}/gl/vao.cpp
    ${SOURCE_DIR}/gl/vbo.cpp
    ${SOURCE_DIR}/window.cpp
    ${SOURCE_DIR}/utils/line.cpp

    ${CMAKE_SOURCE_DIR}/external/glad/src/glad.c
    ${CMAKE_SOURCE_DIR}/external/stb/stb.cpp
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
