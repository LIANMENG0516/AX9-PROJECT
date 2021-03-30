#include "app_com.h"

extern System_MsgStruct SysMsg;

extern CmdFrameStr SenFrameCmd;

extern Com_Buffer DebugComRX;
extern Com_Buffer DebugComTX;

extern Com_Buffer CommuComRX;
extern Com_Buffer CommuComTX;


OS_TCB ComTaskTcb;

CPU_STK App_Com_Task_Stk[APP_COM_STK_SIZE];

void App_Com_Task()
{
	OS_ERR err;

	while(1)
	{				
        if(ReceiveFrameAnalysis(&CommuComRX.Data[0], CommuComRX.Len) == SUCCESS)   //格式化并解析串口数据
        {
            memset(CommuComTX.Data, 0, CommuComTX.Len);
            Cmd_Process();                                  //命令处理
            FrameCmdPackage(CommuComTX.Data);
            Send_CmdPackage(COMMU_COM_DMAY_STREAMX_TX);                                     
        }
        
        if(ReceiveFrameAnalysis(&DebugComRX.Data[0], DebugComRX.Len) == SUCCESS)   //格式化并解析串口数据
        {
            memset(DebugComRX.Data, 0, DebugComRX.Len);
            Cmd_Process();                                  //命令处理
        }
        
        if(SysMsg.Cmd.HV_Send == TRUE)
        {
            SysMsg.Cmd.HV_Send = FALSE;
            
            SenFrameCmd.Cid = CMD_ADJUST_HV;
            SenFrameCmd.Len = 8;
            
            SenFrameCmd.Data[0] = SysMsg.AdjVol.R_VPP1 >> 8;
            SenFrameCmd.Data[1] = SysMsg.AdjVol.R_VPP1;
            SenFrameCmd.Data[2] = SysMsg.AdjVol.R_VNN1 >> 8;
            SenFrameCmd.Data[3] = SysMsg.AdjVol.R_VNN1;
            SenFrameCmd.Data[4] = SysMsg.AdjVol.R_VPP2 >> 8;
            SenFrameCmd.Data[5] = SysMsg.AdjVol.R_VPP2;
            SenFrameCmd.Data[6] = SysMsg.AdjVol.R_VNN2 >> 8;
            SenFrameCmd.Data[7] = SysMsg.AdjVol.R_VNN2;
            
            FrameCmdPackage(CommuComTX.Data);
            Send_CmdPackage(DEBUG_COM_DMAY_STREAMX_TX);
        }
        
        if(SysMsg.Cmd.CW_Send == TRUE)
        {
            SysMsg.Cmd.CW_Send = FALSE;
            
            SenFrameCmd.Cid = CMD_ADJUST_CW;
            SenFrameCmd.Len = 8;
            
            SenFrameCmd.Data[0] = SysMsg.AdjVol.R_VPP1 >> 8;
            SenFrameCmd.Data[1] = SysMsg.AdjVol.R_VPP1;
            SenFrameCmd.Data[2] = SysMsg.AdjVol.R_VNN1 >> 8;
            SenFrameCmd.Data[3] = SysMsg.AdjVol.R_VNN1;
            SenFrameCmd.Data[4] = SysMsg.AdjVol.R_VPP2 >> 8;
            SenFrameCmd.Data[5] = SysMsg.AdjVol.R_VPP2;
            SenFrameCmd.Data[6] = SysMsg.AdjVol.R_VNN2 >> 8;
            SenFrameCmd.Data[7] = SysMsg.AdjVol.R_VNN2;
            
            FrameCmdPackage(CommuComTX.Data);
            Send_CmdPackage(DEBUG_COM_DMAY_STREAMX_TX);
        }
        
        if(SysMsg.Cmd.Timeout == TRUE)
        {
            SysMsg.Cmd.Timeout = FALSE;
            
            SenFrameCmd.Cid = TIMEOUT;
            SenFrameCmd.Len = 8;
            
            SenFrameCmd.Data[0] = SysMsg.AdjVol.R_VPP1 >> 8;
            SenFrameCmd.Data[1] = SysMsg.AdjVol.R_VPP1;
            SenFrameCmd.Data[2] = SysMsg.AdjVol.R_VNN1 >> 8;
            SenFrameCmd.Data[3] = SysMsg.AdjVol.R_VNN1;
            SenFrameCmd.Data[4] = SysMsg.AdjVol.R_VPP2 >> 8;
            SenFrameCmd.Data[5] = SysMsg.AdjVol.R_VPP2;
            SenFrameCmd.Data[6] = SysMsg.AdjVol.R_VNN2 >> 8;
            SenFrameCmd.Data[7] = SysMsg.AdjVol.R_VNN2;
            
            FrameCmdPackage(CommuComTX.Data);
            Send_CmdPackage(DEBUG_COM_DMAY_STREAMX_TX);
        }

		OSTimeDlyHMSM(0, 0, 0, 10, OS_OPT_TIME_PERIODIC, &err);
	}
}

void App_Com_TaskCreate()
{
	OS_ERR err;
	
	OSTaskCreate((OS_TCB *			)&ComTaskTcb, 
				 (CPU_CHAR *		)"App_Com_Task", 
				 (OS_TASK_PTR		)App_Com_Task,
				 (void *			)0,
				 (OS_PRIO			)APP_COM_TASK_PRIO,
				 (CPU_STK *			)&App_Com_Task_Stk[0],
				 (CPU_STK_SIZE		)APP_COM_STK_SIZE / 10,
				 (CPU_STK_SIZE		)APP_COM_STK_SIZE,
				 (OS_MSG_QTY		)0,
				 (OS_TICK			)0,
				 (void *			)0,
				 (OS_OPT			)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
				 (OS_ERR *			)&err);
}





