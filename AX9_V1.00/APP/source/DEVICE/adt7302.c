#include "adt7302.h"

#include "gouble.h"

uint8_t Tempature_Read_Fpga()
{
    uint8_t TempMsb, TempLsb, TempCode;
    
    uint16_t TempVal;
    
    
    CTL_SPI3_PIN_CS3(0);
    
    SPI_ReadWriteByte(SPI3, 0);
    TempMsb = SPI_ReadWriteByte(SPI3, 0);
    
    SPI_ReadWriteByte(SPI3, 0);
    TempLsb = SPI_ReadWriteByte(SPI3, 0);
    
    CTL_SPI3_PIN_CS3(1);
    
    TempCode = (TempMsb << 8) | TempLsb;
    
    if((0x2000 & TempCode) == 0x2000)
    {
        TempVal = (TempCode - 16384) / 32;
    }
    else
    {
        TempVal = TempCode / 32;
    }

    return TempVal;
}




























