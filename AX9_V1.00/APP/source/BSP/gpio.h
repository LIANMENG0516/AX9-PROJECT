#ifndef __GPIO_H_
#define __GPIO_H_

#include "stm32f4xx.h"

//DEBUG_COM
#define DEBUG_COM_PORT_TX         GPIOA
#define DEBUG_COM_PIN_TX          GPIO_Pin_0
#define DEBUG_COM_PIN_TX_MODE     GPIO_Mode_AF
#define DEBUG_COM_PIN_TX_OTYPE    GPIO_OType_PP
#define DEBUG_COM_PIN_TX_PUPD     GPIO_PuPd_NOPULL

#define DEBUG_COM_PORT_RX         GPIOA
#define DEBUG_COM_PIN_RX          GPIO_Pin_1
#define DEBUG_COM_PIN_RX_MODE     GPIO_Mode_AF
#define DEBUG_COM_PIN_RX_OTYPE    GPIO_OType_PP
#define DEBUG_COM_PIN_RX_PUPD     GPIO_PuPd_NOPULL

//COMM_COM
#define COMM_COM_PORT_TX          GPIOD
#define COMM_COM_PIN_TX           GPIO_Pin_5
#define COMM_COM_PIN_TX_MODE      GPIO_Mode_AF
#define COMM_COM_PIN_TX_OTYPE     GPIO_OType_PP
#define COMM_COM_PIN_TX_PUPD      GPIO_PuPd_NOPULL

#define COMM_COM_PORT_RX          GPIOD
#define COMM_COM_PIN_RX           GPIO_Pin_6
#define COMM_COM_PIN_RX_MODE      GPIO_Mode_AF
#define COMM_COM_PIN_RX_OTYPE     GPIO_OType_PP
#define COMM_COM_PIN_RX_PUPD      GPIO_PuPd_NOPULL

//SPI3
#define SPI3_PORT_SCK             GPIOC
#define SPI3_PIN_SCK              GPIO_Pin_10
#define SPI3_PIN_SCK_MODE         GPIO_Mode_AF
#define SPI3_PIN_SCK_OTYPE        GPIO_OType_PP
#define SPI3_PIN_SCK_PUPD         GPIO_PuPd_NOPULL

#define SPI3_PORT_MOSI            GPIOC
#define SPI3_PIN_MOSI             GPIO_Pin_11
#define SPI3_PIN_MOSI_MODE        GPIO_Mode_AF
#define SPI3_PIN_MOSI_OTYPE       GPIO_OType_PP
#define SPI3_PIN_MOSI_PUPD        GPIO_PuPd_NOPULL

#define SPI3_PORT_MISO            GPIOC  
#define SPI3_PIN_MISO             GPIO_Pin_12
#define SPI3_PIN_MISO_MODE        GPIO_Mode_IN
#define SPI3_PIN_MISO_OTYPE       GPIO_OType_PP
#define SPI3_PIN_MISO_PUPD        GPIO_PuPd_NOPULL

#define SPI3_PIN_CS_MODE          GPIO_Mode_OUT
#define SPI3_PIN_CS_OTYPE         GPIO_OType_PP
#define SPI3_PIN_CS_PUPD          GPIO_PuPd_NOPULL
#define SPI3_PORT_CS              GPIOB
#define SPI3_PIN_CS2              GPIO_Pin_13
#define SPI3_PIN_CS3              GPIO_Pin_0
#define SPI3_PIN_CS4              GPIO_Pin_14

#define CTL_SPI3_PIN_CS2(x)       x ? GPIO_SetBits(SPI3_PORT_CS, SPI3_PIN_CS2) : GPIO_ResetBits(SPI3_PORT_CS, SPI3_PIN_CS2)
#define CTL_SPI3_PIN_CS3(x)       x ? GPIO_SetBits(SPI3_PORT_CS, SPI3_PIN_CS3) : GPIO_ResetBits(SPI3_PORT_CS, SPI3_PIN_CS3)
#define CTL_SPI3_PIN_CS4(x)       x ? GPIO_SetBits(SPI3_PORT_CS, SPI3_PIN_CS4) : GPIO_ResetBits(SPI3_PORT_CS, SPI3_PIN_CS4)

//DAC
#define DACOUT1_PORT              GPIOA
#define DACOUT1_PIN               GPIO_Pin_4
#define DACOUT1_MODE              GPIO_Mode_AF
#define DACOUT1_OType             GPIO_OType_PP
#define DACOUT1_PuPd              GPIO_PuPd_NOPULL

#define DACOUT2_PORT              GPIOA
#define DACOUT2_PIN               GPIO_Pin_5
#define DACOUT2_MODE              GPIO_Mode_AF
#define DACOUT2_OType             GPIO_OType_PP
#define DACOUT2_PuPd              GPIO_PuPd_NOPULL

