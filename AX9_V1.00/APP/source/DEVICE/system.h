#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "stm32f4xx.h"

#include "gouble.h"

#define SYSTEM_ON  TRUE
#define SYSTEM_OFF FALSE

typedef enum {FALSE = 0, TRUE = !FALSE} bool;

typedef struct
{
    bool CMD_HVFlag;           //高压调压标志
    bool CMD_CWFlag;           //低压调压标志
    
    uint16_t T_VPP1;
    uint16_t T_VNN1;
    uint16_t T_VPP2;
    uint16_t T_VNN2;
    uint16_t T_PCW;
    uint16_t T_NCW;

}Ad_VolStruct;

typedef struct
{    
    uint8_t FPGA1;
    uint8_t FPGA;
    uint8_t CPU;
    uint8_t USPB;
}SysTemper;

typedef struct
{    
    uint16_t Rpm1;
    uint16_t Rpm2;
    uint16_t Rpm3;
    uint16_t Rpm4;
    uint16_t Rpm5;

}FanStrc;



typedef struct
{
    Ad_VolStruct    AdVolStr;
    SysTemper       Temperature;
    FanStrc         Fan;
    bool		    SystemState;
    
}System_MsgStruct;


bool System_PowerControl(void);



#endif
