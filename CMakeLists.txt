cmake_minimum_required(VERSION 3.1)
project(i2cDisplay
    VERSION 1.0
    DESCRIPTION "antennaSwitch plugin Cmake"
    LANGUAGES CXX)
set(CMAKE_BUILD_TYPE Release)
include_directories(.)
include_directories(libSSD1306/lib)
set(SOURCES "")
list(APPEND SOURCES
    i2cDisplay.cpp 
    i2cdisplay.cpp 
    libSSD1306/lib/FileDescriptor.cpp 
    libSSD1306/lib/OledFont8x12.cpp 
    libSSD1306/lib/OledFont8x16.cpp 
    libSSD1306/lib/OledFont8x8.cpp 
    libSSD1306/lib/OledGraphics.cpp 
    libSSD1306/lib/OledHardware.cpp 
    libSSD1306/lib/OledI2C.cpp 
    libSSD1306/lib/OledPixel.cpp)

add_library(i2cDisplay SHARED ${SOURCES})
target_link_libraries(i2cDisplay pthread) 

set(CMAKE_CXX_FLAGS_RELEASE "-O2")
# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION /opt/vmbase/extensions )
