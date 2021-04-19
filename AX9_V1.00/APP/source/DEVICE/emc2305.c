#include "emc2305.h"

#include "gouble.h"


void SMDAT_2305_OUT()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;				
	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;		
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;				
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;			
	GPIO_Init(GPIOB, &GPIO_InitStruct);	
}

void SMDAT_2305_IN()
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;				
	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;		
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;				
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;			
	GPIO_Init(GPIOB, &GPIO_InitStruct);	
}

void I2c_Emc_Start()
{
	SMDAT_2305_OUT();
	SMCLK_2305_1();
    Delay_Nop(10);
	SMDAT_2305_1();
	Delay_Nop(10);
	SMDAT_2305_0();
	Delay_Nop(10);
	SMCLK_2305_0();
	Delay_Nop(10);
}

void I2c_Emc_Stop()
{
	SMDAT_2305_OUT();
	SMCLK_2305_0();
	SMDAT_2305_0();
	Delay_Nop(10);
	SMCLK_2305_1();
	Delay_Nop(10);
	SMDAT_2305_1();
	Delay_Nop(10);
}

void I2c_Emc_SendByte(unsigned char data)
{	
	SMDAT_2305_OUT();

	for(uint8_t mask=0x80; mask!=0; mask>>=1)
	{
		if((mask&data) == 0)
		{
			SMDAT_2305_0();
		}
		else
		{
			SMDAT_2305_1();
		}
		Delay_Nop(10);
		SMCLK_2305_1();
		Delay_Nop(10);
		SMCLK_2305_0();
        Delay_Nop(10);
	}
}

uint8_t I2c_Emc_ReadByte()
{
	uint8_t data;
	
	SMDAT_2305_IN();
	SMCLK_2305_0();

	for(uint8_t mask=0x80; mask!=0; mask>>=1)
	{
		if(SMDAT_2305_READ()==0)
		{
			data &= ~mask;
		}
		else
		{
			data |= mask;
		}
		Delay_Nop(10);
		SMCLK_2305_1();
		Delay_Nop(10);
		SMCLK_2305_0();
		Delay_Nop(10);
	}
	return data;
}

uint8_t I2c_Emc_WaitAck()
{
	uint16_t startCnt = 2000;

	SMDAT_2305_IN();
    
    Delay_Nop(5);
	
	while(SMDAT_2305_READ())
	{
		if(--startCnt == 0)
		{
			return 1;
		}
	}
	
	SMCLK_2305_1();
	Delay_Nop(10);    
	SMCLK_2305_0();
	Delay_Nop(10);
	return 0;
}

void I2c_Emc_SendAck()
{
	SMDAT_2305_OUT();
    
	SMCLK_2305_0();
	Delay_Nop(10);
	SMDAT_2305_0();
	Delay_Nop(10);
	SMCLK_2305_1();
	Delay_Nop(10);
	SMCLK_2305_0();
	Delay_Nop(10);
}

void I2c_Emc_SendNack()
{
	SMDAT_2305_OUT();
	SMCLK_2305_0();
	Delay_Nop(10);
	SMDAT_2305_1();
	Delay_Nop(10);
	SMCLK_2305_1();
	Delay_Nop(10);
	SMCLK_2305_0();
	Delay_Nop(10);
}

void Emc2305_WriteByte(uint8_t id, uint8_t addr, uint8_t val)
{    
    I2c_Emc_Start();    
    I2c_Emc_SendByte((id << 1) & 0xFE);     //发送器件地址, 写地址
    if(I2c_Emc_WaitAck())
    {
        DEBUG_PRINTF(DEBUG_STRING, "IIC ERROR \r\n");
    }
    I2c_Emc_SendByte(addr);
    if(I2c_Emc_WaitAck())
    {
        DEBUG_PRINTF(DEBUG_STRING, "IIC ERROR \r\n");
    }
    I2c_Emc_SendByte(val);
    if(I2c_Emc_WaitAck())
    {
        DEBUG_PRINTF(DEBUG_STRING, "IIC ERROR \r\n");
    }
    I2c_Emc_Stop();
}

