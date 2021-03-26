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
	
	USART_ITConfig(DEBUG_COM, USART_IT_RXNE, DISABLE);								//�ر�RXNE�ж� 
	USART_ITConfig(DEBUG_COM, USART_IT_TXE, DISABLE);								//�ر�TXE�ж�
    USART_ITConfig(DEBUG_COM, USART_IT_IDLE, ENABLE);								//����IDLE�ж�
    
	USART_DMACmd(DEBUG_COM, USART_DMAReq_Rx, ENABLE);								//����USART_DMA����ͨ��
	USART_DMACmd(DEBUG_COM, USART_DMAReq_Tx, ENABLE);								//����USART_DMA����ͨ��
    
    Dma_Config(DEBUG_COM_DMAY_STREAMX_RX, DEBUG_COM_DMA_CHANNEL_RX, (uint32_t)&DEBUG_COM->DR, (uint32_t)DebugComRX.Data, sizeof(DebugComRX.Data), DMA_PeripheralDataSize_Byte, DMA_MemoryDataSize_Byte, DMA_Mode_Normal, DMA_Priority_VeryHigh);      //����DEBUG_COM_RX_DMAͨ��                                                                     
    Dma_Config(DEBUG_COM_DMAY_STREAMX_TX, DEBUG_COM_DMA_CHANNEL_TX, (uint32_t)&DEBUG_COM->DR, (uint32_t)DebugComTX.Data, sizeof(DebugComTX.Data), DMA_PeripheralDataSize_Byte, DMA_MemoryDataSize_Byte, DMA_Mode_Normal, DMA_Priority_VeryHigh);      //����DEBUG_COM_TX_DMAͨ��  
    
    DMA_Cmd(DEBUG_COM_DMAY_STREAMX_RX, ENABLE);                                     //ʹ��DMA����
	DMA_Cmd(DEBUG_COM_DMAY_STREAMX_TX, DISABLE);                                    //�ر�DMA����
    
	DMA_ITConfig(DEBUG_COM_DMAY_STREAMX_TX, DMA_IT_TC, ENABLE);						//����DMA�����ж�	
}

void Commu_Com_Config()
{
	Usart_Init(COMMU_COM, 115200);	
	
	USART_ITConfig(COMMU_COM, USART_IT_RXNE, DISABLE);								//�ر�RXNE�ж� 
	USART_ITConfig(COMMU_COM, USART_IT_TXE, DISABLE);								//�ر�TXE�ж�
    USART_ITConfig(COMMU_COM, USART_IT_IDLE, ENABLE);								//����IDLE�ж�
    
	USART_DMACmd(COMMU_COM, USART_DMAReq_Rx, ENABLE);								//����USART_DMA����ͨ��
	USART_DMACmd(COMMU_COM, USART_DMAReq_Tx, ENABLE);								//����USART_DMA����ͨ��
    
    Dma_Config(COMMU_COM_DMAY_STREAMX_RX, COMMU_COM_DMA_CHANNEL_RX, (uint32_t)&COMMU_COM->DR, (uint32_t)CommuComRX.Data, sizeof(CommuComRX.Data), DMA_PeripheralDataSize_Byte, DMA_MemoryDataSize_Byte, DMA_Mode_Normal, DMA_Priority_VeryHigh);      //����DEBUG_COM_RX_DMAͨ��                                                                     
    Dma_Config(COMMU_COM_DMAY_STREAMX_TX, COMMU_COM_DMA_CHANNEL_TX, (uint32_t)&COMMU_COM->DR, (uint32_t)CommuComTX.Data, sizeof(CommuComTX.Data), DMA_PeripheralDataSize_Byte, DMA_MemoryDataSize_Byte, DMA_Mode_Normal, DMA_Priority_VeryHigh);      //����DEBUG_COM_TX_DMAͨ��  
    
    DMA_Cmd(COMMU_COM_DMAY_STREAMX_RX, ENABLE);                                      //ʹ��DMA����
	DMA_Cmd(COMMU_COM_DMAY_STREAMX_TX, DISABLE);                                     //�ر�DMA����
    
	DMA_ITConfig(COMMU_COM_DMAY_STREAMX_TX, DMA_IT_TC, ENABLE);						 //����DMA�����ж�	
}



