#include "system.h"

System_MsgStruct System_MsgStr = {
    .AdVolStr.CMD_HVFlag        = FALSE,
    .AdVolStr.CMD_CWFlag        = FALSE,
    .AdVolStr.T_VPP1            = 0,
    .AdVolStr.T_VNN1            = 0,
    .AdVolStr.T_VPP2            = 0,
    .AdVolStr.T_VNN2            = 0,
    .AdVolStr.T_PCW             = 0,
    .AdVolStr.T_NCW             = 0,
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
    System_MsgStr.AdVolStr.CMD_HVFlag        = FALSE;
    System_MsgStr.AdVolStr.CMD_CWFlag        = FALSE;
    System_MsgStr.AdVolStr.T_VPP1            = 0;
    System_MsgStr.AdVolStr.T_VNN1            = 0;
    System_MsgStr.AdVolStr.T_VPP2            = 0;
    System_MsgStr.AdVolStr.T_VNN2            = 0;
    System_MsgStr.AdVolStr.T_PCW             = 0;
    System_MsgStr.AdVolStr.T_NCW             = 0;
    System_MsgStr.Temperature.FPGA           = 0;
    System_MsgStr.Temperature.CPU            = 0;
    System_MsgStr.Temperature.USPB           = 0;
    System_MsgStr.Fan.Rpm1                   = 0;
    System_MsgStr.Fan.Rpm2                   = 0;
    System_MsgStr.Fan.Rpm3                   = 0;
    System_MsgStr.Fan.Rpm4                   = 0;
    System_MsgStr.Fan.Rpm5                   = 0;
    System_MsgStr.SystemState                = SYSTEM_OFF;
    System_MsgStr.PowerOnReq                 = FALSE;
    System_MsgStr.ShutDownReq                = FALSE;
    System_MsgStr.System_S3_Change           = FALSE;
    System_MsgStr.System_S4_Change           = FALSE;
    System_MsgStr.S3Minitor                  = FALSE;
}


void Delay_Nop(uint16_t count)
{
    while(--count);
}


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
			startCnt = 400;
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

void System_S3_State_Minitor()
{  
    OS_ERR err;
    
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
    
    if(s3StateChanged == TRUE)
    {
        if(stateNow == TRUE)
        {
            OSTimeDly(2, OS_OPT_TIME_DLY, &err);
            CTL_P12V_EN(1);
            OSTimeDly(20, OS_OPT_TIME_DLY, &err);
            CTL_N12V_5V5_EN(1);
            OSTimeDly(20, OS_OPT_TIME_DLY, &err);
            CTL_P5V5_1_EN(1);
            OSTimeDly(20, OS_OPT_TIME_DLY, &err);
            CTL_P5V5_2_EN(1);
            OSTimeDly(20, OS_OPT_TIME_DLY, &err);
            CTL_P3V75_EN(1);
            CTL_P2V25_EN(1);
            OSTimeDly(20, OS_OPT_TIME_DLY, &err);
            CTL_D0V95_EN(1);
            OSTimeDly(15, OS_OPT_TIME_DLY, &err);
            CTL_VDD_P5V_EN(1);
            CTL_D1V45_EN(1);
            EN_FRONT(1);
            EN_FPGA_01(1); 
            AFE_EN1(1);
            OSTimeDly(15, OS_OPT_TIME_DLY, &err);
            EN_FPGA_02(1);
            AFE_EN2(1);
        }
        else
        {
            OSTimeDly(2, OS_OPT_TIME_DLY, &err);
            CTL_P12V_EN(1);
            OSTimeDly(20, OS_OPT_TIME_DLY, &err);
            CTL_N12V_5V5_EN(1);
            OSTimeDly(20, OS_OPT_TIME_DLY, &err);
            CTL_P5V5_1_EN(1);
            OSTimeDly(20, OS_OPT_TIME_DLY, &err);
            CTL_P5V5_2_EN(1);
            OSTimeDly(20, OS_OPT_TIME_DLY, &err);
            CTL_P3V75_EN(1);
            CTL_P2V25_EN(1);
            OSTimeDly(20, OS_OPT_TIME_DLY, &err);
            CTL_D0V95_EN(1);
            OSTimeDly(15, OS_OPT_TIME_DLY, &err);
            CTL_VDD_P5V_EN(1);
            CTL_D1V45_EN(1);
            EN_FRONT(1);
            EN_FPGA_01(1); 
            AFE_EN1(1);
            OSTimeDly(15, OS_OPT_TIME_DLY, &err);
            EN_FPGA_02(1);
            AFE_EN2(1);
        }
    }
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
        System_MsgStr.System_S4_Change = TRUE;
    }
    if(stateNow == stateOld)
    {
        startCnt = 0;
    }
    return s4StateChanged; 
}






















