QT       -= core gui

TARGET = /opt/vmbase/extensions/i2cDisplay
TEMPLATE = lib

SOURCES +=  \
    i2cDisplay.cpp \
    i2cdisplay.cpp \
    libSSD1306/lib/FileDescriptor.cpp \
    libSSD1306/lib/OledFont8x12.cpp \
    libSSD1306/lib/OledFont8x16.cpp \
    libSSD1306/lib/OledFont8x8.cpp \
    libSSD1306/lib/OledGraphics.cpp \
    libSSD1306/lib/OledHardware.cpp \
    libSSD1306/lib/OledI2C.cpp \
    libSSD1306/lib/OledPixel.cpp

HEADERS += \
    i2cdisplay.h \
    libSSD1306/lib/FileDescriptor.h \
    libSSD1306/lib/OledBitmap.h \
    libSSD1306/lib/OledFont8x12.h \
    libSSD1306/lib/OledFont8x16.h \
    libSSD1306/lib/OledFont8x8.h \
    libSSD1306/lib/OledGraphics.h \
    libSSD1306/lib/OledHardware.h \
    libSSD1306/lib/OledI2C.h \
    libSSD1306/lib/OledPixel.h \
    libSSD1306/lib/point.h \
    vmplugins.h \
    vmsystem.h \
    plugin_factory.h \
    plugin_interface.h \
    vmtoolbox.h \
    vmtypes.h

DISTFILES += \
    README.md \
    example.js
