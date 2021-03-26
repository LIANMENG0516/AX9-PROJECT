#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "stm32f4xx.h"

#include "gouble.h"

#define SYSTEM_OFF   0
#define SYSTEM_ON    1
#define SYSTEM_SLEEP 2

typedef enum {FALSE = 0, TRUE = !FALSE} bool;

#define SAMPLE_A3V75_SEQUENCE       5
#define SAMPLE_A2V25_SEQUENCE       6
#define SAMPLE_AP12V_SEQUENCE       7
#define SAMPLE_AN12V_SEQUENCE       8
#define SAMPLE_AP5V5_1_SEQUENCE     9
#define SAMPLE_AP5V5_2_SEQUENCE     10
#define SAMPLE_AN5V5_SEQUENCE       11
#define SAMPLE_D5V_SEQUENCE         12
#define SAMPLE_D0V95_SEQUENCE       13
#define SAMPLE_D1V45_SEQUENCE       14

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
    
    uint16_t R_VPP1;
    uint16_t R_VNN1;
    uint16_t R_VPP2;
    uint16_t R_VNN2;
    uint16_t R_PCW;
    uint16_t R_NCW;
    
    uint16_t R_A3V75;
    uint16_t R_A2V25;
    uint16_t R_AP12V;
    uint16_t R_AN12V;
    uint16_t R_AP5V5_1;
    uint16_t R_AP5V5_2;
    
    uint16_t R_AN5V5;
    uint16_t R_D5V;
    uint16_t R_D0V95;
    uint16_t R_D1V45;
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
    bool            System_S4_Change;
    bool            S3Minitor;
}System_MsgStruct;

void Delay_Nop(uint16_t count);

bool System_PwrKey_Minitor(void);

void System_S3_State_Minitor(void);

void SystemStateInit(void);

#endif
