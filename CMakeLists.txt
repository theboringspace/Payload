cmake_minimum_required(VERSION 3.24)

project(Payload
    VERSION 0.1.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# ---------------------------------------------------------------------------
# Raylib: use an installed copy if available (e.g. MSYS2 mingw-w64-ucrt-x86_64-raylib),
# otherwise download and build it from source.
# ---------------------------------------------------------------------------
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET)

if(NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        ${RAYLIB_VERSION}
        GIT_SHALLOW    TRUE
    )
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(raylib)
endif()

# ---------------------------------------------------------------------------
# Game executable
# ---------------------------------------------------------------------------
file(GLOB_RECURSE PAYLOAD_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(${PROJECT_NAME} ${PAYLOAD_SOURCES})

# Every folder containing a header is an include path, so both "Scene.h" and
# "Scenes/Scene.h" resolve. New subfolders (e.g. include/UI) are picked up automatically.
file(GLOB_RECURSE PAYLOAD_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
)

set(PAYLOAD_INCLUDE_DIRS
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
foreach(header IN LISTS PAYLOAD_HEADERS)
    get_filename_component(header_dir "${header}" DIRECTORY)
    list(APPEND PAYLOAD_INCLUDE_DIRS "${header_dir}")
endforeach()
list(REMOVE_DUPLICATES PAYLOAD_INCLUDE_DIRS)

target_include_directories(${PROJECT_NAME} PRIVATE ${PAYLOAD_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Hide the console window in Release builds on Windows.
if(WIN32 AND CMAKE_BUILD_TYPE STREQUAL "Release")
    if(MSVC)
        target_link_options(${PROJECT_NAME} PRIVATE /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup)
    else()
        target_link_options(${PROJECT_NAME} PRIVATE -mwindows)
    endif()
endif()

# Absolute path to assets for development; copied next to the exe for distribution.
target_compile_definitions(${PROJECT_NAME} PRIVATE
    ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    COMMENT "Copying assets"
)


# ---------------------------------------------------------------------------
# Sandbox Executable
# ---------------------------------------------------------------------------
# Sandbox: all game code except the real main.cpp, plus TestFiles/
list(FILTER PAYLOAD_SOURCES EXCLUDE REGEX "/main\\.cpp$")
file(GLOB_RECURSE SANDBOX_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/TestFiles/testSrc/*.cpp")
add_executable(Sandbox ${PAYLOAD_SOURCES} ${SANDBOX_SOURCES})
target_include_directories(Sandbox PRIVATE ${PAYLOAD_INCLUDE_DIRS})
target_include_directories(Sandbox PRIVATE testFiles/testInclude)
target_link_libraries(Sandbox PRIVATE raylib)
