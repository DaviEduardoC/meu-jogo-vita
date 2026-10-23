
cmake_minimum_required(VERSION 3.16)

project(GodOfWarVita C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED ENV{VITASDK})
    message(FATAL_ERROR "VITASDK environment variable is not set")
endif()

set(VITASDK "$ENV{VITASDK}")
set(VITA_LIB "$ENV{VITASDK}/arm-vita-eabi/lib")

include("$ENV{VITASDK}/share/vita.cmake")

set(VITA_TITLEID "GOW000001")
set(VITA_VERSION "01.00")
set(VITA_APP_NAME "God of War Vita")

# Ajusta estes caminhos à estrutura real do projeto.
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.c")
    list(APPEND GAME_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.c")
endif()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
    list(APPEND GAME_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")
endif()

if(NOT GAME_SOURCES)
    message(FATAL_ERROR "No C/C++ source files found")
endif()

add_executable(${PROJECT_NAME} ${GAME_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${VITASDK}/arm-vita-eabi/include"
)

# Confirma a existência das bibliotecas antes de linkar.
set(VITA_REQUIRED_LIBS
    vitaGL
    vitashark
    mathneon
    SceShaccCgExt
    SceGxm_stub
    SceDisplay_stub
    SceCtrl_stub
    SceAppMgr_stub
    SceCommonDialog_stub
    SceSysmodule_stub
    SceKernelDmacMgr_stub
)

foreach(lib IN LISTS VITA_REQUIRED_LIBS)
    if(NOT EXISTS "${VITA_LIB}/lib${lib}.a")
        message(FATAL_ERROR
            "Missing library: ${VITA_LIB}/lib${lib}.a")
    endif()
endforeach()

# O grupo permite resolver dependências circulares entre
# bibliotecas estáticas. A ordem dentro do grupo deixa de
# ser determinante para a resolução dos símbolos.
target_link_libraries(${PROJECT_NAME} PRIVATE
    "-Wl,--start-group"

    vitaGL
    vitashark
    mathneon
    SceShaccCgExt

    SceGxm_stub
    SceShaccCg_stub
    SceDisplay_stub
    SceCtrl_stub
    SceAppMgr_stub
    SceCommonDialog_stub
    SceSysmodule_stub
    SceDmacMgr_stub

    m
    c
    gcc

    "-Wl,--end-group"
)

# Cria o executável SELF.
vita_create_self(
    ${PROJECT_NAME}.self
    ${PROJECT_NAME}
    UNSAFE
)

# Cria o pacote VPK.
vita_create_vpk(
    ${PROJECT_NAME}.vpk
    ${VITA_TITLEID}
    ${PROJECT_NAME}.self
    VERSION ${VITA_VERSION}
    NAME ${VITA_APP_NAME}
)
