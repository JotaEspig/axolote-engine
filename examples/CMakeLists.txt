cmake_minimum_required(VERSION 2.8.5...3.27.5)
project(your-project-name)

# Find packages
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# =-=-=-=-=-=-= EXECUTABLE =-=-=-=-=-=-=
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Source files
set(
    SOURCE_FILES
    # Your source files here
)

# Adding executables
add_executable(your-project-name ${SOURCE_FILES})

# Libraries
target_link_directories(
    your-project-name
    PRIVATE
    ${CMAKE_SOURCE_DIR}/external/lib/axolote
)
target_link_libraries(
    your-project-name
    PRIVATE
    axolote
    ${OPENGL_LIBRARIES} glfw stdc++ assimp
    # assimp is the 3D Model Loader lib (it's inside the folder external/lib/axolote)
)

# Header files
target_include_directories(
    your-project-name
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/include
)
