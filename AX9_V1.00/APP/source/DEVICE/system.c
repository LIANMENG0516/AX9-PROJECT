#include "system.h"

System_MsgStruct System_MsgStr;


void Power_On()
{

}

void Power_Off()
{

}

void Shutdown_Request()
{

}

bool System_PowerControl()	
{	
	bool stateFlag = FALSE;
	static uint16_t startCnt = 0;
	static bool stateNow = FALSE;
		
	stateNow = PWR_KEY_CHK() ? TRUE : FALSE;
	
	if(stateNow == TRUE  && ++startCnt)						
	{	
		if((System_MsgStr.SystemState == SYSTEM_OFF) && startCnt >= 50 && startCnt < 400)   //在关机状态下按下按键执行开机	
		{
			System_MsgStr.SystemState = SYSTEM_ON; 
			stateFlag = TRUE;
			Power_On();
			
		}
		if((System_MsgStr.SystemState == SYSTEM_ON) && startCnt >= 400)                     //在开机状态下按下按键发送关机请求, 使屏幕弹出关机对话框							
		{
			startCnt = 400;
			stateFlag = TRUE;
			Shutdown_Request();
		}
	}
	if(stateNow == FALSE)				//按键松开
	{
		startCnt = 0;
	}

	return stateFlag;
}







