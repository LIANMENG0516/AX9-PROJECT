#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "stm32f4xx.h"

#include "gouble.h"

#define SYSTEM_OFF   0
#define SYSTEM_ON    1
#define SYSTEM_SLEEP 2

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
    uint8_t		    SystemState;
    bool            PowerOnReq;
    bool            ShutDownReq;
    bool            System_S3_Change;
    
}System_MsgStruct;


bool System_PwrKey_Minitor(void);



#endif
