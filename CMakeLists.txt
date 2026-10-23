
set(VITA_LIB "$ENV{VITASDK}/arm-vita-eabi/lib")

# Bibliotecas necessárias ao projeto.
set(VITA_REQUIRED_LIBS
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
    SceKernelDmacMgr_stub
)

# Verificar as bibliotecas realmente instaladas.
foreach(lib IN LISTS VITA_REQUIRED_LIBS)
    if(NOT EXISTS "${VITA_LIB}/lib${lib}.a")
        message(FATAL_ERROR
            "Biblioteca em falta: ${VITA_LIB}/lib${lib}.a")
    endif()
endforeach()

# Ligar as bibliotecas ao executável.
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
    SceKernelDmacMgr_stub
    m
    c
    gcc
    "-Wl,--end-group"
)
