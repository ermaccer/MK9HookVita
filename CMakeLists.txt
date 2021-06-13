cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(mk9hook_vita)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-q -Wall -O3 -std=gnu99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions")

include_directories(
)

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

if (NOT ${RELEASE})
  add_definitions(-DENABLE_LOGGING)
endif()

add_executable(${PROJECT_NAME}
  main.c
  draw.c
  mk9menu.c
  mk9.c
)
# in case i need anything
target_link_libraries(${PROJECT_NAME}
  taihen_stub
  taihenForKernel_stub
  taihenModuleUtils_stub
  SceAppMgr_stub
  SceDisplay_stub
  SceCtrl_stub
  SceKernelModulemgr_stub
  SceLibKernel_stub
  SceIofilemgr_stub
  SceLibc_stub
  SceKernelThreadMgr_stub 
  SceShutterSound_stub 
  SceSysmodule_stub 
  SceIofilemgrForDriver_stub
  SceSblAIMgrForDriver_stub
  SceThreadmgrForDriver_stub
  SceSysclibForDriver_stub
  SceSysmemForDriver_stub
  SceProcessmgrForDriver_stub
  SceSysrootForKernel_stub
  SceAppMgrForDriver_stub
  ScePowerForDriver_stub
  SceCtrlForDriver_stub
  SceIofilemgrForDriver_stub
  SceSblAIMgrForDriver_stub
  SceLibc_stub_weak
  SceNet_stub_weak
  SceNetCtl_stub_weak
  SceSysmem_stub_weak
  SceDisplay_stub_weak
  SceSysmodule_stub_weak
  SceIofilemgr_stub_weak
  SceLibKernel_stub_weak
  SceKernelThreadMgr_stub_weak
  SceKernelModulemgr_stub_weak
  gcc
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES LINK_FLAGS "-nostdlib"
)

vita_create_self(${PROJECT_NAME}.suprx ${PROJECT_NAME}
  UNSAFE
  CONFIG ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}.yml
)