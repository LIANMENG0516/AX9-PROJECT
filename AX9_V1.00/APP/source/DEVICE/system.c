#include "system.h"

System_MsgStruct SysMsg = {
    .AdjVol.T_VPP1              = 0,
    .AdjVol.T_VNN1              = 0,
    .AdjVol.T_VPP2              = 0,
    .AdjVol.T_VNN2              = 0,
    .Temperature.FPGA           = 0,
    .Temperature.CPU            = 0,
    .Temperature.USPB           = 0,
    .Fan.Rpm1                   = 0,
    .Fan.Rpm2                   = 0,
    .Fan.Rpm3                   = 0,
    .Fan.Rpm4                   = 0,
    .Fan.Rpm5                   = 0,
    .SystemState                = SYSTEM_OFF,
    .PowerOnReq                 = FALSE,
    .ShutDownReq                = FALSE,
    .System_S3_Change           = FALSE,
    .System_S4_Change           = FALSE,
    .S3Minitor                  = FALSE,
};

void SystemStateInit()
{
    SysMsg.AdjVol.T_VPP1                = 0;
    SysMsg.AdjVol.T_VNN1                = 0;
    SysMsg.AdjVol.T_VPP2                = 0;
    SysMsg.AdjVol.T_VNN2                = 0;
    SysMsg.AdjVol.HV_Minitor            = FALSE;
    SysMsg.Temperature.FPGA           = 0;
    SysMsg.Temperature.CPU            = 0;
    SysMsg.Temperature.USPB           = 0;
    SysMsg.Fan.Rpm1                   = 0;
    SysMsg.Fan.Rpm2                   = 0;
    SysMsg.Fan.Rpm3                   = 0;
    SysMsg.Fan.Rpm4                   = 0;
    SysMsg.Fan.Rpm5                   = 0;
    SysMsg.SystemState                = SYSTEM_OFF;
    SysMsg.PowerOnReq                 = FALSE;
    SysMsg.ShutDownReq                = FALSE;
    SysMsg.System_S3_Change           = FALSE;
    SysMsg.System_S4_Change           = FALSE;
    SysMsg.S3Minitor                  = FALSE;
}

void Delay_Nop(uint16_t count)
{
    while(--count);
}


bool System_PwrKey_Minitor()	
{	
	bool stateChange = FALSE;
	static uint16_t startCnt = 0;
	static bool stateNow = FALSE, stateOld = FALSE;
		
	stateNow = PWR_KEY_CHK() ? TRUE : FALSE;
    
    if(stateOld != stateNow && ++startCnt>=60)
    {
        startCnt = 0;
        SysMsg.KeyState = stateOld = stateNow;
        
        if(SysMsg.SystemState == SYSTEM_OFF)   //在关机状态下按下按键执行开机	
		{
            SysMsg.PowerOnReq = TRUE;
		}
        if(SysMsg.SystemState == SYSTEM_ON)    //在开机状态下按下按键发送关机请求, 使屏幕弹出关机对话框							
		{
            SysMsg.ShutDownReq = TRUE;
		}
        
        stateChange = TRUE;
    }
    if(stateNow == FALSE)
    {
        startCnt = 0;
        SysMsg.PowerOnReq = FALSE;
        SysMsg.ShutDownReq = FALSE;
        SysMsg.KeyState = FALSE;
        stateNow = stateOld = FALSE;
    }

	return stateChange;
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
        SysMsg.S3_State = stateOld = stateNow;
        s3StateChanged = TRUE;
        SysMsg.System_S3_Change = TRUE;
    }
    if(stateNow == stateOld)
    {
        startCnt = 0;
    }
    return s3StateChanged;
}

bool System_S4_State_Minitor()
{  
    bool s4StateChanged = FALSE;
    
    static uint8_t startCnt = 0;
    
    static bool stateNow = FALSE, stateOld = FALSE;
    
    stateNow = (bool)SUS_S4_CHK();
    
    if((stateNow != stateOld) && (++startCnt >= 1)) 
    {
        startCnt = 0;
        stateOld = stateNow;
        s4StateChanged = TRUE;
        SysMsg.System_S4_Change = TRUE;
    }
    if(stateNow == stateOld)
    {
        startCnt = 0;
    }
    return s4StateChanged; 
}






















