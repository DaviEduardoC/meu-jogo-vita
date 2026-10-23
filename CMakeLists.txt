cmake_minimum_required(VERSION 3.0)
project(gow_3d_demake)

set(CMAKE_TOOLCHAIN_FILE "/usr/local/vitasdk/share/vita.toolchain.cmake")
include("/usr/local/vitasdk/share/vita.cmake")

set(VITA_APP_NAME "GOW 3D Demake")
set(VITA_TITLEID  "GOW3D0001")
set(VITA_VERSION  "01.00")

add_executable(gow_3d_demake src/main.c)

target_link_libraries(gow_3d_demake vitaGL SceGxm_stub SceDisplay_stub SceCtrl_stub m)

vita_create_vpk(gow_3d_demake ${VITA_TITLEID} ${VITA_APP_NAME})