void V_Adc_Config()
{
    Adc_Init(ADC3, ADC_VCHANNEL_NUM);
    
    ADC_RegularChannelConfig(ADC3, CHANNEL_VPP1,    SAMPLE_VPP1_SEQUENCE,    ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC3, CHANNEL_VNN1,    SAMPLE_VNN1_SEQUENCE,    ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC3, CHANNEL_VPP2,    SAMPLE_VPP2_SEQUENCE,    ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC3, CHANNEL_VNN2,    SAMPLE_VNN2_SEQUENCE,    ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC3, CHANNEL_A3V75,   SAMPLE_A3V75_SEQUENCE,   ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC3, CHANNEL_A2V25,   SAMPLE_A2V25_SEQUENCE,   ADC_SampleTime_480Cycles);
    ADC_RegularChannelConfig(ADC3, CHANNEL_AP12V,   SAMPLE_AP12V_SEQUENCE,   ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC3, CHANNEL_AN12V,   SAMPLE_AN12V_SEQUENCE,   ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC3, CHANNEL_AP5V5_1, SAMPLE_AP5V5_1_SEQUENCE, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC3, CHANNEL_AP5V5_2, SAMPLE_AP5V5_2_SEQUENCE, ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC3, CHANNEL_AN5V5,   SAMPLE_AN5V5_SEQUENCE,   ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC3, CHANNEL_D5V,     SAMPLE_D5V_SEQUENCE,     ADC_SampleTime_480Cycles);
    ADC_RegularChannelConfig(ADC3, CHANNEL_D0V95,   SAMPLE_D0V95_SEQUENCE,   ADC_SampleTime_480Cycles);
	ADC_RegularChannelConfig(ADC3, CHANNEL_D1V45,   SAMPLE_D1V45_SEQUENCE,   ADC_SampleTime_480Cycles);
}

void I_Adc_Config()
{
    Adc_Init(ADC1, ADC_ICHANNEL_NUM);
    
    ADC_RegularChannelConfig(ADC1, CHANNEL_VPP1, 1,  ADC_SampleTime_480Cycles);

	ADC_SoftwareStartConv(ADC1);										     //��ʼת��
}



extern uint16_t  Adc_V_ConValue[ADC_VSAMPLE_NUM][ADC_VCHANNEL_NUM];

extern uint16_t  Adc_I_ConValue[ADC_ISAMPLE_NUM];

void V_AdcDma_Config()
{
    V_Adc_Config();                                                         //(uint32_t)Adc_V_ConValue, ADC_VSAMPLE_NUM * ADC_VCHANNEL_NUM
    Dma_Config(ADC_DMAY_STREAMX_V, ADC_DMA_CHANNEL_V, (uint32_t)&ADC3->DR, (uint32_t)Adc_V_ConValue, ADC_VSAMPLE_NUM * ADC_VCHANNEL_NUM, DMA_PeripheralDataSize_HalfWord, DMA_MemoryDataSize_HalfWord, DMA_Mode_Circular, DMA_Priority_VeryHigh);                                                                                                                                                                                                                  
    DMA_Cmd(ADC_DMAY_STREAMX_V, ENABLE); 
//    ADC_DMARequestAfterLastTransferCmd(ADC3, ENABLE);                       //�����������ֻ����һ��DMAת��
//    ADC_SoftwareStartConv(ADC3);										     //��ʼת��
    
//    ADC_CommonInitTypeDef ADC_CommonInitStruct;
//    ADC_InitTypeDef ADC_InitStruct;
//    
//    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
//    
//    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, ENABLE);
//    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, DISABLE);
//    
//    ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
//    ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;                            //Ԥ��Ƶ4��Ƶ                            
//    ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
//    ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;          //���������׶�֮����ӳ�5��ʱ��
//    ADC_CommonInit(&ADC_CommonInitStruct);
//    
//    ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
//    ADC_InitStruct.ADC_ScanConvMode = ENABLE;                                           //ɨ��ģʽ
//    ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;                                     //����ת��ģʽ
//    ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;            //ת��������������ⲿ��������
//    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_Ext_IT11;
//    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
//    ADC_InitStruct.ADC_NbrOfConversion = 14;                                    //˳����й���ת����ADCͨ������Ŀ 
//    ADC_Init(ADC3, &ADC_InitStruct);
//    
//    ADC_Cmd(ADC3, ENABLE);														        //ʹ��ָ����ADCx

//    ADC_RegularChannelConfig(ADC3, CHANNEL_VPP1,    SAMPLE_VPP1_SEQUENCE,    ADC_SampleTime_480Cycles);
//	ADC_RegularChannelConfig(ADC3, CHANNEL_VNN1,    SAMPLE_VNN1_SEQUENCE,    ADC_SampleTime_480Cycles);
//	ADC_RegularChannelConfig(ADC3, CHANNEL_VPP2,    SAMPLE_VPP2_SEQUENCE,    ADC_SampleTime_480Cycles);
//	ADC_RegularChannelConfig(ADC3, CHANNEL_VNN2,    SAMPLE_VNN2_SEQUENCE,    ADC_SampleTime_480Cycles);
//	ADC_RegularChannelConfig(ADC3, CHANNEL_A3V75,   SAMPLE_A3V75_SEQUENCE,   ADC_SampleTime_480Cycles);
//	ADC_RegularChannelConfig(ADC3, CHANNEL_A2V25,   SAMPLE_A2V25_SEQUENCE,   ADC_SampleTime_480Cycles);
//    ADC_RegularChannelConfig(ADC3, CHANNEL_AP12V,   SAMPLE_AP12V_SEQUENCE,   ADC_SampleTime_480Cycles);
//	ADC_RegularChannelConfig(ADC3, CHANNEL_AN12V,   SAMPLE_AN12V_SEQUENCE,   ADC_SampleTime_480Cycles);
//	ADC_RegularChannelConfig(ADC3, CHANNEL_AP5V5_1, SAMPLE_AP5V5_1_SEQUENCE, ADC_SampleTime_480Cycles);
//	ADC_RegularChannelConfig(ADC3, CHANNEL_AP5V5_2, SAMPLE_AP5V5_2_SEQUENCE, ADC_SampleTime_480Cycles);
//	ADC_RegularChannelConfig(ADC3, CHANNEL_AN5V5,   SAMPLE_AN5V5_SEQUENCE,   ADC_SampleTime_480Cycles);
//	ADC_RegularChannelConfig(ADC3, CHANNEL_D5V,     SAMPLE_D5V_SEQUENCE,     ADC_SampleTime_480Cycles);
//    ADC_RegularChannelConfig(ADC3, CHANNEL_D0V95,   SAMPLE_D0V95_SEQUENCE,   ADC_SampleTime_480Cycles);
//	ADC_RegularChannelConfig(ADC3, CHANNEL_D1V45,   SAMPLE_D1V45_SEQUENCE,   ADC_SampleTime_480Cycles);

//    
//    
//    
//    
//    
//    DMA_InitTypeDef DMA_InitStructure;	

//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);	

//	DMA_InitStructure.DMA_Channel = DMA_Channel_2;    				
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC3->DR;
//	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Adc_V_ConValue;  														
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;									
//	DMA_InitStructure.DMA_BufferSize = ADC_VSAMPLE_NUM * ADC_VCHANNEL_NUM;			
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;								
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;									
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;							
//	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;									
//    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;	
//    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;	
//    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;	
//    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;	
//    
//	DMA_Init(DMA2_Stream0, &DMA_InitStructure);
//	
//	DMA_Cmd(DMA2_Stream0, ENABLE);
    
//    ADC_TempSensorVrefintCmd( ENABLE );                                          //�ڲ��ο���ѹ���� 
	ADC_DMARequestAfterLastTransferCmd( ADC3, ENABLE );                         //�����������ֻ����һ��DMA�ж�
    
    
    ADC_DMACmd(ADC3, ENABLE);
	ADC_SoftwareStartConv(ADC3);	
}

