cmake_minimum_required(VERSION 3.10)
project(TITANWoofer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    master.cpp
    framework/bios.cpp
    framework/disk.cpp
    framework/edid.cpp
    framework/clean.cpp
    framework/mac.cpp
    framework/utils.cpp 
)

include_directories(framework)
add_executable(TITANWoofer ${SOURCES})

if(WIN32)
    target_link_libraries(TITANWoofer iphlpapi)
endif()