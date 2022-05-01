#include "i2cdisplay.h"
#include "vmtoolbox.h"

const char JSTypeNameStr[] = "i2cDisplay" ;


const char* I2CDisplay::Name() {
    return "Plugin";
}

const char* I2CDisplay::JSTypeName() {
    return( (const char*) JSTypeNameStr );
}


// This is called when a new instance is needed for the JS code
// example : var x = new Log();
// make init here
I2CDisplay* I2CDisplay::allocNewInstance(ISDRVirtualMachineEnv *host) {
    (void)host ;
    I2CDisplay* result = new I2CDisplay();
    result->init();
    return( result );
}

// This is called when the allocated instance is no longer required
void I2CDisplay::deleteInstance(IJSClass *instance) {
    delete instance ;
}

void I2CDisplay::init() {
    display = nullptr ;
}


bool I2CDisplay::openI2C(char *bus_name) {
    i2c_bus = std::string(bus_name);
    display = new SSD1306::OledI2C( i2c_bus, 0x3C) ;
    display->clear();
    return( true );
}

void I2CDisplay::clear() {
    if( display != nullptr ) {
        display->clear();
    }
}

void I2CDisplay::update() {
    if( display != nullptr ) {
        display->displayUpdate();
    }
}

SSD1306::OledI2C *I2CDisplay::getDisplay() {
    return( display );
}

// we explain to the VM the methods we will add to this object
// method bridges are plain C function.
// each method exposed must have on C bridge function
//int push_method( void *stack ) ;
int configure_method( void *stack );
int clear_method(void *stack);
int update_method(void *stack);
int text8x8_method(void *stack);
int line_method( void *stack );

void I2CDisplay::declareMethods( ISDRVirtualMachineEnv *host ) {

    host->addMethod( (const char *)"configure", configure_method, true);
    host->addMethod( (const char *)"clear", clear_method, true);
    host->addMethod( (const char *)"update", update_method, true);
    host->addMethod( (const char *)"text8x8", text8x8_method, true); // text8x8( col[0..24],line[O...7],char *, set/clear)
    host->addMethod( (const char *)"line", line_method, true );
}

int configure_method( void *stack ) {
    bool ok = false ;
    int n = vmtools->getStackSize( stack );
    if( n < 1 ) {
        vmtools->throwException( stack, (char *)"Missing argument !");
        return(0);
    }
    const char *i2c_bus   = vmtools->getString( stack, 0 );
    I2CDisplay* object = (I2CDisplay *)vmtools->getObject(stack);
    if( object != nullptr ) {
        ok = object->openI2C( (char *)i2c_bus );
    }

    vmtools->pushBool( stack, ok );
    return(1);
}

int clear_method(void *stack) {
    I2CDisplay* object = (I2CDisplay *)vmtools->getObject(stack);
    if( object != nullptr ) {
        object->clear();
        return(1);
    }
    return(0);
}

int update_method(void *stack) {
    I2CDisplay* object = (I2CDisplay *)vmtools->getObject(stack);
    if( object != nullptr ) {
        object->update();
        return(1);
    }
    return(0);
}

// text8x8( line[0..24],row[O...7],char *, set/clear)
int text8x8_method(void *stack) {
    int n = vmtools->getStackSize( stack );
    if( n < 3 ) {
        vmtools->throwException( stack, (char *)"Missing arguments !");
        return(0);
    }
    int line = vmtools->getInt( stack, 0 );
    int row = vmtools->getInt( stack, 1 );
    char *msg = (char *)vmtools->getString( stack, 2);
    SSD1306::PixelStyle mode = SSD1306::PixelStyle::Set ;
    if( n >= 4 ) {
        int pmode = vmtools->getInt( stack, 3 );
        if( pmode == 0 )
            mode = SSD1306::PixelStyle::Unset ;
        if( pmode >= 1 )
            mode = SSD1306::PixelStyle::Set ;
    }

    I2CDisplay* object = (I2CDisplay *)vmtools->getObject(stack);
    if( object != nullptr ) {
        SSD1306::OledI2C *oled = object->getDisplay() ;
        if( oled != nullptr ) {
            SSD1306::drawString8x8(SSD1306::OledPoint{row, line * 8},
                                           std::string(msg),
                                           mode,
                                           (*oled));
            vmtools->pushBool( stack, true );
            return(1);
        }
    }
    vmtools->pushBool( stack, false );
    return(1);
}
// .line( x1, y1, x2, y2, [color]);
int line_method(void *stack) {
    int n = vmtools->getStackSize( stack );
    if( n < 4 ) {
        vmtools->throwException( stack, (char *)"Missing arguments !");
        return(0);
    }
    int x1 = vmtools->getInt( stack, 0 );
    int y1 = vmtools->getInt( stack, 1 );
    int x2 = vmtools->getInt( stack, 2 );
    int y2 = vmtools->getInt( stack, 3 );
    SSD1306::PixelStyle mode = SSD1306::PixelStyle::Set ;
    if( n >= 5 ) {
        int pmode = vmtools->getInt( stack, 4 );
        if( pmode == 0 )
            mode = SSD1306::PixelStyle::Unset ;
        if( pmode >= 1 )
            mode = SSD1306::PixelStyle::Set ;
    }
    I2CDisplay* object = (I2CDisplay *)vmtools->getObject(stack);
    if( object != nullptr ) {
        SSD1306::OledI2C *oled = object->getDisplay() ;
        if( oled != nullptr ) {
            SSD1306::line( SSD1306::OledPoint(x1, y1),
                           SSD1306::OledPoint(x2, y2),
                           mode,
                           (*oled));
            vmtools->pushBool( stack, true );
            return(1);
        }
    }
    vmtools->pushBool( stack, false );
    return(1);
}
