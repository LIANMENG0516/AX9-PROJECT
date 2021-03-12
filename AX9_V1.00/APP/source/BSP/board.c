#include "board.h"

#include "gouble.h"

__ALIGN_BEGIN USB_OTG_CORE_HANDLE USB_OTG_dev __ALIGN_END;

extern System_MsgStruct System_MsgStr;

extern Com_Buffer DebugComRX;
extern Com_Buffer DebugComTX;

extern Com_Buffer CommuComRX;
extern Com_Buffer CommuComTX;

void Debug_Com_Config()
{
	Usart_Init(DEBUG_COM, 115200);	
	
	USART_ITConfig(DEBUG_COM, USART_IT_RXNE, DISABLE);								//关闭RXNE中断 
	USART_ITConfig(DEBUG_COM, USART_IT_TXE, DISABLE);								//关闭TXE中断
    USART_ITConfig(DEBUG_COM, USART_IT_IDLE, ENABLE);								//开启IDLE中断
    
	USART_DMACmd(DEBUG_COM, USART_DMAReq_Rx, ENABLE);								//开启USART_DMA接收通道
	USART_DMACmd(DEBUG_COM, USART_DMAReq_Tx, ENABLE);								//开启USART_DMA发送通道
    
    Dma_Config(DEBUG_COM_DMAY_STREAMX_RX, DEBUG_COM_DMA_CHANNEL_RX, (uint32_t)&DEBUG_COM->DR, (uint32_t)DebugComRX.Data, sizeof(DebugComRX.Data), DMA_PeripheralDataSize_Byte, DMA_MemoryDataSize_Byte, DMA_Mode_Normal, DMA_Priority_VeryHigh);      //配置DEBUG_COM_RX_DMA通道                                                                     
    Dma_Config(DEBUG_COM_DMAY_STREAMX_TX, DEBUG_COM_DMA_CHANNEL_TX, (uint32_t)&DEBUG_COM->DR, (uint32_t)DebugComTX.Data, sizeof(DebugComTX.Data), DMA_PeripheralDataSize_Byte, DMA_MemoryDataSize_Byte, DMA_Mode_Normal, DMA_Priority_VeryHigh);      //配置DEBUG_COM_TX_DMA通道  
    
    DMA_Cmd(DEBUG_COM_DMAY_STREAMX_RX, ENABLE);                                     //使能DMA接收
	DMA_Cmd(DEBUG_COM_DMAY_STREAMX_TX, DISABLE);                                    //关闭DMA发送
    
	DMA_ITConfig(DEBUG_COM_DMAY_STREAMX_TX, DMA_IT_TC, ENABLE);						//开启DMA发送中断	
}

void Commu_Com_Config()
{
	Usart_Init(COMMU_COM, 115200);	
	
	USART_ITConfig(COMMU_COM, USART_IT_RXNE, DISABLE);								//关闭RXNE中断 
	USART_ITConfig(COMMU_COM, USART_IT_TXE, DISABLE);								//关闭TXE中断
    USART_ITConfig(COMMU_COM, USART_IT_IDLE, ENABLE);								//开启IDLE中断
    
	USART_DMACmd(COMMU_COM, USART_DMAReq_Rx, ENABLE);								//开启USART_DMA接收通道
	USART_DMACmd(COMMU_COM, USART_DMAReq_Tx, ENABLE);								//开启USART_DMA发送通道
    
    Dma_Config(COMMU_COM_DMAY_STREAMX_RX, COMMU_COM_DMA_CHANNEL_RX, (uint32_t)&COMMU_COM->DR, (uint32_t)CommuComRX.Data, sizeof(CommuComRX.Data), DMA_PeripheralDataSize_Byte, DMA_MemoryDataSize_Byte, DMA_Mode_Normal, DMA_Priority_VeryHigh);      //配置DEBUG_COM_RX_DMA通道                                                                     
    Dma_Config(COMMU_COM_DMAY_STREAMX_TX, COMMU_COM_DMA_CHANNEL_TX, (uint32_t)&COMMU_COM->DR, (uint32_t)CommuComTX.Data, sizeof(CommuComTX.Data), DMA_PeripheralDataSize_Byte, DMA_MemoryDataSize_Byte, DMA_Mode_Normal, DMA_Priority_VeryHigh);      //配置DEBUG_COM_TX_DMA通道  
    
    DMA_Cmd(COMMU_COM_DMAY_STREAMX_RX, ENABLE);                                      //使能DMA接收
	DMA_Cmd(COMMU_COM_DMAY_STREAMX_TX, DISABLE);                                     //关闭DMA发送
    
	DMA_ITConfig(COMMU_COM_DMAY_STREAMX_TX, DMA_IT_TC, ENABLE);						 //开启DMA发送中断	
}