void Emc2305_WriteData(uint8_t id, uint8_t addr, uint8_t *buffer, uint8_t len)
{
    I2c_Emc_Start();
    I2c_Emc_SendByte((id << 1) & 0xFE);     //发送器件地址, 写地址
    if(I2c_Emc_WaitAck())
    {
        DEBUG_PRINTF(DEBUG_STRING, "IIC ERROR \r\n");
    }
    I2c_Emc_SendByte(addr);
    if(I2c_Emc_WaitAck())
    {
        DEBUG_PRINTF(DEBUG_STRING, "IIC ERROR \r\n");
    }
    for(int i=0; i<len; i++)
    {
        I2c_Emc_SendByte(*buffer++);
        if(I2c_Emc_WaitAck())
        {
            DEBUG_PRINTF(DEBUG_STRING, "IIC ERROR \r\n");
        }
    }
    I2c_Emc_Stop();
}

void Emc2305_ReadByte(uint8_t id, uint8_t addr, uint8_t *buffer)
{
    I2c_Emc_Start();
    I2c_Emc_SendByte((id << 1) & 0xFE);     //发送器件地址, 写地址
    if(I2c_Emc_WaitAck())
    {
        DEBUG_PRINTF(DEBUG_STRING, "IIC ERROR \r\n");
    }
    I2c_Emc_SendByte(addr);
    if(I2c_Emc_WaitAck())
    {
        DEBUG_PRINTF(DEBUG_STRING, "IIC ERROR \r\n");
    }
    I2c_Emc_Start();
    I2c_Emc_SendByte((id << 1) | 0x01);     //发送器件地址, 读地址
    if(I2c_Emc_WaitAck())
    {
        DEBUG_PRINTF(DEBUG_STRING, "IIC ERROR \r\n");
    }
    *buffer = I2c_Emc_ReadByte();
    I2c_Emc_SendNack();
    I2c_Emc_Stop();
}

void Emc2305_ReadData(uint8_t id, uint8_t addr, uint8_t *buffer, uint8_t len)
{
    uint8_t i = 0;
    
    I2c_Emc_Start();
    I2c_Emc_SendByte((id << 1) & 0xFE);     //发送器件地址, 写地址
    if(I2c_Emc_WaitAck())
    {
        DEBUG_PRINTF(DEBUG_STRING, "IIC ERROR \r\n");
    }
    I2c_Emc_SendByte(addr);
    if(I2c_Emc_WaitAck())
    {
        DEBUG_PRINTF(DEBUG_STRING, "IIC ERROR \r\n");
    }
    I2c_Emc_Start();
    I2c_Emc_SendByte((id << 1) | 0x01);     //发送器件地址, 读地址
    if(I2c_Emc_WaitAck())
    {
        DEBUG_PRINTF(DEBUG_STRING, "IIC ERROR \r\n");
    }
    do
    {
        Delay_Nop(10);
        *buffer++ = I2c_Emc_ReadByte();
        if(++i==len)
        {
            I2c_Emc_SendNack();
        }
        else
        {
            I2c_Emc_SendAck();
        }
    }while(i!=len);
    I2c_Emc_Stop();
}

extern System_MsgStruct SysMsg;

void Fan_Emc2305_Control()
{
    static uint8_t TempNow = 0, TempOld = 0;
    
    uint8_t Speed;
    
    if(SysMsg.Temperature.CPU >= SysMsg.Temperature.FPGA)
    {
        TempNow = SysMsg.Temperature.CPU;
    }
    else
    {
        TempNow = SysMsg.Temperature.FPGA;
    }
    
    if(TempNow >= SysMsg.Temperature.USPB)
    {
        TempNow = TempNow;
    }
    else
    {
        TempNow = SysMsg.Temperature.USPB;
    }
    
    if(TempNow != TempOld)
    {
        TempOld = TempNow;
        
        if(TempNow <= TEMPERATURE_50)
        {
            Emc2305_WriteByte(EMC2305_10K_ADDR, FAN1_SETTING, SPEED_NoMin); 
            Emc2305_WriteByte(EMC2305_10K_ADDR, FAN2_SETTING, SPEED_NoMin);
            Emc2305_WriteByte(EMC2305_10K_ADDR, FAN3_SETTING, SPEED_NoMin);
            Emc2305_WriteByte(EMC2305_10K_ADDR, FAN4_SETTING, SPEED_NoMin);
            Emc2305_WriteByte(EMC2305_10K_ADDR, FAN5_SETTING, SPEED_NoMin);
        }
        else if(TempNow > TEMPERATURE_50 && TempNow < TEMPERATURE_95)
        {
            Speed = SPEED_NoMin + (SPEED_NoMax - SPEED_NoMin) / (TEMPERATURE_95 - TEMPERATURE_50) * TempNow;
            Emc2305_WriteByte(EMC2305_10K_ADDR, FAN1_SETTING, Speed); 
            Emc2305_WriteByte(EMC2305_10K_ADDR, FAN2_SETTING, Speed); 
            Emc2305_WriteByte(EMC2305_10K_ADDR, FAN3_SETTING, Speed); 
            Emc2305_WriteByte(EMC2305_10K_ADDR, FAN4_SETTING, Speed); 
            Emc2305_WriteByte(EMC2305_10K_ADDR, FAN5_SETTING, Speed); 
        }
        else
        {
            Emc2305_WriteByte(EMC2305_10K_ADDR, FAN1_SETTING, SPEED_NoMax);
            Emc2305_WriteByte(EMC2305_10K_ADDR, FAN2_SETTING, SPEED_NoMax);
            Emc2305_WriteByte(EMC2305_10K_ADDR, FAN3_SETTING, SPEED_NoMax);
            Emc2305_WriteByte(EMC2305_10K_ADDR, FAN4_SETTING, SPEED_NoMax);
            Emc2305_WriteByte(EMC2305_10K_ADDR, FAN5_SETTING, SPEED_NoMax);
        }
    }
}

