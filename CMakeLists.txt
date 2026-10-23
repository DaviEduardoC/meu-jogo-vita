cmake_minimum_required(VERSION 3.0)
project(gow_3d_demake)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  endif()
endif()

include($ENV{VITASDK}/share/vita.cmake REQUIRED)

set(VITA_APP_NAME "GOW 3D Demake")
set(VITA_TITLEID  "GOW3D0001")
set(VITA_VERSION  "01.00")

add_executable(gow_3d_demake src/main.c)

target_link_libraries(gow_3d_demake vitaGL SceGxm_stub SceDisplay_stub SceCtrl_stub m)

vita_create_vpk(gow_3d_demake ${VITA_TITLEID} ${VITA_APP_NAME})
