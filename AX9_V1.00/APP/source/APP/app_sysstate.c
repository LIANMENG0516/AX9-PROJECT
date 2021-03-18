#include "app_sysstate.h"

extern System_MsgStruct System_MsgStr;

OS_TCB SysStateTaskTcb;

CPU_STK App_SysState_Task_Stk[APP_SYSSTATE_STK_SIZE];

void App_SysState_Task()
{
	OS_ERR err;

	while(1)
	{		
        if(System_MsgStr.SystemState == SYSTEM_ON)
        {
            MCU_LED_BLINK();
        }
        if(System_MsgStr.SystemState == SYSTEM_OFF)
        {
            CTL_MCU_LED(0);
        }
        if(System_MsgStr.SystemState == SYSTEM_SLEEP)
        {
            CTL_MCU_LED(1);
        }

        OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_PERIODIC, &err);
	}
}

void App_SysState_TaskCreate()
{
	OS_ERR err;
	
	OSTaskCreate((OS_TCB *			)&SysStateTaskTcb, 
				 (CPU_CHAR *		)"App_SysState_Task", 
				 (OS_TASK_PTR		)App_SysState_Task,
				 (void *			)0,
				 (OS_PRIO			)APP_SYSSTATE_TASK_PRIO,
				 (CPU_STK *			)&App_SysState_Task_Stk[0],
				 (CPU_STK_SIZE		)APP_SYSSTATE_STK_SIZE / 10,
				 (CPU_STK_SIZE		)APP_SYSSTATE_STK_SIZE,
				 (OS_MSG_QTY		)0,
				 (OS_TICK			)0,
				 (void *			)0,
				 (OS_OPT			)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
				 (OS_ERR *			)&err);
}
