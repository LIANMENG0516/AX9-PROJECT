#ifndef __GPIO_H_
#define __GPIO_H_

#include "stm32f4xx.h"

//USART4_DEBUG_COM
#define DEBUG_COM_TX_PORT         GPIOA
#define DEBUG_COM_TX_PIN          GPIO_Pin_0

#define DEBUG_COM_RX_PORT         GPIOA
#define DEBUG_COM_RX_PIN          GPIO_Pin_1

//T_AP5V5_2_ADC
#define T_AP5V5_2_PORT            GPIOA
#define T_AP5V5_2_PIN             GPIO_Pin_2

//T_D5V_ADC
#define T_D5V_PORT                GPIOA
#define T_D5V_PIN                 GPIO_Pin_3
#define T_D5V_PIN_MODE            GPIO_Mode_AN

//HVADJ1_DAC
#define HVADJ1_PORT               GPIOA
#define HVADJ1_PIN                GPIO_Pin_4

//HVADJ3_DAC
#define HVADJ3_PORT               GPIOA
#define HVADJ3_PIN                GPIO_Pin_5

//BAT2_SMBUS_C
#define BAT2_SMBUS_C_PORT         GPIOA
#define BAT2_SMBUS_C_PIN          GPIO_Pin_8

//SPI3_CS3   
#define SPI3_CS3_PORT             GPIOB
#define SPI3_CS3_PIN              GPIO_Pin_0
#define CTL_SPI3_CS3(x)           x ? GPIO_SetBits(SPI3_PORT_CS, SPI3_PIN_CS3) : GPIO_ResetBits(SPI3_PORT_CS, SPI3_PIN_CS3)

//SMCLK_2305
#define SMCLK_2305_PORT           GPIOB
#define SMCLK_2305_PIN            GPIO_Pin_6

//SMDAT_2305
#define SMDAT_2305_PORT           GPIOB
#define SMDAT_2305_PIN            GPIO_Pin_7
#define SMDAT_2305_1()            GPIO_SetBits(SMDAT_2305_PORT, SMDAT_2305_PIN)
#define SMDAT_2305_0()            GPIO_ResetBits(SMDAT_2305_PORT, SMDAT_2305_PIN)
#define SMDAT_2305_IN()           {GPIOB->MODER = GPIOB->MODER & 0xFFFF3FFF;}
#define SMDAT_2305_OUT()          {GPIOB->MODER = GPIOB->MODER & 0xFFFF7FFF; GPIOB->MODER = GPIOB->MODER | 0x00004000;}
#define SMDAT_2305_READ()         GPIO_ReadInputDataBit(SMDAT_2305_PORT, SMDAT_2305_PIN)

//IIC1_SCK
#define IIC1_SCK_PORT             GPIOB      
#define IIC1_SCK_PIN              GPIO_Pin_8    
#define IIC1_SCK_1()              GPIO_SetBits(IIC1_SCK_PORT, IIC1_SCK_PIN)
#define IIC1_SCK_0()              GPIO_ResetBits(IIC1_SCK_PORT, IIC1_SCK_PIN)

//IIC1_SDA
#define IIC1_SDA_PORT             GPIOB
#define IIC1_SDA_PIN              GPIO_Pin_9 
#define IIC1_SDA_1()              GPIO_SetBits(IIC1_SDA_PORT, IIC1_SDA_PIN)
#define IIC1_SDA_0()              GPIO_ResetBits(IIC1_SDA_PORT, IIC1_SDA_PIN)
#define IIC1_SDA_IN()             {GPIOB->MODER = GPIOB->MODER & 0xFFF3FFFF;}
#define IIC1_SDA_OUT()            {GPIOB->MODER = GPIOB->MODER & 0xFFF7FFFF; GPIOB->MODER = GPIOB->MODER | 0x00040000;}
#define IIC1_SDA_READ()           GPIO_ReadInputDataBit(IIC1_SDA_PORT, IIC1_SDA_PIN)

//SPI3_CS2   
#define SPI3_CS2_PORT             GPIOB
#define SPI3_CS2_PIN              GPIO_Pin_13
#define CTL_SPI3_CS2(x)           x ? GPIO_SetBits(SPI3_CS2_PORT, SPI3_CS2_PIN) : GPIO_ResetBits(SPI3_CS2_PORT, SPI3_CS2_PIN)

