#include "bat.h"

extern System_MsgStruct SysMsg;

//void SMDAT_BAT1_OUT()
//{
//    GPIO_InitTypeDef GPIO_InitStruct;
//    
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
//    
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;				
//	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;		
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;				
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;			
//	GPIO_Init(GPIOF, &GPIO_InitStruct);	
//}

//void SMDAT_BAT1_IN()
//{
//    GPIO_InitTypeDef GPIO_InitStruct;
//    
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
//    
//    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;				
//	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;		
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;				
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;			
//	GPIO_Init(GPIOF, &GPIO_InitStruct);	
//}

//void I2c_Bat1_Start()
//{
//    SMDAT_BAT1_OUT();
//    
//    BAT1_SMBUS_C_1();
//    BAT1_SMBUS_D_1();
//    Delay_Nop(1800);
//    BAT1_SMBUS_D_0();
//    Delay_Nop(1800);
//    BAT1_SMBUS_C_0();
//    Delay_Nop(1800);
//}

//void I2c_Bat1_Stop()
//{
//    SMDAT_BAT1_OUT();
//    
//    BAT1_SMBUS_C_0();
//    BAT1_SMBUS_D_0();
//    Delay_Nop(1800);
//    BAT1_SMBUS_C_1();
//    Delay_Nop(1800);
//    BAT1_SMBUS_D_1();
//    Delay_Nop(1800);
//}

//void I2c_Bat1_SendByte(unsigned char data)
//{	
//	SMDAT_BAT1_OUT();

//	for(uint8_t mask=0x80; mask!=0; mask>>=1)
//	{
//		if((mask&data) == 0)
//		{
//			BAT1_SMBUS_D_0();
//		}
//		else
//		{
//			BAT1_SMBUS_D_1();
//		}
//		Delay_Nop(1800);
//		BAT1_SMBUS_C_1();
//		Delay_Nop(1800);
//		BAT1_SMBUS_C_0();
//        Delay_Nop(1800);
//	}
//}

//uint8_t I2c_Bat1_WaitAck()
//{
//	uint16_t startCnt = 2000;

//	SMDAT_BAT1_IN();
//    
//    Delay_Nop(1800);
//	
//	while(BAT1_SMBUS_D_READ())
//	{
//		if(--startCnt == 0)
//		{
//			return 1;
//		}
//	}
//	
//	BAT1_SMBUS_C_1();
//    Delay_Nop(1800);
//    BAT1_SMBUS_C_0();
//    Delay_Nop(1800);
//	return 0;
//}

//void I2c_Bat1_SendAck()
//{
//	SMDAT_BAT1_OUT();
//    
//	BAT1_SMBUS_C_0();
//	Delay_Nop(1800);
//	BAT1_SMBUS_D_0();
//	Delay_Nop(1800);
//	BAT1_SMBUS_C_1();
//	Delay_Nop(1800);
//	BAT1_SMBUS_C_0();
//	Delay_Nop(1800);
//}

//void I2c_Bat1_SendNack()
//{
//	SMDAT_BAT1_OUT();
//	BAT1_SMBUS_C_0();
//	Delay_Nop(1800);
//	BAT1_SMBUS_D_1();
//	Delay_Nop(1800);
//	BAT1_SMBUS_C_1();
//	Delay_Nop(1800);
//	BAT1_SMBUS_C_0();
//	Delay_Nop(1800);
//}

//uint8_t I2c_Bat1_ReadByte()
//{
//    uint8_t data;
//    
//    SMDAT_BAT1_IN();
//    BAT1_SMBUS_C_0();
//    
//    for(uint8_t mask=0x80; mask!=0; mask>>=1)
//    {
//        if(BAT1_SMBUS_D_READ()==0)
//        {
//            data &= ~mask;
//        }
//        else
//        {
//            data |= mask;
//        }
//        Delay_Nop(1800);
//        BAT1_SMBUS_C_1();
//        Delay_Nop(1800);
//        BAT1_SMBUS_C_0();
//        Delay_Nop(1800);
//    }
//    return data;
//}

//bool I2c_Bat1_ReadData(uint8_t id, uint8_t regaddr, uint8_t *buffer, uint8_t len)
//{
//    uint8_t i = 0;
//    
//    I2c_Bat1_Start();
//    I2c_Bat1_SendByte(id);
//    if(I2c_Bat1_WaitAck())
//    {
//        return FALSE;
//    }
//    I2c_Bat1_SendByte(regaddr);
//    if(I2c_Bat1_WaitAck())
//    {
//        return FALSE;
//    }
//    I2c_Bat1_Start();
//    I2c_Bat1_SendByte(id | 0x01);
//    if(I2c_Bat1_WaitAck())
//    {
//        return FALSE;
//    }
//    do
//    {
//        Delay_Nop(1800);
//        *buffer++ = I2c_Bat1_ReadByte();
//        if(++i == len)
//        {
//            I2c_Bat1_SendNack();
//        }
//        else
//        {
//            I2c_Bat1_SendAck();
//        }
//    }while(i!=len);
//    Delay_Nop(1800);
//    I2c_Bat1_Stop();
//    
//    return TRUE;
//}

