project(mylib)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES
    ${SOURCE_DIR}/engine.cpp
    ${SOURCE_DIR}/hero.cpp
    ${SOURCE_DIR}/boss.cpp
    ${SOURCE_DIR}/closeWeapon.cpp
    ${SOURCE_DIR}/rangedWeapon.cpp
    ${SOURCE_DIR}/sceneManager.cpp
    ${SOURCE_DIR}/sceneBase.cpp
    ${SOURCE_DIR}/bossBehavior.cpp
    ${SOURCE_DIR}/gameObject.cpp
    ${SOURCE_DIR}/pause.cpp
    ${SOURCE_DIR}/game.cpp
    ${SOURCE_DIR}/menu.cpp
)

set(HEADERS
    ${HEADER_DIR}/engine.h
    ${HEADER_DIR}/hero.h
    ${HEADER_DIR}/boss.h
    ${HEADER_DIR}/closeWeapon.h
    ${HEADER_DIR}/rangedWeapon.h
    ${HEADER_DIR}/sceneManager.h
    ${HEADER_DIR}/sceneBase.h
    ${HEADER_DIR}/bossBehavior.h
    ${HEADER_DIR}/gameObject.h
    ${HEADER_DIR}/game.h
    ${HEADER_DIR}/pause.h
    ${HEADER_DIR}/menu.h
)

add_library(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

target_include_directories(${PROJECT_NAME}
PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${HEADER_DIR}>
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Libraries")