/****************************************************************
 *                                                              *
 * @copyright  Copyright (c) 2020 SDR-Technologies SAS          *
 * @author     Sylvain AZARIAN - s.azarian@sdr-technologies.fr  *
 * @project    SDR Virtual Machine                              *
 *                                                              *
 * Code propriete exclusive de la société SDR-Technologies SAS  *
 *                                                              *
 ****************************************************************/


#ifndef VMSYSTEM_H
#define VMSYSTEM_H


typedef int (*js_c_function)(void *ctx);
class IJSClass ;

class ISDRVirtualMachineEnv {
public:
    virtual IJSClass* getInstance( const char *JSTypeName ) ;
    virtual void pushInstance( IJSClass *instance  );
  
    virtual void addMethod( const char *method_name, js_c_function method_call, bool args=false);
} ;


#endif // VMSYSTEM_H
