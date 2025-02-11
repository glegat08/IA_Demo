cmake_minimum_required(VERSION 3.28)
project(IAGame VERSION 1.0.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/app/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/app/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/app/bin)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)

# Forcer la génération des DLLs
set(SFML_BUILD_SHARED_LIBS TRUE CACHE BOOL "Build shared SFML libraries")

# Options pour ne pas inclure des parties inutiles de SFML
set(SFML_BUILD_EXAMPLES FALSE)
set(SFML_BUILD_DOC FALSE)
set(SFML_BUILD_TEST FALSE)
# set(SFML_BUILD_AUDIO FALSE)
# set(SFML_BUILD_NETWORK FALSE)

FetchContent_MakeAvailable(SFML)

add_subdirectory(mylib)
add_subdirectory(mainFile)

target_include_directories(mylib PUBLIC ${SFML_SOURCE_DIR}/include)