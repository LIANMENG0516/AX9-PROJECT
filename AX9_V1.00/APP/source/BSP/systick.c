#include "systick.h"

#include "gouble.h"

 __IO uint32_t TimingDelay;

void SysTick_Iint()
{
#ifdef USE_UCOSIII    
	SysTick_Config(21000000/OS_CFG_TICK_RATE_HZ);            	//此处设置了 UCOSII 的系统时钟为1ms, 滴答定时器的中断时间 = uCOS的1个节拍时间, 即ucos一个节拍时间为1ms
#else
	SysTick_Config(21000);
#endif
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);		//SysTick时钟: 168/8=21MHz
}

void Delay_ms(__IO uint32_t nTime)
{ 
	Set_DelayMs(nTime);
	while(Get_DelayMs());	
}

void TimingDelay_Decrement()
{
	if (TimingDelay != 0x00)
	{ 
		TimingDelay--;
	}
}

void Set_DelayMs(__IO uint32_t nTime)
{
	TimingDelay = nTime;
}

uint32_t Get_DelayMs()
{
	return TimingDelay;
}

void delay_us(uint16_t time)
{	  
	uint16_t temp;
	SysTick->LOAD = time * 21;
	SysTick->VAL = 0;
	SysTick->CTRL = (1 << 0);   
	do
	{
		temp = SysTick->CTRL;
	}
	while(!(temp & (1<<16)));
	SysTick->CTRL = 0;
	SysTick->VAL = 0;
}

void delay_ms(uint16_t time)
{	  
	uint32_t temp;
	SysTick->LOAD = time * 21000;
	SysTick->VAL = 0;
	SysTick->CTRL = (1 << 0);   
	do
	{
		temp = SysTick->CTRL;
	}
	while(!(temp & (1<<16)));
	SysTick->CTRL = 0;
	SysTick->VAL = 0;
}





























