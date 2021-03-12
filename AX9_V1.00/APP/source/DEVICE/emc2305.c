#include "emc2305.h"

#include "gouble.h"

void I2c_Emc_Start()
{
	EMC_SDA_OUT();
	EMC_SCK_1();
	EMC_SDA_1();
	Delay_ms(5);
	EMC_SDA_0();
	Delay_ms(5);
	EMC_SCK_0();
	Delay_ms(5);
}

void I2c_Emc_Stop()
{
	EMC_SDA_OUT();
	EMC_SCK_0();
	EMC_SDA_0();
	Delay_ms(5);
	EMC_SCK_1();
	Delay_ms(5);
	EMC_SDA_1();
	Delay_ms(5);
}

void I2c_Emc_SendByte(unsigned char data)
{	
	EMC_SDA_OUT();

	Delay_ms(5);
	for(uint8_t mask=0x80; mask!=0; mask>>=1)
	{
		if((mask&data) == 0)
		{
			EMC_SDA_0();
		}
		else
		{
			EMC_SDA_0();
		}
		Delay_ms(5);
		EMC_SCK_1();
		Delay_ms(5);
		EMC_SCK_0();
		Delay_ms(5);
	}
}

uint8_t I2c_Emc_WaitAck()
{
	uint16_t startCnt = 5000;
	
	EMC_SDA_IN();
	
	while(EMC_SDA_READ())
	{
		if(--startCnt == 0)
		{
			return 1;
		}
	}
	
	EMC_SCK_1();
	Delay_ms(5);    
	EMC_SCK_0();
	Delay_ms(5);
	return 0;
}

void I2c_Emc_SendAck()
{
	EMC_SDA_OUT();
    
	EMC_SCK_0();
	Delay_ms(5);
	EMC_SDA_0();
	Delay_ms(5);
	EMC_SCK_1();
	Delay_ms(5);
	EMC_SCK_0();
	Delay_ms(5);
}

void I2c_Emc_SendNack()
{
	EMC_SDA_OUT();
	EMC_SCK_0();
	Delay_ms(5);
	EMC_SDA_1();
	delay_us(5);
	EMC_SCK_1();
	Delay_ms(5);
	EMC_SCK_0();
	Delay_ms(5);
}

uint8_t I2c_Emc_ReadByte()
{
	uint8_t data;
	
	EMC_SDA_IN();
	EMC_SCK_0();

	for(uint8_t mask=0x80; mask!=0; mask>>=1)
	{
		if(EMC_SDA_READ()==0)
		{
			data &= ~mask;
		}
		else
		{
			data |= mask;
		}
		delay_us(5);
		EMC_SCK_1();
		delay_us(5);
		EMC_SCK_0();
		delay_us(5);
	}
	return data;
}


extern System_MsgStruct System_MsgStr;

void Fan_Emc2305_Control()
{
    uint8_t TempNow = 0, TempOld = 0, Speed;
    
    if(System_MsgStr.Temperature.CPU >= System_MsgStr.Temperature.FPGA)
    {
        TempNow = System_MsgStr.Temperature.CPU;
    }
    else
    {
        TempNow = System_MsgStr.Temperature.FPGA;
    }
    
    if(TempNow >= System_MsgStr.Temperature.USPB)
    {
        TempNow = TempNow;
    }
    else
    {
        TempNow = System_MsgStr.Temperature.USPB;
    }
    
    if(TempNow != TempOld)
    {
        TempOld = TempNow;
        
        if(TempNow <= TEMPERATURE_50)
        {
            Write_Emc2305_Reg(FAN1_SETTING, SPEED_NoMin); 
            Write_Emc2305_Reg(FAN2_SETTING, SPEED_NoMin);
            Write_Emc2305_Reg(FAN3_SETTING, SPEED_NoMin);
            Write_Emc2305_Reg(FAN4_SETTING, SPEED_NoMin);
            Write_Emc2305_Reg(FAN5_SETTING, SPEED_NoMin);
        }
        else if(TempNow > TEMPERATURE_50 && TempNow < TEMPERATURE_95)
        {
            Speed = SPEED_NoMin + (SPEED_NoMax - SPEED_NoMin) / (TEMPERATURE_95 - TEMPERATURE_50) * TempNow;
            Write_Emc2305_Reg(FAN1_SETTING, Speed); 
            Write_Emc2305_Reg(FAN2_SETTING, Speed); 
            Write_Emc2305_Reg(FAN3_SETTING, Speed); 
            Write_Emc2305_Reg(FAN4_SETTING, Speed); 
            Write_Emc2305_Reg(FAN5_SETTING, Speed); 
        }
        else
        {
            Write_Emc2305_Reg(FAN1_SETTING, SPEED_NoMax);
            Write_Emc2305_Reg(FAN2_SETTING, SPEED_NoMax);
            Write_Emc2305_Reg(FAN3_SETTING, SPEED_NoMax);
            Write_Emc2305_Reg(FAN4_SETTING, SPEED_NoMax);
            Write_Emc2305_Reg(FAN5_SETTING, SPEED_NoMax);
        }
    }
}

