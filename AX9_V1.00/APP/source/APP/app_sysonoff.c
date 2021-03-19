#include "app_sysonoff.h"

extern System_MsgStruct System_MsgStr;

OS_TCB SysOnOffTaskTcb;

CPU_STK App_SysOnOff_Task_Stk[APP_SYSONOFF_STK_SIZE];


void System_PowerOn(OS_ERR err)
{
    static uint16_t startCnt = 0;
    static uint8_t powerOnStep = 0;    
    
    if(System_MsgStr.PowerOnReq == TRUE)
    {
        PWR_CTL(1);
        PBUS_ON(1);
        PWR_BTN_COM(0);
        OSTimeDly(100, OS_OPT_TIME_DLY, &err);
        PWR_BTN_COM(1);
        System_MsgStr.PowerOnReq = FALSE;
        powerOnStep = 1;
    }

    if(powerOnStep == 1)
    {
//        if(SUS_S3_CHK())
//        {
            //上电时序
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

            startCnt = 0;
            powerOnStep = 2;
//        }
//        else
//        {
//            if(++startCnt >= 200)       //开机失败, 规定时间内未能检测到S3信号拉高
//            {
//                PBUS_ON(0);
//                PWR_CTL(0);
//                startCnt = 0;
//                powerOnStep = 0;
//            }
//        }
    }

    if(powerOnStep == 2)
    {
        if(!FPGA_CFG_DOWN_CHK())
        {
            OSTimeDly(3000, OS_OPT_TIME_DLY, &err);
        }
        PWR_OK_COM(1);
        
        powerOnStep = 0;
        
        System_MsgStr.SystemState = SYSTEM_ON;
    }
}

void System_ShutDown(OS_ERR err)
{    
    static uint8_t shutDownStep = 0;
    if(System_MsgStr.ShutDownReq == TRUE)
    {
        PWR_BTN_COM(0);
        OSTimeDly(100, OS_OPT_TIME_DLY, &err);
        PWR_BTN_COM(1);
        System_MsgStr.ShutDownReq = FALSE;
        shutDownStep = 1;
    }
    
    if(shutDownStep == 1)
    {
//        if(!SUS_S3_CHK())
//        {
            //下电时序
            AFE_EN2(0);
            EN_FPGA_02(0);
            AFE_EN1(0);
            EN_FPGA_01(0);
            EN_FRONT(0);
            CTL_D1V45_EN(0);
            CTL_VDD_P5V_EN(0);
            CTL_D0V95_EN(0);
            CTL_P2V25_EN(0);
            CTL_P3V75_EN(0);
            CTL_P5V5_2_EN(0);
            CTL_P5V5_1_EN(0);
            CTL_N12V_5V5_EN(0);
            CTL_P12V_EN(0);
            
            shutDownStep = 2;
//        }
    }
    
    if(shutDownStep == 2)
    {
        if(FPGA_CFG_DOWN_CHK() == FALSE)
        {
            PWR_OK_COM(0);
            
            shutDownStep = 0;
            
            System_MsgStr.SystemState = SYSTEM_OFF;
            
            while(PWR_KEY_CHK());
        }
    }
}

void App_SysOnOff_Task()
{
	OS_ERR err;

	while(1)
	{		
        System_PowerOn(err);
        System_ShutDown(err);
        OSTimeDlyHMSM(0, 0, 0, 10, OS_OPT_TIME_PERIODIC, &err);
	}
}

void App_SysOnOff_TaskCreate()
{
	OS_ERR err;
	
	OSTaskCreate((OS_TCB *			)&SysOnOffTaskTcb, 
				 (CPU_CHAR *		)"SysOnOffTaskTcb", 
				 (OS_TASK_PTR		)App_SysOnOff_Task,
				 (void *			)0,
				 (OS_PRIO			)APP_SYSONOFF_TASK_PRIO,
				 (CPU_STK *			)&App_SysOnOff_Task_Stk[0],
				 (CPU_STK_SIZE		)APP_SYSONOFF_STK_SIZE / 10,
				 (CPU_STK_SIZE		)APP_SYSONOFF_STK_SIZE,
				 (OS_MSG_QTY		)0,
				 (OS_TICK			)0,
				 (void *			)0,
				 (OS_OPT			)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
				 (OS_ERR *			)&err);
}
