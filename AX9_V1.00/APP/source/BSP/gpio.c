#include "gpio.h"

void Gpio_Config()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE, ENABLE);                                                                                    
	
	//LED
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure);   
    
    //DEBUG_COM
    GPIO_PinAFConfig(DEBUG_COM_PORT_TX, GPIO_PinSource0, GPIO_AF_UART4);
    GPIO_PinAFConfig(DEBUG_COM_PORT_RX, GPIO_PinSource1, GPIO_AF_UART4);
    
	GPIO_InitStructure.GPIO_Pin     = DEBUG_COM_PIN_TX;
	GPIO_InitStructure.GPIO_Mode    = DEBUG_COM_PIN_TX_MODE;
    GPIO_InitStructure.GPIO_OType   = DEBUG_COM_PIN_TX_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = DEBUG_COM_PIN_TX_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_COM_PORT_TX, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin     = DEBUG_COM_PIN_RX;
	GPIO_InitStructure.GPIO_Mode    = DEBUG_COM_PIN_RX_MODE;
    GPIO_InitStructure.GPIO_OType   = DEBUG_COM_PIN_RX_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = DEBUG_COM_PIN_RX_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_COM_PORT_RX, &GPIO_InitStructure);
    
    //COMM_COM
    GPIO_PinAFConfig(COMM_COM_PORT_TX, GPIO_PinSource5, GPIO_AF_USART2);
    GPIO_PinAFConfig(COMM_COM_PORT_RX, GPIO_PinSource6, GPIO_AF_USART2);
    
	GPIO_InitStructure.GPIO_Pin     = COMM_COM_PIN_TX;
	GPIO_InitStructure.GPIO_Mode    = COMM_COM_PIN_TX_MODE;
    GPIO_InitStructure.GPIO_OType   = COMM_COM_PIN_TX_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = COMM_COM_PIN_TX_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(COMM_COM_PORT_TX, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin     = COMM_COM_PIN_RX;
	GPIO_InitStructure.GPIO_Mode    = COMM_COM_PIN_RX_MODE;
    GPIO_InitStructure.GPIO_OType   = COMM_COM_PIN_RX_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = COMM_COM_PIN_RX_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(COMM_COM_PORT_RX, &GPIO_InitStructure);

    //SPI3
    GPIO_PinAFConfig(SPI3_PORT_SCK, GPIO_PinSource10, GPIO_AF_SPI3);
    GPIO_PinAFConfig(SPI3_PORT_MOSI, GPIO_PinSource11, GPIO_AF_SPI3);
    GPIO_PinAFConfig(SPI3_PORT_MISO, GPIO_PinSource12, GPIO_AF_SPI3);
    
    GPIO_InitStructure.GPIO_Pin     = SPI3_PIN_SCK;
	GPIO_InitStructure.GPIO_Mode    = SPI3_PIN_SCK_MODE;
    GPIO_InitStructure.GPIO_OType   = SPI3_PIN_SCK_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = SPI3_PIN_SCK_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(SPI3_PORT_SCK, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin     = SPI3_PIN_MOSI;
	GPIO_InitStructure.GPIO_Mode    = SPI3_PIN_MOSI_MODE;
    GPIO_InitStructure.GPIO_OType   = SPI3_PIN_MOSI_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = SPI3_PIN_MOSI_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(SPI3_PORT_MOSI, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin     = SPI3_PIN_MISO;
	GPIO_InitStructure.GPIO_Mode    = SPI3_PIN_MISO_MODE;
    GPIO_InitStructure.GPIO_OType   = SPI3_PIN_MISO_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = SPI3_PIN_MISO_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(SPI3_PORT_MISO, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin     = SPI3_PIN_CS2 | SPI3_PIN_CS3 | SPI3_PIN_CS4;
	GPIO_InitStructure.GPIO_Mode    = SPI3_PIN_CS_MODE;
    GPIO_InitStructure.GPIO_OType   = SPI3_PIN_CS_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = SPI3_PIN_CS_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(SPI3_PORT_CS, &GPIO_InitStructure);
    
    //DAC
    GPIO_InitStructure.GPIO_Pin     = DACOUT1_PIN;
	GPIO_InitStructure.GPIO_Mode    = DACOUT1_MODE;
    GPIO_InitStructure.GPIO_OType   = DACOUT1_OType;
    GPIO_InitStructure.GPIO_PuPd    = DACOUT1_PuPd;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(DACOUT1_PORT, &GPIO_InitStructure);
    
    
    GPIO_InitStructure.GPIO_Pin     = DACOUT2_PIN;
	GPIO_InitStructure.GPIO_Mode    = DACOUT2_MODE;
    GPIO_InitStructure.GPIO_OType   = DACOUT2_OType;
    GPIO_InitStructure.GPIO_PuPd    = DACOUT2_PuPd;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(DACOUT2_PORT, &GPIO_InitStructure);
    
    //ADC-VPP1
    GPIO_InitStructure.GPIO_Pin     = T_VPP1_PIN;
	GPIO_InitStructure.GPIO_Mode    = T_VPP1_PIN_MODE;
    GPIO_InitStructure.GPIO_OType   = T_VPP1_PIN_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = T_VPP1_PIN_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(T_VPP1_PORT, &GPIO_InitStructure);
    
    //ADC-VNN1
    GPIO_InitStructure.GPIO_Pin     = T_VNN1_PIN;
	GPIO_InitStructure.GPIO_Mode    = T_VNN1_PIN_MODE;
    GPIO_InitStructure.GPIO_OType   = T_VNN1_PIN_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = T_VNN1_PIN_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(T_VNN1_PORT, &GPIO_InitStructure);
    
    //ADC-VPP2
    GPIO_InitStructure.GPIO_Pin     = T_VPP2_PIN;
	GPIO_InitStructure.GPIO_Mode    = T_VPP2_PIN_MODE;
    GPIO_InitStructure.GPIO_OType   = T_VPP2_PIN_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = T_VPP2_PIN_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(T_VPP2_PORT, &GPIO_InitStructure);
    
    //ADC-VNN2
    GPIO_InitStructure.GPIO_Pin     = T_VNN2_PIN;
	GPIO_InitStructure.GPIO_Mode    = T_VNN2_PIN_MODE;
    GPIO_InitStructure.GPIO_OType   = T_VNN2_PIN_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = T_VNN2_PIN_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(T_VNN2_PORT, &GPIO_InitStructure);
    
    //ADC-IAPD
    GPIO_InitStructure.GPIO_Pin     = T_IAPD_PIN;
	GPIO_InitStructure.GPIO_Mode    = T_IAPD_PIN_MODE;
    GPIO_InitStructure.GPIO_OType   = T_IAPD_PIN_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = T_IAPD_PIN_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(T_IAPD_PORT, &GPIO_InitStructure);
    
    //ADC-A2V25 
    GPIO_InitStructure.GPIO_Pin     = T_A2V25_PIN;
	GPIO_InitStructure.GPIO_Mode    = T_A2V25_PIN_MODE;
    GPIO_InitStructure.GPIO_OType   = T_A2V25_PIN_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = T_A2V25_PIN_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(T_A2V25_PORT, &GPIO_InitStructure);
    
    //ADC-A3V75   
    GPIO_InitStructure.GPIO_Pin     = T_A3V75_PIN;
	GPIO_InitStructure.GPIO_Mode    = T_A3V75_PIN_MODE;
    GPIO_InitStructure.GPIO_OType   = T_A3V75_PIN_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = T_A3V75_PIN_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(T_A3V75_PORT, &GPIO_InitStructure);
    
    //ADC-AP5V5_1   
    GPIO_InitStructure.GPIO_Pin     = T_AP5V5_1_PIN;
	GPIO_InitStructure.GPIO_Mode    = T_AP5V5_1_PIN_MODE;
    GPIO_InitStructure.GPIO_OType   = T_AP5V5_1_PIN_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = T_AP5V5_1_PIN_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(T_AP5V5_1_PORT, &GPIO_InitStructure);
    
    //ADC-AP12V   
    GPIO_InitStructure.GPIO_Pin     = T_AP12V_PIN;
	GPIO_InitStructure.GPIO_Mode    = T_AP12V_PIN_MODE;
    GPIO_InitStructure.GPIO_OType   = T_AP12V_PIN_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = T_AP12V_PIN_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(T_AP12V_PORT, &GPIO_InitStructure);
    
    //ADC-AN5V5  
    GPIO_InitStructure.GPIO_Pin     = T_AN5V5_PIN;
	GPIO_InitStructure.GPIO_Mode    = T_AN5V5_PIN_MODE;
    GPIO_InitStructure.GPIO_OType   = T_AN5V5_PIN_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = T_AN5V5_PIN_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(T_AN5V5_PORT, &GPIO_InitStructure);
    
    //ADC-AN12V  
    GPIO_InitStructure.GPIO_Pin     = T_AN12V_PIN;
	GPIO_InitStructure.GPIO_Mode    = T_AN12V_PIN_MODE;
    GPIO_InitStructure.GPIO_OType   = T_AN12V_PIN_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = T_AN12V_PIN_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(T_AN12V_PORT, &GPIO_InitStructure);
    
    //ADC-AN5V5  
    GPIO_InitStructure.GPIO_Pin     = T_D0V95_PIN;
	GPIO_InitStructure.GPIO_Mode    = T_D0V95_PIN_MODE;
    GPIO_InitStructure.GPIO_OType   = T_D0V95_PIN_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = T_D0V95_PIN_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(T_D0V95_PORT, &GPIO_InitStructure);
    
    //ADC-AN12V  
    GPIO_InitStructure.GPIO_Pin     = T_D1V45_PIN;
	GPIO_InitStructure.GPIO_Mode    = T_D1V45_PIN_MODE;
    GPIO_InitStructure.GPIO_OType   = T_D1V45_PIN_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = T_D1V45_PIN_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(T_D1V45_PORT, &GPIO_InitStructure);
    
    //ADC-AN12V  
    GPIO_InitStructure.GPIO_Pin     = T_AP5V5_2_PIN;
	GPIO_InitStructure.GPIO_Mode    = T_AP5V5_2_PIN_MODE;
    GPIO_InitStructure.GPIO_OType   = T_AP5V5_2_PIN_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = T_AP5V5_2_PIN_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(T_AP5V5_2_PORT, &GPIO_InitStructure);
    
    //ADC-D5V  
    GPIO_InitStructure.GPIO_Pin     = T_D5V_PIN;
	GPIO_InitStructure.GPIO_Mode    = T_D5V_PIN_MODE;
    GPIO_InitStructure.GPIO_OType   = T_D5V_PIN_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = T_D5V_PIN_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(T_D5V_PORT, &GPIO_InitStructure);
    
    //EMC_2305
    GPIO_InitStructure.GPIO_Pin     = EMC_SCK_PIN;
	GPIO_InitStructure.GPIO_Mode    = EMC_SCK_PIN_MODE;
    GPIO_InitStructure.GPIO_OType   = EMC_SCK_PIN_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = EMC_SCK_PIN_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(EMC_SCK_PORT, &GPIO_InitStructure);

    //EMC_2305
    GPIO_InitStructure.GPIO_Pin     = EMC_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode    = EMC_SDA_MODE;
    GPIO_InitStructure.GPIO_OType   = EMC_SDA_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = EMC_SDA_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(EMC_SDA_PORT, &GPIO_InitStructure);

    //TMP468_2305
    GPIO_InitStructure.GPIO_Pin     = TMP_SCK_PIN;
	GPIO_InitStructure.GPIO_Mode    = TMP_SCK_PIN_MODE;
    GPIO_InitStructure.GPIO_OType   = TMP_SCK_PIN_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = TMP_SCK_PIN_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(TMP_SCK_PORT, &GPIO_InitStructure);

    //TMP468_2305
    GPIO_InitStructure.GPIO_Pin     = TMP_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode    = TMP_SDA_MODE;
    GPIO_InitStructure.GPIO_OType   = TMP_SDA_OTYPE;
    GPIO_InitStructure.GPIO_PuPd    = TMP_SDA_PUPD;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(TMP_SDA_PORT, &GPIO_InitStructure);

    //PWR_KEY
    GPIO_InitStructure.GPIO_Pin     = PWR_KEY_PIN;
	GPIO_InitStructure.GPIO_Mode    = PWR_KEY_MODE;
    GPIO_InitStructure.GPIO_OType   = PWR_KEY_OType;
    GPIO_InitStructure.GPIO_PuPd    = PWR_KEY_PuPd;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(PWR_KEY_PORT, &GPIO_InitStructure);

    //PWR_CTL
    GPIO_InitStructure.GPIO_Pin     = PWR_CTL_PIN;
	GPIO_InitStructure.GPIO_Mode    = PWR_CTL_MODE;
    GPIO_InitStructure.GPIO_OType   = PWR_CTL_OType;
    GPIO_InitStructure.GPIO_PuPd    = PWR_CTL_PuPd;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_Init(PWR_CTL_PORT, &GPIO_InitStructure);


    
    
    
}























