cmake_minimum_required(VERSION 3.5)
project(gow_3d_demake)

include("$ENV{VITASDK}/share/vita.cmake" REQUIRED)

add_executable(gow_3d_demake src/main.c)

target_link_libraries(gow_3d_demake vitaGL SceGxm_stub SceDisplay_stub SceCtrl_stub stdc++ m c)

vita_create_vpk(gow_3d_demake GOW3D0001 "GOW 3D Demake")