void V_Adc_Config()
{
    Adc_Init(ADC3, ADC_ICHANNEL_NUM);
    
    ADC_RegularChannelConfig(ADC3, CHANNEL_VPP1,    1,  ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC3, CHANNEL_VNN1,    2,  ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC3, CHANNEL_VPP2,    3,  ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC3, CHANNEL_VNN2,    4,  ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC3, CHANNEL_A3V75,   5,  ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC3, CHANNEL_A2V25,   6,  ADC_SampleTime_480Cycles);

    ADC_RegularChannelConfig(ADC3, CHANNEL_AP12V,   7,  ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC3, CHANNEL_AN12V,   8,  ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC3, CHANNEL_AP5V5_1, 9,  ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC3, CHANNEL_AP5V5_2, 10, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC3, CHANNEL_AN5V5,   11, ADC_SampleTime_480Cycles);

	ADC_RegularChannelConfig(ADC3, CHANNEL_D5V,     12, ADC_SampleTime_480Cycles);
    ADC_RegularChannelConfig(ADC3, CHANNEL_D0V95,   13, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC3, CHANNEL_D1V45,   14, ADC_SampleTime_480Cycles);

	ADC_SoftwareStartConv(ADC3);										     //开始转换
}

void I_Adc_Config()
{
    Adc_Init(ADC1, ADC_ICHANNEL_NUM);
    
    ADC_RegularChannelConfig(ADC1, CHANNEL_VPP1,    1,  ADC_SampleTime_480Cycles);

	ADC_SoftwareStartConv(ADC1);										     //开始转换
}



uint16_t  Adc_V_ConValue[ADC_VSAMPLE_NUM][ADC_VCHANNEL_NUM];

uint16_t  Adc_I_ConValue[ADC_ISAMPLE_NUM];

void V_AdcDma_Config()
{
    V_Adc_Config();
    
    ADC_DMACmd(ADC3, ENABLE);
    Dma_Config(ADC_DMAY_STREAMX_V, ADC_DMA_CHANNEL_V, (uint32_t)&ADC3->DR, (uint32_t)Adc_V_ConValue, ADC_VSAMPLE_NUM * ADC_VCHANNEL_NUM, DMA_PeripheralDataSize_HalfWord, DMA_MemoryDataSize_HalfWord, DMA_Mode_Normal, DMA_Priority_VeryHigh);                                                                                                                                                                                                                  
    DMA_Cmd(ADC_DMAY_STREAMX_V, ENABLE); 
}

void I_AdcDma_Config()
{
    I_Adc_Config();

    ADC_DMACmd(ADC1, ENABLE);
    Dma_Config(ADC_DMAY_STREAMX_I, ADC_DMA_CHANNEL_I, (uint32_t)&ADC1->DR, (uint32_t)Adc_I_ConValue, ADC_ISAMPLE_NUM, DMA_PeripheralDataSize_HalfWord, DMA_MemoryDataSize_HalfWord, DMA_Mode_Normal, DMA_Priority_VeryHigh);                                                                                                                                                                                                                  
    DMA_Cmd(ADC_DMAY_STREAMX_I, ENABLE); 
}

void Fan_Config()
{
    Fan_Emc2305_Init();
}

void Board_Bsp_Init()
{
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0000);

	Nvic_Config();
	Gpio_Config();
	USBD_Init(&USB_OTG_dev, USB_OTG_FS_CORE_ID, &USR_desc, &USBD_CDC_cb, &USR_cb);
	
	SysTick_Iint();
    
    Commu_Com_Config();                     //通讯串口初始化--与EC通讯
    Debug_Com_Config();                     //调试串口初始化
    
    Spi_Dac_Config();
    
    V_AdcDma_Config();                      //电压采样通道初始化--共14路电压采样, 全部使用ADC3
    I_AdcDma_Config();                      //电流采样通道初始化--共1路电流采样, 使用采样电阻将电流转化为电压进行采样, 使用ADC1

    Fan_Config();                           //风扇初始化
}













