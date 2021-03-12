#ifndef __ADC_H_
#define __ADC_H_

#include "stm32f4xx.h"

#define ADC_VCHANNEL_NUM    14
#define ADC_VSAMPLE_NUM     20

#define ADC_ICHANNEL_NUM    1
#define ADC_ISAMPLE_NUM     20

#define ADC_DMAY_STREAMX_V DMA2_Stream0
#define ADC_DMA_CHANNEL_V  DMA_Channel_2

#define ADC_DMAY_STREAMX_I DMA2_Stream0
#define ADC_DMA_CHANNEL_I  DMA_Channel_0

//ADC3
#define CHANNEL_VPP1 	    ADC_Channel_10		
#define CHANNEL_VNN1 	    ADC_Channel_11
#define CHANNEL_VPP2 	    ADC_Channel_12		
#define CHANNEL_VNN2 	    ADC_Channel_13
#define CHANNEL_A2V25 	    ADC_Channel_9		
#define CHANNEL_A3V75 	    ADC_Channel_14
#define CHANNEL_AP5V5_1 	ADC_Channel_15	
#define CHANNEL_AP12V	    ADC_Channel_4		
#define CHANNEL_AN5V5	    ADC_Channel_5		
#define CHANNEL_AN12V	    ADC_Channel_6
#define CHANNEL_D0V95 	    ADC_Channel_7
#define CHANNEL_D1V45 	    ADC_Channel_8
#define CHANNEL_AP5V5_2 	ADC_Channel_2
#define CHANNEL_D5V 	    ADC_Channel_3

//ADC1
#define CHANNEL_IADP 	    ADC_Channel_15      //�������

void Adc_Init(ADC_TypeDef* ADCx, uint8_t NumChannel);

#endif

