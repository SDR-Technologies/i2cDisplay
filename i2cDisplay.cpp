/****************************************************************
 *                                                              *
 * @copyright  Copyright (c) 2020 SDR-Technologies SAS          *
 * @author     Sylvain AZARIAN - s.azarian@sdr-technologies.fr  *
 * @project    SDR Virtual Machine                              *
 *                                                              *
 * Code propriete exclusive de la société SDR-Technologies SAS  *
 *                                                              *
 ****************************************************************/

#include <iostream>

#include "plugin_factory.h"
#include "vmsystem.h"
#include "vmtoolbox.h"

#include "i2cdisplay.h"

StackTools *vmtools = nullptr ;


SDK_PLUGIN_EXPORT_C
auto GetPluginFactory() -> IPluginFactory*
{

    static PluginFactory pinfo = [] {
        auto p = PluginFactory("SDRVM Extensions", "0.1-alpha");
        p.registerClass<I2CDisplay>("i2cDisplay");
        return p;
    }();
    return &pinfo;
}


SDK_PLUGIN_EXPORT_C
void setTools( StackTools *tools ) {
    vmtools = tools ;
}

struct _DLLInit{
    _DLLInit(){
        vmtools = nullptr ;

        std::cerr << " [TRACE] i2cDisplay loaded OK." << std::endl;
    }
    ~_DLLInit(){
        std::cerr << " [TRACE] i2cDisplay unloaded." << std::endl;
    }

} dll_init;
