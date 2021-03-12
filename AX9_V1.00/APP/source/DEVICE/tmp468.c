#include "tmp468.h"

#include "gouble.h"

void I2c_Tmp_Start()
{
	TMP_SDA_OUT();
	TMP_SCK_1();
	TMP_SDA_1();
	Delay_ms(5);
	TMP_SDA_0();
	Delay_ms(5);
	TMP_SCK_0();
	Delay_ms(5);
}

void I2c_Tmp_Stop()
{
	TMP_SDA_OUT();
	TMP_SCK_0();
	TMP_SDA_0();
	Delay_ms(5);
	TMP_SCK_1();
	Delay_ms(5);
	TMP_SDA_1();
	Delay_ms(5);
}

void I2c_Tmp_SendByte(unsigned char data)
{	
	TMP_SDA_OUT();

	Delay_ms(5);
	for(uint8_t mask=0x80; mask!=0; mask>>=1)
	{
		if((mask&data) == 0)
		{
			TMP_SDA_0();
		}
		else
		{
			TMP_SDA_0();
		}
		Delay_ms(5);
		TMP_SCK_1();
		Delay_ms(5);
		TMP_SCK_0();
		Delay_ms(5);
	}
}

uint8_t I2c_Tmp_WaitAck()
{
	uint16_t startCnt = 5000;
	
	TMP_SDA_IN();
	
	while(TMP_SDA_READ())
	{
		if(--startCnt == 0)
		{
			return 1;
		}
	}
	
	TMP_SCK_1();
	Delay_ms(5);    
	TMP_SCK_0();
	Delay_ms(5);
	return 0;
}

void I2c_Tmp_SendAck()
{
	TMP_SDA_OUT();
    
	TMP_SCK_0();
	Delay_ms(5);
	TMP_SDA_0();
	Delay_ms(5);
	TMP_SCK_1();
	Delay_ms(5);
	TMP_SCK_0();
	Delay_ms(5);
}

void I2c_Tmp_SendNack()
{
	TMP_SDA_OUT();
    
	TMP_SCK_0();
	Delay_ms(5);
	TMP_SDA_1();
	delay_us(5);
	TMP_SCK_1();
	Delay_ms(5);
	TMP_SCK_0();
	Delay_ms(5);
}

uint8_t I2c_Tmp_ReadByte()
{
	uint8_t data;
	
	TMP_SDA_IN();
	TMP_SCK_0();

	for(uint8_t mask=0x80; mask!=0; mask>>=1)
	{
		if(TMP_SDA_READ()==0)
		{
			data &= ~mask;
		}
		else
		{
			data |= mask;
		}
		delay_us(5);
		TMP_SCK_1();
		delay_us(5);
		TMP_SCK_0();
		delay_us(5);
	}
	return data;
}

void Tmp468_WriteByte(uint8_t id, uint16_t addr, uint16_t val)
{
    I2c_Tmp_Start();
    I2c_Tmp_SendByte(id & 0xfe);           //发送器件地址, 写地址
    I2c_Tmp_WaitAck();
    I2c_Tmp_SendByte(addr);
    I2c_Tmp_WaitAck();
    I2c_Tmp_SendByte(val);
    I2c_Tmp_WaitAck();
    I2c_Tmp_Stop();
}

void Tmp468_ReadByte(uint8_t id, uint8_t addr, uint8_t *buffer)
{
    I2c_Tmp_Start();
    I2c_Tmp_SendByte(id & 0xfe);     //发送器件地址, 写地址
    I2c_Tmp_WaitAck();
    I2c_Tmp_SendByte(addr);
    I2c_Tmp_WaitAck();
    I2c_Tmp_SendByte(id | 0x01);     //发送器件地址, 读地址
    I2c_Tmp_WaitAck();
    *buffer = I2c_Tmp_ReadByte();
    I2c_Tmp_SendNack();
    I2c_Tmp_Stop();
}

void Tmp468_ReadData(uint8_t id, uint8_t addr, uint8_t *buffer, uint8_t len)
{
    uint8_t i = 0;
    
    I2c_Tmp_Start();
    I2c_Tmp_SendByte(id & 0xfe); 
    I2c_Tmp_WaitAck();
    I2c_Tmp_SendByte(addr);
    I2c_Tmp_WaitAck();
    I2c_Tmp_Start();
    I2c_Tmp_SendByte(id | 0x01);
	I2c_Tmp_WaitAck();
    do
    {
        delay_us(50);
        *buffer++ = I2c_Tmp_ReadByte();
        if(++i==len)
        {
            I2c_Tmp_SendNack();
        }
        else
        {
            I2c_Tmp_SendAck();
        }
    }while(i!=len);
    I2c_Tmp_Stop();
}



extern System_MsgStruct System_MsgStr;


void Obtain_TemperatureFPGA()
{

    uint8_t Temp[2];


    Tmp468_ReadData(TMP468_ADDR, RT1_ADDR, Temp, 2);
    
    System_MsgStr.Temperature.FPGA1 = (int)(((((Temp[0] << 8) + Temp[1]) >> 3) * 0.0625) + 0.5);    //四舍五入取整数
}