void I_AdcDma_Config()
{
    //I_Adc_Config();
    Adc_Init(ADC1, ADC_ICHANNEL_NUM);
    ADC_RegularChannelConfig(ADC1, CHANNEL_VPP1, 1,  ADC_SampleTime_480Cycles);
	ADC_SoftwareStartConv(ADC1);										     //��ʼת��

    ADC_DMACmd(ADC1, ENABLE);
    Dma_Config(ADC_DMAY_STREAMX_I, ADC_DMA_CHANNEL_I, (uint32_t)&ADC1->DR, (uint32_t)Adc_I_ConValue, ADC_ISAMPLE_NUM, DMA_PeripheralDataSize_HalfWord, DMA_MemoryDataSize_HalfWord, DMA_Mode_Circular, DMA_Priority_VeryHigh);                                                                                                                                                                                                                  
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
    
    Commu_Com_Config();                     //ͨѶ���ڳ�ʼ��--��ECͨѶ
    Debug_Com_Config();                     //���Դ��ڳ�ʼ��
    
    Spi_Dac_Config();
    
    V_AdcDma_Config();                      //��ѹ����ͨ����ʼ��--��14·��ѹ����, ȫ��ʹ��ADC3
    //I_AdcDma_Config();                      //��������ͨ����ʼ��--��1·��������, ʹ�ò������轫����ת��Ϊ��ѹ���в���, ʹ��ADC1

    
//    Dac_config(DAC_Channel_1);
//    Dac_config(DAC_Channel_2);
    
    
//    PWR_CTL(1);
//    PBUS_ON(1);
//    CTL_P12V_EN(1);
//    CTL_N12V_5V5_EN(1);
//    CTL_P5V5_1_EN(1);
//    CTL_P5V5_2_EN(1);
//    CTL_P3V75_EN(1);
//    CTL_P2V25_EN(1);
//    CTL_D0V95_EN(1);
//    CTL_VDD_P5V_EN(1);
//    CTL_D1V45_EN(1);
//    EN_FRONT(1);
//    EN_FPGA_01(1); 
//    AFE_EN1(1);
//    EN_FPGA_02(1);
//    AFE_EN2(1);
//    while(1);
//    
//    DacCw_Tlv5626cd_Shutdown();
//    
//    
//    Adjust_Voltage_Vpp1(10);
//    Adjust_Voltage_Vnn1(10);
//    
//    Adjust_Voltage_Vpp2(40);
//    Adjust_Voltage_Vnn2(40);
//    
//    CTL_VNN1_VPP1_EN(0);
//    
//    CTL_VNN2_VPP2_EN(0);

//    Adjust_Voltage_Pcw(0);
//    Adjust_Voltage_Ncw(0);
}