void Fan_Speed_Read()
{
    uint8_t Tach1_Count[2], Tach2_Count[2], Tach3_Count[2], Tach4_Count[2], Tach5_Count[2];
    
    Emc2305_ReadData(EMC2305_10K_ADDR, FAN1_TACHREAD_HIGH, Tach1_Count, 2);
    Emc2305_ReadData(EMC2305_10K_ADDR, FAN2_TACHREAD_HIGH, Tach2_Count, 2);
    Emc2305_ReadData(EMC2305_10K_ADDR, FAN3_TACHREAD_HIGH, Tach3_Count, 2);
    Emc2305_ReadData(EMC2305_10K_ADDR, FAN4_TACHREAD_HIGH, Tach4_Count, 2);
    Emc2305_ReadData(EMC2305_10K_ADDR, FAN5_TACHREAD_HIGH, Tach5_Count, 2);
                                                          
    SysMsg.Fan.Rpm1 = 3932160 * 2 / ((Tach1_Count[0] << 8) + (Tach1_Count[1] >> 3));
    SysMsg.Fan.Rpm2 = 3932160 * 2 / ((Tach2_Count[0] << 8) + (Tach2_Count[1] >> 3));
    SysMsg.Fan.Rpm3 = 3932160 * 2 / ((Tach3_Count[0] << 8) + (Tach3_Count[1] >> 3));
    SysMsg.Fan.Rpm4 = 3932160 * 2 / ((Tach4_Count[0] << 8) + (Tach4_Count[1] >> 3));
    SysMsg.Fan.Rpm5 = 3932160 * 2 / ((Tach5_Count[0] << 8) + (Tach5_Count[1] >> 3));
}

void Fan_Emc2305_Init()
{
    uint8_t temp;
    
    Emc2305_WriteByte(EMC2305_10K_ADDR, BASIC_CTL, 0x80);               //屏蔽中断
    
    Emc2305_ReadByte(EMC2305_10K_ADDR, BASIC_CTL, &temp); 
    
    Emc2305_WriteByte(EMC2305_10K_ADDR, PWM_POLARITY, 0x00);            //设置PWM极性
    Emc2305_WriteByte(EMC2305_10K_ADDR, PWM_OUTPUT,   0x1F);            //设置PWM为推挽输出
    Emc2305_WriteByte(EMC2305_10K_ADDR, PWM45_BASE,   0x00);            //设置PWM4、PWM5基础频率为26KHz
    Emc2305_WriteByte(EMC2305_10K_ADDR, PWM123_BASE,  0x00);            //设置PWM1、PWM2、PWM3基础频率为26KHz
    Emc2305_WriteByte(EMC2305_10K_ADDR, FAN1_SETTING, SPEED_NoMin);     //设置占空比
    Emc2305_WriteByte(EMC2305_10K_ADDR, FAN2_SETTING, SPEED_NoMin);
    Emc2305_WriteByte(EMC2305_10K_ADDR, FAN3_SETTING, SPEED_NoMin);
    Emc2305_WriteByte(EMC2305_10K_ADDR, FAN4_SETTING, SPEED_NoMin);
    Emc2305_WriteByte(EMC2305_10K_ADDR, FAN5_SETTING, SPEED_NoMin);
}







