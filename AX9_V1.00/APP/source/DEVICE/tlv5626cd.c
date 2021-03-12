#include "tlv5626cd.h"

#include "gouble.h"

void Spi_Dac_Config()
{
    Spi_config(SPI3, SPI_DataSize_16b, SPI_CPOL_High, SPI_CPHA_2Edge);
}

void DacHv_Tlv5626cd_ValueSet(uint8_t channel, uint8_t data)
{
    if(channel == TLV5626CD_A)
    {
        SPI_CS_DACHV(0);
        SPI_WriteByte(SPI3, TLV562CD_MODE);
        SPI_WriteByte(SPI3, (0xc000 | (data << 4)));
        SPI_CS_DACHV(1);
    }
    if(channel == TLV5626CD_B)
    {
        SPI_CS_DACHV(0);
        SPI_WriteByte(SPI3, TLV562CD_MODE);
        SPI_WriteByte(SPI3, (0x4000 | (data << 4)));
        SPI_CS_DACHV(1);
    }
}

void DacCw_Tlv5626cd_ValueSet(uint8_t channel, uint8_t data)
{
    if(channel == TLV5626CD_A)
    {
        SPI_CS_DACCW(0);
        SPI_WriteByte(SPI3, TLV562CD_MODE);
        SPI_WriteByte(SPI3, (0xc000 | (data << 4)));
        SPI_CS_DACHV(1);
    }
    if(channel == TLV5626CD_B)
    {
        SPI_CS_DACCW(0);
        SPI_WriteByte(SPI3, TLV562CD_MODE);
        SPI_WriteByte(SPI3, (0x4000 | (data << 4)));
        SPI_CS_DACHV(1);
    }
}