//SPI3_CS4   
#define SPI3_CS4_PORT             GPIOB
#define SPI3_CS4_PIN              GPIO_Pin_14
#define CTL_SPI3_CS4(x)           x ? GPIO_SetBits(SPI3_CS4_PORT, SPI3_CS4_PIN) : GPIO_ResetBits(SPI3_CS4_PORT, SPI3_CS4_PIN)

//T_VPP1_ADC    
#define T_VPP1_PORT               GPIOC
#define T_VPP1_PIN                GPIO_Pin_0

//T_VNN1_ADC    
#define T_VNN1_PORT               GPIOC
#define T_VNN1_PIN                GPIO_Pin_1

//T_VPP2_ADC    
#define T_VPP2_PORT               GPIOC
#define T_VPP2_PIN                GPIO_Pin_2

//T_VNN2_ADC    
#define T_VNN2_PORT               GPIOC
#define T_VNN2_PIN                GPIO_Pin_3

//T_IAPD_ADC    
#define T_IAPD_PORT               GPIOC
#define T_IAPD_PIN                GPIO_Pin_5

//BAT2_SMBUS_D   
#define BAT2_SMBUS_D_PORT         GPIOC
#define BAT2_SMBUS_D_PIN          GPIO_Pin_9

//SPI3_SCK
#define SPI3_PORT_SCK             GPIOC
#define SPI3_PIN_SCK              GPIO_Pin_10

//SPI3_MOSI
#define SPI3_PORT_MOSI            GPIOC
#define SPI3_PIN_MOSI             GPIO_Pin_11

//SPI3_MISO
#define SPI3_PORT_MISO            GPIOC  
#define SPI3_PIN_MISO             GPIO_Pin_12

//C_P5V5_1
#define C_P5V5_1_PORT             GPIOC
#define C_P5V5_1_PIN              GPIO_Pin_13

//C_P5V5_2
#define C_P5V5_2_PORT             GPIOC
#define C_P5V5_2_PIN              GPIO_Pin_14

//LIDIN
#define LIDIN_PORT                GPIOC
#define LIDIN_PIN                 GPIO_Pin_15

//CHARGE_EN
#define CHARGE_EN_PORT            GPIOD
#define CHARGE_EN_PIN             GPIO_Pin_1

//C_P2V25
#define C_P2V25_PORT              GPIOD
#define C_P2V25_PIN               GPIO_Pin_2

//C_D0V95
#define C_D0V95_PORT              GPIOD
#define C_D0V95_PIN               GPIO_Pin_3

//C_D1V45
#define C_D1V45_PORT              GPIOD
#define C_D1V45_PIN               GPIO_Pin_4

//USART2_COMM_COM
#define COMM_COM_TX_PORT          GPIOD
#define COMM_COM_TX_PIN           GPIO_Pin_5

#define COMM_COM_RX_PORT          GPIOD
#define COMM_COM_RX_PIN           GPIO_Pin_6

//C_P12V
#define C_P12V_PORT               GPIOD
#define C_P12V_PIN                GPIO_Pin_7

//C_P3V75
#define C_P3V75_PORT              GPIOD
#define C_P3V75_PIN               GPIO_Pin_8

//C_N12V_5V5
#define C_N12V_5V5_PORT           GPIOD
#define C_N12V_5V5_PIN            GPIO_Pin_9

//PD10
#define PD10_PORT                 GPIOD
#define PD10_PIN                  GPIO_Pin_10

//CHARGE_CTL
#define CHARGE_CTL_PORT           GPIOD
#define CHARGE_CTL_PIN            GPIO_Pin_11

//C_VDD_P5V
#define C_VDD_P5V_PORT            GPIOD
#define C_VDD_P5V_PIN             GPIO_Pin_12

//PBUS_ON
#define PBUS_ON_PORT              GPIOD
#define PBUS_ON_PIN               GPIO_Pin_13

//SV_CTL_IN
#define SV_CTL_IN_PORT            GPIOD
#define SV_CTL_IN_PIN             GPIO_Pin_14

//V_PROE1
#define V_PROE1_PORT              GPIOD
#define V_PROE1_PIN               GPIO_Pin_15

//V_PROE2
#define V_PROE2_PORT              GPIOE
#define V_PROE2_PIN               GPIO_Pin_0

