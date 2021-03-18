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
		if((System_MsgStr.SystemState == SYSTEM_OFF) && startCnt >= 60)   //�ڹػ�״̬�°��°���ִ�п���	
		{
            startCnt = 60;
            System_MsgStr.PowerOnReq = TRUE;
			stateFlag = TRUE;

		}
		if((System_MsgStr.SystemState == SYSTEM_ON) && startCnt >= 400)                     //�ڿ���״̬�°��°������͹ػ�����, ʹ��Ļ�����ػ��Ի���							
		{
			startCnt = 60;
            System_MsgStr.ShutDownReq = TRUE;
			stateFlag = TRUE;

		}
	}
	if(stateNow == FALSE)				//�����ɿ�
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
























