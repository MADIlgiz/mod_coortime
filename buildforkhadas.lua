workspace "Mod_coortime_crossbuild"
configurations {"Debug"}

includedirs "/home/ilgiz/NEWretkslp/retk2/"
includedirs "/home/ilgiz/NEWretkslp/apks_slp/"
includedirs "/home/ilgiz/KHADASCARDIMAGE/ROOTFS1/usr/include"
includedirs "/home/ilgiz/KHADASCARDIMAGE/ROOTFS1/usr/lib"
includedirs "/home/ilgiz/KHADASSDCARDIMAGE/ROOTFS1/usr/include"
project "mod_coortime"
kind "ConsoleApp"
language "C++"
files{"./*.hpp","./*cpp"}
libdirs{"/home/ilgiz/NEWretkslp/libaarch64","/home/ilgiz/KHADASSDCARDIMAGE/ROOTFS1/usr/lib"}
links{"retk2","slp","gps"}
