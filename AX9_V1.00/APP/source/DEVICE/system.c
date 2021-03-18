#include "system.h"

System_MsgStruct System_MsgStr;

bool System_PwrKey_Minitor()	
{	
	bool stateFlag = FALSE;
	static uint16_t startCnt = 0;
	static bool stateNow = FALSE;
		
	stateNow = PWR_KEY_CHK() ? TRUE : FALSE;

	if(stateNow == TRUE  && ++startCnt)						
	{	
		if((System_MsgStr.SystemState == SYSTEM_OFF) && startCnt >= 60)   //在关机状态下按下按键执行开机	
		{
            startCnt = 60;
            System_MsgStr.PowerOnReq = TRUE;
			stateFlag = TRUE;

		}
		if((System_MsgStr.SystemState == SYSTEM_ON) && startCnt >= 400)                     //在开机状态下按下按键发送关机请求, 使屏幕弹出关机对话框							
		{
			startCnt = 60;
            System_MsgStr.ShutDownReq = TRUE;
			stateFlag = TRUE;

		}
	}
	if(stateNow == FALSE)				//按键松开
	{
		startCnt = 0;
	}

	return stateFlag;
}




bool System_S3_State_Minitor()
{  
    bool s3StateChanged = FALSE;
    
    static uint8_t startCnt = 0;
    
    static bool stateNow = FALSE, stateOld = FALSE;
    
    stateNow = (bool)SUS_S3_CHK();
    
    if((stateNow != stateOld) && (++startCnt >= 1)) 
    {
        startCnt = 0;
        stateOld = stateNow;
        s3StateChanged = TRUE;
        System_MsgStr.System_S3_Change = TRUE;
    }
    if(stateNow == stateOld)
    {
        startCnt = 0;
    }
    return s3StateChanged; 
}
























