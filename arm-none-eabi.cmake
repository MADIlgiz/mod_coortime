set (CMAKE_CROSSCOMPILING true)
set(CMAKE_SYSTEM linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

#set(CMAKE_SYSROOT /home/ilgiz/BOARDROOTFS)
#set(CMAKE_SYSROOT /media/ilgiz/ROOTFS)
set(CMAKE_SYSROOT /home/ilgiz/KHADASSDCARDIMAGE/ROOTFS1)
set(tools /opt/gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu/bin)
#include_directories("/media/ilgiz/OPT/retk2")
#include_directories("/media/ilgiz/OPT/apks_slp")
include_directories(/opt/gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu/aarch64-none-linux-gnu/include)
#include_directories("/home/ilgiz/BOARDROOTFS/usr/include")
include_directories("/home/ilgiz/opencv_cross/opencv/platforms/linux/build/install/include")
include_directories("/home/ilgiz/opencv_cross/opencv/platforms/linux/build/install/include/opencv4")
set(CMAKE_C_COMPILER /opt/gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER /opt/gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-g++)




set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

#set(CMAKE_EXE_LINKER_FLAGS "-L/opt/gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu/aarch64-none-linux-gnu/lib")
#set(CMAKE_EXE_LINKER_FLAGS "-L/opt/gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu/aarch64-none-linux-gnu/lib/libslp.a")
#target_link_libraries(/opt/gcc-arm-10.2-2020.11-x86_64-aarch64-none-linux-gnu/aarch64-none-linux-gnu/lib/libretk2.a)