//void Bat1_PowerRead()
//{
//    uint8_t buffer[3] = {0, 0 , 0};
//    
//    if(I2c_Bat1_ReadData(BAT_ADDR, BAT_PWR_CMD, buffer, 3) == TRUE)
//    {
//        if(buffer[0] <= 100)
//        {
//            SysMsg.PwrInfo.Bat1_Power = buffer[0];
//        }
//    }
//}


























void SMDAT_BAT1_OUT()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;				
	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;		
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;				
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;			
	GPIO_Init(GPIOF, &GPIO_InitStruct);	
}

void SMDAT_BAT1_IN()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;				
	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;		
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;				
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;			
	GPIO_Init(GPIOF, &GPIO_InitStruct);	
}

void I2c_Bat1_Start()
{
    SMDAT_BAT1_OUT();
    
    BAT1_SMBUS_C_1();
    BAT1_SMBUS_D_1();
    delay_us_os(5);
    BAT1_SMBUS_D_0();
    delay_us_os(5);
    BAT1_SMBUS_C_0();
    delay_us_os(5);
}

void I2c_Bat1_Stop()
{
    SMDAT_BAT1_OUT();
    
    BAT1_SMBUS_C_0();
    BAT1_SMBUS_D_0();
    delay_us_os(5);
    BAT1_SMBUS_C_1();
    delay_us_os(5);
    BAT1_SMBUS_D_1();
    delay_us_os(5);
}

void I2c_Bat1_SendByte(unsigned char data)
{	
	SMDAT_BAT1_OUT();
    delay_us_os(5);
	for(uint8_t mask=0x80; mask!=0; mask>>=1)
	{
		if((mask&data) == 0)
		{
			BAT1_SMBUS_D_0();
		}
		else
		{
			BAT1_SMBUS_D_1();
		}
		delay_us_os(5);
		BAT1_SMBUS_C_1();
		delay_us_os(5);
		BAT1_SMBUS_C_0();
        delay_us_os(5);
	}
}

uint8_t I2c_Bat1_WaitAck()
{
	uint16_t startCnt = 2000;

	SMDAT_BAT1_IN();
    
    delay_us_os(5);
	while(BAT1_SMBUS_D_READ())
	{
		if(--startCnt == 0)
		{
			return 1;
		}
	}
	
	BAT1_SMBUS_C_1();
    delay_us_os(5);
    BAT1_SMBUS_C_0();
    delay_us_os(5);
	return 0;
}

void I2c_Bat1_SendAck()
{
	SMDAT_BAT1_OUT();
    
	BAT1_SMBUS_C_0();
	delay_us_os(5);
	BAT1_SMBUS_D_0();
	delay_us_os(5);
	BAT1_SMBUS_C_1();
	delay_us_os(5);
	BAT1_SMBUS_C_0();
	delay_us_os(5);
}

void I2c_Bat1_SendNack()
{
	SMDAT_BAT1_OUT();
	BAT1_SMBUS_C_0();
	delay_us_os(5);
	BAT1_SMBUS_D_1();
	delay_us_os(5);
	BAT1_SMBUS_C_1();
	delay_us_os(5);
	BAT1_SMBUS_C_0();
	delay_us_os(5);
}

uint8_t I2c_Bat1_ReadByte()
{
    uint8_t data;
    
    SMDAT_BAT1_IN();
    BAT1_SMBUS_C_0();
    
    for(uint8_t mask=0x80; mask!=0; mask>>=1)
    {
        if(BAT1_SMBUS_D_READ()==0)
        {
            data &= ~mask;
        }
        else
        {
            data |= mask;
        }
        delay_us_os(5);
        BAT1_SMBUS_C_1();
        delay_us_os(5);
        BAT1_SMBUS_C_0();
        delay_us_os(5);
    }
    return data;
}

bool I2c_Bat1_ReadData(uint8_t id, uint8_t regaddr, uint8_t *buffer, uint8_t len)
{
    uint8_t i = 0;
    
    I2c_Bat1_Start();
    I2c_Bat1_SendByte(id);
    if(I2c_Bat1_WaitAck())
    {
        return FALSE;
    }
    I2c_Bat1_SendByte(regaddr);
    if(I2c_Bat1_WaitAck())
    {
        return FALSE;
    }
    I2c_Bat1_Start();
    I2c_Bat1_SendByte(id | 0x01);
    if(I2c_Bat1_WaitAck())
    {
        return FALSE;
    }
    do
    {
        delay_us_os(50);
        *buffer++ = I2c_Bat1_ReadByte();
        if(++i == len)
        {
            I2c_Bat1_SendNack();
        }
        else
        {
            I2c_Bat1_SendAck();
        }
    }while(i!=len);
    delay_us_os(5);
    I2c_Bat1_Stop();
    
    return TRUE;
}

void Bat1_PowerRead()
{
    uint8_t buffer[3] = {0, 0 , 0};
    
    if(SysMsg.PwrInfo.Bat1_Insert == TRUE)
    {
        if(I2c_Bat1_ReadData(BAT_ADDR, BAT_PWR_CMD, buffer, 3) == TRUE)
        {
            if(buffer[0] <= 100)
            {
                SysMsg.PwrInfo.Bat1_Power = buffer[0];
            }
        }
    }
    else
    {
        SysMsg.PwrInfo.Bat1_Power = 0;
    }
}