//ADC-VPP1    
#define T_VPP1_PORT               GPIOC
#define T_VPP1_PIN                GPIO_Pin_0
#define T_VPP1_PIN_MODE           GPIO_Mode_AN
#define T_VPP1_PIN_OTYPE          GPIO_OType_PP
#define T_VPP1_PIN_PUPD           GPIO_PuPd_NOPULL

//ADC-VNN1    
#define T_VNN1_PORT               GPIOC
#define T_VNN1_PIN                GPIO_Pin_1
#define T_VNN1_PIN_MODE           GPIO_Mode_AN
#define T_VNN1_PIN_OTYPE          GPIO_OType_PP
#define T_VNN1_PIN_PUPD           GPIO_PuPd_NOPULL

//ADC-VPP2    
#define T_VPP2_PORT               GPIOC
#define T_VPP2_PIN                GPIO_Pin_2
#define T_VPP2_PIN_MODE           GPIO_Mode_AN
#define T_VPP2_PIN_OTYPE          GPIO_OType_PP
#define T_VPP2_PIN_PUPD           GPIO_PuPd_NOPULL

//ADC-VNN2    
#define T_VNN2_PORT               GPIOC
#define T_VNN2_PIN                GPIO_Pin_3
#define T_VNN2_PIN_MODE           GPIO_Mode_AN
#define T_VNN2_PIN_OTYPE          GPIO_OType_PP
#define T_VNN2_PIN_PUPD           GPIO_PuPd_NOPULL

//ADC-IAPD    
#define T_IAPD_PORT               GPIOC
#define T_IAPD_PIN                GPIO_Pin_5
#define T_IAPD_PIN_MODE           GPIO_Mode_AN
#define T_IAPD_PIN_OTYPE          GPIO_OType_PP
#define T_IAPD_PIN_PUPD           GPIO_PuPd_NOPULL

//ADC-A2V25   
#define T_A2V25_PORT              GPIOF
#define T_A2V25_PIN               GPIO_Pin_3
#define T_A2V25_PIN_MODE          GPIO_Mode_AN
#define T_A2V25_PIN_OTYPE         GPIO_OType_PP
#define T_A2V25_PIN_PUPD          GPIO_PuPd_NOPULL    

//ADC-A3V75   
#define T_A3V75_PORT              GPIOF
#define T_A3V75_PIN               GPIO_Pin_4
#define T_A3V75_PIN_MODE          GPIO_Mode_AN
#define T_A3V75_PIN_OTYPE         GPIO_OType_PP
#define T_A3V75_PIN_PUPD          GPIO_PuPd_NOPULL

//ADC-AP5V5_1   
#define T_AP5V5_1_PORT            GPIOF
#define T_AP5V5_1_PIN             GPIO_Pin_5
#define T_AP5V5_1_PIN_MODE        GPIO_Mode_AN
#define T_AP5V5_1_PIN_OTYPE       GPIO_OType_PP
#define T_AP5V5_1_PIN_PUPD        GPIO_PuPd_NOPULL
    
//ADC-AP12V   
#define T_AP12V_PORT              GPIOF
#define T_AP12V_PIN               GPIO_Pin_6
#define T_AP12V_PIN_MODE          GPIO_Mode_AN
#define T_AP12V_PIN_OTYPE         GPIO_OType_PP
#define T_AP12V_PIN_PUPD          GPIO_PuPd_NOPULL

//ADC-AN5V5   
#define T_AN5V5_PORT              GPIOF
#define T_AN5V5_PIN               GPIO_Pin_7
#define T_AN5V5_PIN_MODE          GPIO_Mode_AN
#define T_AN5V5_PIN_OTYPE         GPIO_OType_PP
#define T_AN5V5_PIN_PUPD          GPIO_PuPd_NOPULL    

//ADC-AN12V   
#define T_AN12V_PORT              GPIOF
#define T_AN12V_PIN               GPIO_Pin_8
#define T_AN12V_PIN_MODE          GPIO_Mode_AN
#define T_AN12V_PIN_OTYPE         GPIO_OType_PP
#define T_AN12V_PIN_PUPD          GPIO_PuPd_NOPULL 

//ADC-D0V95   
#define T_D0V95_PORT              GPIOF
#define T_D0V95_PIN               GPIO_Pin_9
#define T_D0V95_PIN_MODE          GPIO_Mode_AN
#define T_D0V95_PIN_OTYPE         GPIO_OType_PP
#define T_D0V95_PIN_PUPD          GPIO_PuPd_NOPULL 

//ADC-D1V45
#define T_D1V45_PORT              GPIOF
#define T_D1V45_PIN               GPIO_Pin_10
#define T_D1V45_PIN_MODE          GPIO_Mode_AN
#define T_D1V45_PIN_OTYPE         GPIO_OType_PP
#define T_D1V45_PIN_PUPD          GPIO_PuPd_NOPULL 

