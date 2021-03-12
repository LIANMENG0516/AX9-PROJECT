#include "app_usb.h"

OS_CPU_EXT __IO uint32_t receive_count;
OS_CPU_EXT __ALIGN_BEGIN uint8_t USB_Rx_Buffer[CDC_DATA_MAX_PACKET_SIZE] __ALIGN_END ;
OS_CPU_EXT CDC_IF_Prop_TypeDef VCP_fops;

__ALIGN_BEGIN uint8_t USB_Tx_Buffer[CDC_DATA_MAX_PACKET_SIZE] __ALIGN_END ;

OS_TCB UsbTaskTcb;

CPU_STK App_Usb_Task_Stk[APP_LED_STK_SIZE];

void App_Usb_Task()
{
	while(1)
	{					
		if(VCP_CheckDataReceived() != 0)
		{
			//VCP_fops.pIf_DataTx(USB_Tx_Buffer, receive_count);
			
            
            if(ReceiveFrameAnalysis(USB_Rx_Buffer, receive_count) == SUCCESS)
            {
                Cmd_Process();                       //�����
                FrameCmdPackage(USB_Tx_Buffer);
                VCP_fops.pIf_DataTx(USB_Tx_Buffer, (USB_Tx_Buffer[3] + 6));
            }
            
            receive_count = 0;
		}

	}
}

void App_Usb_TaskCreate()
{
	OS_ERR err;
	
	OSTaskCreate((OS_TCB *			)&UsbTaskTcb, 
				 (CPU_CHAR *		)"App_Usb_Task", 
				 (OS_TASK_PTR		)App_Usb_Task,
				 (void *			)0,
				 (OS_PRIO			)APP_USB_TASK_PRIO,
				 (CPU_STK *			)&App_Usb_Task_Stk[0],
				 (CPU_STK_SIZE		)APP_USB_STK_SIZE / 10,
				 (CPU_STK_SIZE		)APP_USB_STK_SIZE,
				 (OS_MSG_QTY		)0,
				 (OS_TICK			)0,
				 (void *			)0,
				 (OS_OPT			)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
				 (OS_ERR *			)&err);
}





