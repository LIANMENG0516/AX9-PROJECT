#include "adc.h"

#include "gouble.h"

extern System_MsgStruct SysMsg;

void Adc_Init(ADC_TypeDef* ADCx, uint8_t NumChannel)
{    
    ADC_CommonInitTypeDef ADC_CommonInitStruct;
    ADC_InitTypeDef ADC_InitStruct;
    
    if(ADCx == ADC1)
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    if(ADCx == ADC2) 
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
    if(ADCx == ADC3) 
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);
    
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC3, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_ADC3, DISABLE);
    
    ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;                            //预分频4分频                            
    ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;          //两个采样阶段之间的延迟5个时钟
    ADC_CommonInit(&ADC_CommonInitStruct);
    
    ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStruct.ADC_ScanConvMode = ENABLE;                                           //扫描模式
    ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;                                     //连续转换模式
    ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;            //转换由软件而不是外部触发启动
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_Ext_IT11;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStruct.ADC_NbrOfConversion = NumChannel;                                    //顺序进行规则转换的ADC通道的数目 
    ADC_Init(ADCx, &ADC_InitStruct);
    
    ADC_Cmd(ADCx, ENABLE);														        //使能指定的ADCx
}

uint16_t  Adc_V_ConValue[ADC_VSAMPLE_NUM][ADC_VCHANNEL_NUM];

uint16_t  Adc_I_ConValue[ADC_ISAMPLE_NUM];

uint16_t Adc_ReadConvertValue(uint8_t sample_sequence)
{
	uint8_t  i, j;
	uint32_t sum = 0;
	uint16_t temp, dataBuf[ADC_VSAMPLE_NUM];
	
	for(i=0; i<ADC_VSAMPLE_NUM; i++)
	{
		dataBuf[i] = Adc_V_ConValue[i][sample_sequence-1];
	}
	for(i=0; i<ADC_VSAMPLE_NUM; i++)
	{
		for(j=0; j<ADC_VSAMPLE_NUM-1-i; j++)
		{
			if(dataBuf[j] > dataBuf[j+1])
			{
				temp = dataBuf[j];
				dataBuf[j] = dataBuf[j+1];
				dataBuf[j+1] = temp;
			}
		}
	}
	for(i=2; i<(ADC_VSAMPLE_NUM-2); i++)						//去掉两个最小值和两个最大值
	{
		sum = sum + dataBuf[i];
	}
	
	return (sum >> 4);
}



void Adc_GetVoltage()
{
	SysMsg.AdjVol.R_VPP1 = (uint32_t)(((Adc_ReadConvertValue(SAMPLE_VPP1_SEQUENCE) * 3.3 / 4095) / 4.22 * (100 + 4.22)) * 100);
	SysMsg.AdjVol.R_VNN1 = (uint32_t)(((Adc_ReadConvertValue(SAMPLE_VNN1_SEQUENCE) * 3.3 / 4095) / 2.67 * (100 + 2.67)) * 100);
	SysMsg.AdjVol.R_VPP2 = (uint32_t)(((Adc_ReadConvertValue(SAMPLE_VPP2_SEQUENCE) * 3.3 / 4095) / 4.22 * (100 + 4.22)) * 100);
	SysMsg.AdjVol.R_VNN1 = (uint32_t)(((Adc_ReadConvertValue(SAMPLE_VNN2_SEQUENCE) * 3.3 / 4095) / 2.67 * (100 + 2.67)) * 100);
	SysMsg.AdjVol.R_A3V75 = (uint32_t)(((Adc_ReadConvertValue(SAMPLE_A3V75_SEQUENCE) * 3.3 / 4095) / 15 * (15 + 24.9)) * 100);
    SysMsg.AdjVol.R_A2V25 = (uint32_t)(((Adc_ReadConvertValue(SAMPLE_A2V25_SEQUENCE) * 3.3 / 4095) / 15 * (15 + 24.9)) * 100);   
    SysMsg.AdjVol.R_AP12V = (uint32_t)(((Adc_ReadConvertValue(SAMPLE_AP12V_SEQUENCE) * 3.3 / 4095) / 4.99 * (4.99 + 24.9)) * 100);   
    SysMsg.AdjVol.R_AN12V = (uint32_t)(((Adc_ReadConvertValue(SAMPLE_AN12V_SEQUENCE) * 3.3 / 4095) / 4.99 * (4.99 + 110)) * 100);
    SysMsg.AdjVol.R_AP5V5_1 = (uint32_t)(((Adc_ReadConvertValue(SAMPLE_AP5V5_1_SEQUENCE) * 3.3 / 4095) / 15 * (15 + 24.9)) * 100);
    SysMsg.AdjVol.R_AP5V5_2 = (uint32_t)(((Adc_ReadConvertValue(SAMPLE_AP5V5_2_SEQUENCE) * 3.3 / 4095) / 15 * (15 + 24.9)) * 100);
    SysMsg.AdjVol.R_AN5V5 = (uint32_t)(((Adc_ReadConvertValue(SAMPLE_AN5V5_SEQUENCE) * 3.3 / 4095) / 4.99 * (4.99 + 10)) * 100);
    SysMsg.AdjVol.R_D5V = (uint32_t)(((Adc_ReadConvertValue(SAMPLE_D5V_SEQUENCE) * 3.3 / 4095) / 15 * (15 + 24.9)) * 100);
    SysMsg.AdjVol.R_D0V95 = (uint32_t)(((Adc_ReadConvertValue(SAMPLE_D0V95_SEQUENCE) * 3.3 / 4095) / 10 * (10 + 10)) * 100);
    SysMsg.AdjVol.R_D1V45 = (uint32_t)(((Adc_ReadConvertValue(SAMPLE_D1V45_SEQUENCE) * 3.3 / 4095) / 10 * (10 + 10)) * 100);

}

