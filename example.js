var ok = loadPluginLib('/opt/vmbase/extensions/', 'libi2cDisplay');
var ok = ImportObject('libi2cDisplay', 'i2cDisplay');


var oled = new i2cDisplay();
oled.configure("/dev/i2c-0");

var oled = new i2cDisplay();
oled.configure("/dev/i2c-0");
oled.text8x8( 0,0,"OK");
oled.line(0,10,100,10);
oled.update();