//PWR_KEY
#define PWR_KEY_PORT              GPIOE
#define PWR_KEY_PIN               GPIO_Pin_1
#define PWR_KEY_CHK()             GPIO_ReadInputDataBit(PWR_KEY_PORT, PWR_KEY_PIN)

//PWR_CTL
#define PWR_CTL_PORT              GPIOE
#define PWR_CTL_PIN               GPIO_Pin_2

//BAT_STAT1
#define BAT_STAT1_PORT            GPIOE
#define BAT_STAT1_PIN             GPIO_Pin_3

//BAT_STAT2
#define BAT_STAT2_PORT            GPIOE
#define BAT_STAT2_PIN             GPIO_Pin_4

//SYS_LED
#define SYS_LED_PORT              GPIOE
#define SYS_LED_PIN               GPIO_Pin_8

//AC_OK
#define AC_OK_PORT                GPIOE
#define AC_OK_PIN                 GPIO_Pin_9

//PWR_BTN_COM
#define PWR_BTN_COM_PORT          GPIOE
#define PWR_BTN_COM_PIN           GPIO_Pin_10

//US_PWR_ID
#define US_PWR_ID_PORT            GPIOE
#define US_PWR_ID_PIN             GPIO_Pin_11

//SUS_S4
#define SUS_S4_PORT               GPIOE
#define SUS_S4_PIN                GPIO_Pin_12

//SUS_S3
#define SUS_S3_PORT               GPIOE
#define SUS_S3_PIN                GPIO_Pin_13

//BAT1_SMBUS_C 
#define BAT1_SMBUS_C_PORT         GPIOF
#define BAT1_SMBUS_C_PIN          GPIO_Pin_1

//BAT1_SMBUS_D
#define BAT1_SMBUS_D_PORT         GPIOF
#define BAT1_SMBUS_D_PIN          GPIO_Pin_0

//PWR_OK_COM
#define PWR_OK_COM_PORT           GPIOF
#define PWR_OK_COM_PIN            GPIO_Pin_2

//T_A2V25_ADC   
#define T_A2V25_PORT              GPIOF
#define T_A2V25_PIN               GPIO_Pin_3

//T_A3V75_ADC   
#define T_A3V75_PORT              GPIOF
#define T_A3V75_PIN               GPIO_Pin_4

//T_AP5V5_1_ADC   
#define T_AP5V5_1_PORT            GPIOF
#define T_AP5V5_1_PIN             GPIO_Pin_5

//T_AP12V_ADC   
#define T_AP12V_PORT              GPIOF
#define T_AP12V_PIN               GPIO_Pin_6

//T_AN5V5_ADC   
#define T_AN5V5_PORT              GPIOF
#define T_AN5V5_PIN               GPIO_Pin_7
  
//T_AN12V_ADC   
#define T_AN12V_PORT              GPIOF
#define T_AN12V_PIN               GPIO_Pin_8

//T_D0V95_ADC   
#define T_D0V95_PORT              GPIOF
#define T_D0V95_PIN               GPIO_Pin_9

//T_D1V45_ADC
#define T_D1V45_PORT              GPIOF
#define T_D1V45_PIN               GPIO_Pin_10

//BAT1_C_SHIFT
#define BAT1_C_SHIFT_PORT         GPIOG
#define BAT1_C_SHIFT_PIN          GPIO_Pin_0

//BAT2_C_SHIFT
#define BAT2_C_SHIFT_PORT         GPIOG
#define BAT2_C_SHIFT_PIN          GPIO_Pin_1

//CHARGE_LED_O
#define CHARGE_LED_O_PORT         GPIOG
#define CHARGE_LED_O_PIN          GPIO_Pin_2

//CHARGE_LED_G
#define CHARGE_LED_G_PORT         GPIOG
#define CHARGE_LED_G_PIN          GPIO_Pin_3

//SLEEP_LED_C
#define SLEEP_LED_C_PORT          GPIOG
#define SLEEP_LED_C_PIN           GPIO_Pin_4

//C_VNN2_VPP2
#define C_VNN2_VPP2_PORT          GPIOG
#define C_VNN2_VPP2_PIN           GPIO_Pin_14

//C_VNN1_VPP1
#define C_VNN1_VPP1_PORT          GPIOG
#define C_VNN1_VPP1_PIN           GPIO_Pin_15

void Gpio_Config(void);

#endif

