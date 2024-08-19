cmake_minimum_required(VERSION 3.15)
project(axolote-engine)

set(FLAGS "-Wall")
if (CMAKE_COMPILER_IS_GNUXX)
    set(FLAGS "${FLAGS} -Wextra")
endif (CMAKE_COMPILER_IS_GNUXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

# CMake settings
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${FLAGS} -g3 -fsanitize=address,undefined")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${FLAGS} -O3")

option(DEBUG "Enable debug mode" ON)
if (DEBUG)
    message("DEBUG MODE ON")
    add_definitions(-DDEBUG)
else()
    message("DEBUG MODE OFF")
endif()

# Find packages
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
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
if (UNIX)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
endif (UNIX)

# Source files
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(
    SOURCE_FILES
    ${SOURCE_DIR}/assimp.cpp
    ${SOURCE_DIR}/camera.cpp
    ${SOURCE_DIR}/glad/glad.c
    ${SOURCE_DIR}/gl/ebo.cpp
    ${SOURCE_DIR}/gl/shader.cpp
    ${SOURCE_DIR}/gl/texture.cpp
    ${SOURCE_DIR}/gl/vao.cpp
    ${SOURCE_DIR}/gl/vbo.cpp
    ${SOURCE_DIR}/gmesh.cpp
    ${SOURCE_DIR}/gmodel.cpp
    ${SOURCE_DIR}/light.cpp
    ${SOURCE_DIR}/mesh.cpp
    ${SOURCE_DIR}/model.cpp
    ${SOURCE_DIR}/object3d.cpp
    ${SOURCE_DIR}/scene.cpp
    ${SOURCE_DIR}/utils.cpp
    ${SOURCE_DIR}/utils/grid.cpp
    ${SOURCE_DIR}/utils/line.cpp
    ${SOURCE_DIR}/window.cpp

    ${CMAKE_SOURCE_DIR}/external/stb/stb.cpp
)

# Adding axolote shared library
add_library(axolote SHARED ${SOURCE_FILES})
target_compile_definitions(axolote PUBLIC GLAD_GLAPI_EXPORT PRIVATE GLAD_GLAPI_EXPORT_BUILD)

# Libraries
target_link_libraries(
    axolote
    PUBLIC
    ${OPENGL_LIBRARIES} glfw assimp::assimp
)

# Header files
target_include_directories(
    axolote
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/include
    ${ASSIMP_INCLUDE_DIRS}
)


# =-=-=-=-=-=-= TESTS =-=-=-=-=-=-=
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

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

# Libraries
if (UNIX)
    target_link_directories(
        main-test
        PUBLIC
        ./lib
    )
endif (UNIX)

target_link_libraries(
    main-test
    PUBLIC
    axolote
    ${OPENGL_LIBRARIES} glfw assimp::assimp
)

# Header files
target_include_directories(
    main-test
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/include
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

# Libraries
if (UNIX)
    target_link_directories(
        window-test
        PUBLIC
        ./lib
    )
endif (UNIX)

target_link_libraries(
    window-test
    PUBLIC
    axolote
    ${OPENGL_LIBRARIES} glfw assimp::assimp
)

# Header files
target_include_directories(
    window-test
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/include
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

# Libraries
if (UNIX)
    target_link_directories(
        models-and-shaders-test
        PUBLIC
        ./lib
    )
endif (UNIX)

target_link_libraries(
    models-and-shaders-test
    PUBLIC
    axolote
    ${OPENGL_LIBRARIES} glfw assimp::assimp
)

# Header files
target_include_directories(
    models-and-shaders-test
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/include
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
