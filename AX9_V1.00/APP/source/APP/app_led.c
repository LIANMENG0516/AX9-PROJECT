#include "app_led.h"

OS_TCB LedTaskTcb;

CPU_STK App_Led_Task_Stk[APP_LED_STK_SIZE];

void App_Led_Task()
{
	OS_ERR err;

	while(1)
	{					
		GPIO_ResetBits(GPIOE, GPIO_Pin_8); 
		OSTimeDlyHMSM(0, 0, 0, 50, OS_OPT_TIME_PERIODIC, &err);
		GPIO_ResetBits(GPIOE, GPIO_Pin_9); 
		OSTimeDlyHMSM(0, 0, 0, 50, OS_OPT_TIME_PERIODIC, &err);
		GPIO_ResetBits(GPIOE, GPIO_Pin_10); 
		OSTimeDlyHMSM(0, 0, 0, 50, OS_OPT_TIME_PERIODIC, &err);
		GPIO_ResetBits(GPIOE, GPIO_Pin_11); 
		OSTimeDlyHMSM(0, 0, 0, 50, OS_OPT_TIME_PERIODIC, &err); 
		GPIO_SetBits(GPIOE, GPIO_Pin_8); 
		OSTimeDlyHMSM(0, 0, 0, 50, OS_OPT_TIME_PERIODIC, &err); 
		GPIO_SetBits(GPIOE, GPIO_Pin_9); 
		OSTimeDlyHMSM(0, 0, 0, 50, OS_OPT_TIME_PERIODIC, &err);
		GPIO_SetBits(GPIOE, GPIO_Pin_10); 
		OSTimeDlyHMSM(0, 0, 0, 50, OS_OPT_TIME_PERIODIC, &err);
		GPIO_SetBits(GPIOE, GPIO_Pin_11); 
		OSTimeDlyHMSM(0, 0, 0, 50, OS_OPT_TIME_PERIODIC, &err);
	}
}

void App_Led_TaskCreate()
{
	OS_ERR err;
	
	OSTaskCreate((OS_TCB *			)&LedTaskTcb, 
				 (CPU_CHAR *		)"App_Led_Task", 
				 (OS_TASK_PTR		)App_Led_Task,
				 (void *			)0,
				 (OS_PRIO			)APP_LED_TASK_PRIO,
				 (CPU_STK *			)&App_Led_Task_Stk[0],
				 (CPU_STK_SIZE		)APP_LED_STK_SIZE / 10,
				 (CPU_STK_SIZE		)APP_LED_STK_SIZE,
				 (OS_MSG_QTY		)0,
				 (OS_TICK			)0,
				 (void *			)0,
				 (OS_OPT			)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
				 (OS_ERR *			)&err);
}

