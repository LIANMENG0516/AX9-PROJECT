#ifndef __EMC2305_H
#define __EMC2305_H

#include "stm32f4xx.h"

#define EMC2305_ADDR_10K    0x58

#define BASIC_CTL           0x20
#define PWM_POLARITY        0x2a
#define PWM_OUTPUT          0x2b
#define PWM45_BASE          0x2c
#define PWM123_BASE         0x2d

#define FAN1_SETTING        0x30
#define FAN2_SETTING        0x40
#define FAN3_SETTING        0x50
#define FAN4_SETTING        0x60
#define FAN5_SETTING        0x70

#define FAN1_TACHREAD_HIGH  0x3e 
#define FAN1_TACHREAD_LOW   0x3f 
#define FAN2_TACHREAD_HIGH  0x4e 
#define FAN2_TACHREAD_LOW   0x4f 
#define FAN3_TACHREAD_HIGH  0x5e 
#define FAN3_TACHREAD_LOW   0x5f 
#define FAN4_TACHREAD_HIGH  0x6e 
#define FAN4_TACHREAD_LOW   0x6f 
#define FAN5_TACHREAD_HIGH  0x7e 
#define FAN5_TACHREAD_LOW   0x7f 

#define SPEED_NoMin         0x0c    //最小占空比5%
#define SPEED_NoMax         0xff    //最大占空比100%

#define TEMPERATURE_95      95
#define TEMPERATURE_50      50

void Fan_Emc2305_Init(void);
void Fan_Emc2305_Control(void);
void Fan_Speed_Read(void);
void Write_Emc2305_Reg(uint16_t addr, uint16_t val);
uint8_t Read_Emc2305_Reg(uint8_t addr);


#endif