void Write_Emc2305_Reg(uint16_t addr, uint16_t val)
{
    I2c_Emc_Start();
    I2c_Emc_SendByte(EMC2305_ADDR_10K & 0xfe);     //发送器件地址, 写地址
    I2c_Emc_WaitAck();
    I2c_Emc_SendByte(addr);
    I2c_Emc_WaitAck();
    I2c_Emc_SendByte(val);
    I2c_Emc_WaitAck();
    I2c_Emc_Stop();
}

uint8_t Read_Emc2305_Reg(uint8_t addr)
{
    uint8_t data;
    
    I2c_Emc_Start();
    I2c_Emc_SendByte(EMC2305_ADDR_10K & 0xfe);     //发送器件地址, 写地址
    I2c_Emc_WaitAck();
    I2c_Emc_SendByte(addr);
    I2c_Emc_WaitAck();
    I2c_Emc_SendByte(EMC2305_ADDR_10K | 0x01);     //发送器件地址, 读地址
    I2c_Emc_WaitAck();
    data = I2c_Emc_ReadByte();
    I2c_Emc_SendNack();
    I2c_Emc_Stop();
    
    return data;
}

void Fan_Speed_Read()
{
    uint16_t Tach1_Count, Tach2_Count, Tach3_Count, Tach4_Count, Tach5_Count;
    
    Tach1_Count = ((Read_Emc2305_Reg(FAN1_TACHREAD_HIGH) << 8) + Read_Emc2305_Reg(FAN1_TACHREAD_LOW)) >> 3;                                                          
    System_MsgStr.Fan.Rpm1 = 3932160 * 2 / Tach1_Count;
    
    Tach2_Count = ((Read_Emc2305_Reg(FAN1_TACHREAD_HIGH) << 8) + Read_Emc2305_Reg(FAN1_TACHREAD_LOW)) >> 3;                                                          
    System_MsgStr.Fan.Rpm2 = 3932160 * 2 / Tach2_Count;
    
    Tach3_Count = ((Read_Emc2305_Reg(FAN1_TACHREAD_HIGH) << 8) + Read_Emc2305_Reg(FAN1_TACHREAD_LOW)) >> 3;                                                          
    System_MsgStr.Fan.Rpm3 = 3932160 * 2 / Tach3_Count;

    Tach4_Count = ((Read_Emc2305_Reg(FAN1_TACHREAD_HIGH) << 8) + Read_Emc2305_Reg(FAN1_TACHREAD_LOW)) >> 3;                                                          
    System_MsgStr.Fan.Rpm4 = 3932160 * 2 / Tach4_Count;
    
    Tach5_Count = ((Read_Emc2305_Reg(FAN1_TACHREAD_HIGH) << 8) + Read_Emc2305_Reg(FAN1_TACHREAD_LOW)) >> 3;                                                          
    System_MsgStr.Fan.Rpm5 = 3932160 * 2 / Tach5_Count;
}

void Fan_Emc2305_Init()
{
    Write_Emc2305_Reg(BASIC_CTL,    0x80);          //屏蔽中断
    Write_Emc2305_Reg(PWM_POLARITY, 0x00);          //设置PWM极性
    Write_Emc2305_Reg(PWM_OUTPUT,   0x1f);          //设置PWM为推挽输出
    Write_Emc2305_Reg(PWM45_BASE,   0x00);          //设置PWM4、PWM5基础频率为26KHz
    Write_Emc2305_Reg(PWM123_BASE,  0x00);          //设置PWM1、PWM2、PWM3基础频率为26KHz
    Write_Emc2305_Reg(FAN1_SETTING, SPEED_NoMin);   //设置占空比
    Write_Emc2305_Reg(FAN2_SETTING, SPEED_NoMin);
    Write_Emc2305_Reg(FAN3_SETTING, SPEED_NoMin);
    Write_Emc2305_Reg(FAN4_SETTING, SPEED_NoMin);
    Write_Emc2305_Reg(FAN5_SETTING, SPEED_NoMin);
}







