cmake_minimum_required (VERSION 2.6)

# This line will export your dependency's symbols and make them available to your project on Windows. Without this your code will compile but it won't run on Windows!
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# ------------------------------------------------------------------------------
# use c++11
if (WIN32)
    add_definitions(-std:c++latest)
endif (WIN32)

if (UNIX)
    add_definitions(-std=c++17)
endif (UNIX)

# ------------------------------------------------------------------------------
# project name
project (gamelib3)



# ------------------------------------------------------------------------------
# library output folder
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib/$<0:>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib/$<0:>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../lib/$<0:>)

# ------------------------------------------------------------------------------
# export for windows
set(CMAKE_EXPORT_COMPILE_COMMANDS ON )

# ------------------------------------------------------------------------------
# include dirs
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include)

# --------------------------------------------------
# lib dirs
# --------------------------------------------------
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../lib)

# ------------------------------------------------------------------------------
# project build
add_library(gamelib3 SHARED
src/physics/integration.cpp
src/physics/movable.cpp
src/graphics/renderable.cpp
src/graphics/primitives.cpp
src/graphics/autotexture.cpp
src/graphics/sprite.cpp
src/engine/entity.cpp
src/engine/engine.cpp
src/math/vector.cpp
src/utils/files.cpp
src/utils/file.cpp
src/utils/timer.cpp
src/utils/grid.cpp
src/camera/camera.cpp
)

# ------------------------------------------------------------------------------
# dll export for windows
if(MSVC)
    target_compile_definitions(gamelib3 PRIVATE WIN_EXPORT)
endif()

# ------------------------------------------------------------------------------
# install headers
INSTALL ( DIRECTORY src/
  DESTINATION ${CMAKE_BINARY_DIR}/../../include/gamelib3
  FILES_MATCHING PATTERN "*.h*"
  )

# ------------------------------------------------------------------------------
# link SFML DEBUG
target_link_libraries (gamelib3 debug sfml-graphics-d)
target_link_libraries (gamelib3 debug sfml-window-d)
target_link_libraries (gamelib3 debug sfml-system-d)

# ------------------------------------------------------------------------------
# link SFML RELEASE
target_link_libraries (gamelib3 optimized sfml-graphics)
target_link_libraries (gamelib3 optimized sfml-window)
target_link_libraries (gamelib3 optimized sfml-system)

find_package(OpenGL)
target_link_libraries (gamelib3 ${OPENGL_gl_LIBRARY})
