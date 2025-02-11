project(mainFile)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SOURCES
    ${SOURCE_DIR}/main.cpp
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME}
PUBLIC
    mylib
PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

# Chemin vers le dossier libs/sfml_dlls contenant les DLLs
set(SFML_DLL_DIR "${CMAKE_SOURCE_DIR}/libs")

# Liste des DLLs communes (pour Release)
set(SFML_DLLS
    "sfml-graphics-2.dll"
    "sfml-window-2.dll"
    "sfml-system-2.dll"
    "sfml-audio-2.dll"
)

# Liste des DLLs pour le mode Debug
set(SFML_DLLS_DEBUG
    "sfml-graphics-d-2.dll"
    "sfml-window-d-2.dll"
    "sfml-system-d-2.dll"
    "sfml-audio-d-2.dll"
)

# Détection du mode de compilation (Debug ou Release)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(SFML_DLLS_TO_COPY ${SFML_DLLS_DEBUG})
else()
    set(SFML_DLLS_TO_COPY ${SFML_DLLS})
endif()

# Commande pour copier les DLLs après la construction
if(WIN32)
    foreach(DLL ${SFML_DLLS_TO_COPY})
        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${SFML_DLL_DIR}/${DLL}"
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    endforeach()
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Work")