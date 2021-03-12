#include "adc.h"

#include "gouble.h"

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
    
    ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;                            //Ԥ��Ƶ4��Ƶ                            
    ADC_CommonInitStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;          //���������׶�֮����ӳ�20��ʱ��
    ADC_CommonInit(&ADC_CommonInitStruct);
    
    ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStruct.ADC_ScanConvMode = ENABLE;                                           //ɨ��ģʽ
    ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;                                     //����ת��ģʽ
    ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;            //ת��������������ⲿ��������
    ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_Ext_IT11;
    ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStruct.ADC_NbrOfConversion = NumChannel;                                    //˳����й���ת����ADCͨ������Ŀ 
    ADC_Init(ADCx, &ADC_InitStruct);
    
    ADC_Cmd(ADCx, ENABLE);														        //ʹ��ָ����ADCx
}


