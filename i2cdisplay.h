#ifndef I2CDISPLAY_H
#define I2CDISPLAY_H

#include <string>

#include "vmplugins.h"
#include "vmtypes.h"
#include "libSSD1306/lib/OledFont8x16.h"
#include "libSSD1306/lib/OledFont8x8.h"
#include "libSSD1306/lib/OledI2C.h"
#include "libSSD1306/lib/OledGraphics.h"

class I2CDisplay : public IJSClass
{
public:
    I2CDisplay() = default;

    const char* Name() ;
    const char* JSTypeName() ;
    I2CDisplay* allocNewInstance(ISDRVirtualMachineEnv *host) ;
    void deleteInstance( IJSClass *instance ) ;
    void declareMethods( ISDRVirtualMachineEnv *host ) ;

    void init();
    bool openI2C( char *bus_name );
    void clear();
    void update();

    SSD1306::OledI2C *getDisplay();

private:
    std::string i2c_bus ;
    SSD1306::OledI2C *display ;


};

#endif // I2CDISPLAY_H
