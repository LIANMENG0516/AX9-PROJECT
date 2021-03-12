#ifndef __TLV5626CD_H_
#define __TLV5626CD_H_

#include "stm32f4xx.h"

#define SPI_CS_DACHV(x)     CTL_SPI3_PIN_CS2(x)
#define SPI_CS_DACCW(x)     CTL_SPI3_PIN_CS4(x)

#define TLV5626CD_A       1
#define TLV5626CD_B       2

#define TLV562CD_MODE     0xd002     //Set DAC output, select fast mode, select internal reference at 2.048 V 

#define TLV5626CD_1_CS(x) CTL_SPI3_PIN_CS2(x) 
#define TLV5626CD_2_CS(x) CTL_SPI3_PIN_CS4(x)

void Spi_Dac_Config(void);
void DacHv_Tlv5626cd_ValueSet(uint8_t channel, uint8_t data);
void DacCw_Tlv5626cd_ValueSet(uint8_t channel, uint8_t data);


#endif

