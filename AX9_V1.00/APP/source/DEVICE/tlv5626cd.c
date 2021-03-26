#include "tlv5626cd.h"

#include "gouble.h"



void Spi_Dac_Config()
{
    Spi_config(SPI3, SPI_DataSize_16b, SPI_CPOL_High, SPI_CPHA_1Edge);
}

void DacHv_Tlv5626cd_ValueSet(uint8_t channel, uint8_t data)
{
    OS_ERR err;
    
    if(channel == TLV5626CD_A)
    {
        CTL_SPI3_CS2(0);
        SPI_WriteHalfWord(SPI3, TLV562CD_MODE);
        Delay_Nop(4000);
        CTL_SPI3_CS2(1);
        
        Delay_Nop(2000);
        
        CTL_SPI3_CS2(0);
        SPI_WriteHalfWord(SPI3, (0xC000 | (data << 4)));
        Delay_Nop(4000);
        CTL_SPI3_CS2(1);
    }
    if(channel == TLV5626CD_B)
    {
        CTL_SPI3_CS2(0);
        SPI_WriteHalfWord(SPI3, TLV562CD_MODE);
        Delay_Nop(4000);
        CTL_SPI3_CS2(1);
        
        Delay_Nop(2000);
        
        CTL_SPI3_CS2(0);
        SPI_WriteHalfWord(SPI3, (0x4000 | (data << 4)));
        Delay_Nop(4000);
        CTL_SPI3_CS2(1);
    }
}

void DacCw_Tlv5626cd_ValueSet(uint8_t channel, uint8_t data)
{ 
    if(channel == TLV5626CD_A)
    {
        CTL_SPI3_CS4(0);
        SPI_WriteHalfWord(SPI3, TLV562CD_MODE);
        Delay_Nop(4000);
        CTL_SPI3_CS4(1);
        
        Delay_Nop(2000);
        
        CTL_SPI3_CS4(0);
        SPI_WriteHalfWord(SPI3, (0xc000 | (data << 4)));
        Delay_Nop(4000);
        CTL_SPI3_CS4(1);
    }
    if(channel == TLV5626CD_B)
    {
        CTL_SPI3_CS4(0);
        SPI_WriteHalfWord(SPI3, TLV562CD_MODE);
        Delay_Nop(4000);
        CTL_SPI3_CS4(1);
        
        Delay_Nop(2000);
        
        CTL_SPI3_CS4(0);
        SPI_WriteHalfWord(SPI3, (0x4000 | (data << 4)));
        Delay_Nop(4000);
        CTL_SPI3_CS4(1);
    }
}

void DacCw_Tlv5626cd_Shutdown()
{
    CTL_SPI3_CS4(0);
    SPI_WriteHalfWord(SPI3, TLV562CD_SHUTDOWN);
    Delay_Nop(4000);
    CTL_SPI3_CS4(1);
}