//ADC-AP5V5_2
#define T_AP5V5_2_PORT            GPIOA
#define T_AP5V5_2_PIN             GPIO_Pin_2
#define T_AP5V5_2_PIN_MODE        GPIO_Mode_AN
#define T_AP5V5_2_PIN_OTYPE       GPIO_OType_PP
#define T_AP5V5_2_PIN_PUPD        GPIO_PuPd_NOPULL  
    
//ADC-D5V
#define T_D5V_PORT                GPIOA
#define T_D5V_PIN                 GPIO_Pin_3
#define T_D5V_PIN_MODE            GPIO_Mode_AN
#define T_D5V_PIN_OTYPE           GPIO_OType_PP
#define T_D5V_PIN_PUPD            GPIO_PuPd_NOPULL  

//EMC2305_SCK
#define EMC_SCK_PORT              GPIOB
#define EMC_SCK_PIN               GPIO_Pin_6
#define EMC_SCK_PIN_MODE          GPIO_Mode_OUT
#define EMC_SCK_PIN_OTYPE         GPIO_OType_PP
#define EMC_SCK_PIN_PUPD          GPIO_PuPd_UP  
#define EMC_SCK_1()               GPIO_SetBits(EMC_SCK_PORT, EMC_SCK_PIN)
#define EMC_SCK_0()               GPIO_ResetBits(EMC_SCK_PORT, EMC_SCK_PIN)
    
//EMC2305_SDA
#define EMC_SDA_PORT              GPIOB
#define EMC_SDA_PIN               GPIO_Pin_7
#define EMC_SDA_MODE              GPIO_Mode_OUT
#define EMC_SDA_OTYPE             GPIO_OType_PP
#define EMC_SDA_PUPD              GPIO_PuPd_UP  
#define EMC_SDA_1()               GPIO_SetBits(EMC_SDA_PORT, EMC_SDA_PIN)
#define EMC_SDA_0()               GPIO_ResetBits(EMC_SDA_PORT, EMC_SDA_PIN)
#define EMC_SDA_IN()              {GPIOD->MODER = GPIOD->MODER & 0xFFFF3FFF;}
#define EMC_SDA_OUT()             {GPIOD->MODER = GPIOD->MODER & 0xFFFF7FFF; GPIOD->MODER = GPIOD->MODER | 0x00004000;}
#define EMC_SDA_READ()            GPIO_ReadInputDataBit(EMC_SDA_PORT, EMC_SDA_PIN)



//TMP_SCK
#define TMP_SCK_PORT              GPIOB      
#define TMP_SCK_PIN               GPIO_Pin_8    
#define TMP_SCK_PIN_MODE          GPIO_Mode_OUT
#define TMP_SCK_PIN_OTYPE         GPIO_OType_PP
#define TMP_SCK_PIN_PUPD          GPIO_PuPd_UP
#define TMP_SCK_1()               GPIO_SetBits(TMP_SCK_PORT, TMP_SCK_PIN)
#define TMP_SCK_0()               GPIO_ResetBits(TMP_SCK_PORT, TMP_SCK_PIN)


//TMP_SDA
#define TMP_SDA_PORT              GPIOB
#define TMP_SDA_PIN               GPIO_Pin_9
#define TMP_SDA_MODE              GPIO_Mode_OUT
#define TMP_SDA_OTYPE             GPIO_OType_PP
#define TMP_SDA_PUPD              GPIO_PuPd_UP  
#define TMP_SDA_1()               GPIO_SetBits(TMP_SDA_PORT, TMP_SDA_PIN)
#define TMP_SDA_0()               GPIO_ResetBits(TMP_SDA_PORT, TMP_SDA_PIN)
#define TMP_SDA_IN()              {GPIOB->MODER = GPIOB->MODER & 0xFFF3FFFF;}
#define TMP_SDA_OUT()             {GPIOB->MODER = GPIOB->MODER & 0xFFF7FFFF; GPIOB->MODER = GPIOB->MODER | 0x00040000;}
#define TMP_SDA_READ()            GPIO_ReadInputDataBit(TMP_SDA_PORT, TMP_SDA_PIN)



//PWR_KEY
#define PWR_KEY_PORT              GPIOE
#define PWR_KEY_PIN               GPIO_Pin_1
#define PWR_KEY_MODE              GPIO_Mode_IN
#define PWR_KEY_OType             GPIO_OType_PP
#define PWR_KEY_PuPd              GPIO_PuPd_DOWN

#define PWR_KEY_CHK()             GPIO_ReadInputDataBit(PWR_KEY_PORT, PWR_KEY_PIN)

//PWR_CTL
#define PWR_CTL_PORT              GPIOE
#define PWR_CTL_PIN               GPIO_Pin_2
#define PWR_CTL_MODE              GPIO_Mode_OUT
#define PWR_CTL_OType             GPIO_OType_PP
#define PWR_CTL_PuPd              GPIO_PuPd_NOPULL

void Gpio_Config(void);

#endif

