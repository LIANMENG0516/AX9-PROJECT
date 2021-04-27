#ifndef __SYSTEM_H
#define __SYSTEM_H

#include "stm32f4xx.h"

#include "gouble.h"

#define SYSTEM_OFF   0
#define SYSTEM_ON    1
#define SYSTEM_SLEEP 2

#define USB_CHANNEL 1
#define ECCOM_CHANNEL 2
#define DEBUGCOM_CHANNEL 3

typedef enum {FALSE = 0, TRUE = !FALSE} bool;

typedef struct
{    
    bool        TimeFlag;
    uint16_t    Time;
    
    bool        Adj_HV;
    bool        Adj_CW;
    
    bool        HV_Minitor;
    bool        CW_Minitor;
    
    uint16_t    T_VPP1;
    uint16_t    T_VNN1;
    uint16_t    T_VPP2;
    uint16_t    T_VNN2;

    uint16_t MAX_VPP1;
    uint16_t MIN_VPP1;
    uint16_t MAX_VNN1;
    uint16_t MIN_VNN1;
    
    uint16_t MAX_VPP2;
    uint16_t MIN_VPP2;
    uint16_t MAX_VNN2;
    uint16_t MIN_VNN2;
    
    uint16_t R_VPP1;
    uint16_t R_VNN1;
    uint16_t R_VPP2;
    uint16_t R_VNN2;
    
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
    
    uint16_t R_IADP;
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
    bool            Timeout;
    bool            HV_Send;
    bool            CW_Send;
    bool            Firmware_Send;
    bool            CompileInfo_Send;
    bool            Voltage_Send;
    bool            EcInfo_Send;
    uint8_t         Channel;                //命令通道, 是指程序接收到的命令从USB、ECCOM、DEBUGCOM哪个通道进入
}Command_Deal;

typedef struct
{
    Ad_VolStruct    AdjVol;
    SysTemper       Temperature;
    FanStrc         Fan;
    Command_Deal    Cmd;
    uint8_t		    SystemState;
    bool            KeyState;
    bool            PowerOnReq;
    bool            ShutDownReq;
    bool            System_S3_Change;
    bool            System_S4_Change;
    bool            S3_State;
    bool            S4_State;
    bool            S3Minitor;
}System_MsgStruct;

void Delay_Nop(uint16_t count);

bool System_PwrKey_Minitor(void);

bool System_S3_State_Minitor(void);

void SystemStateInit(void);

#endif
