#include "command_process.h"

extern System_MsgStruct SysMsg;

extern Com_Buffer DebugComRX;
extern Com_Buffer DebugComTX;

extern Com_Buffer CommuComRX;
extern Com_Buffer CommuComTX;

uint8_t	RcvDataCmd[100];
CmdFrameStr RcvFrameCmd = {0x68, 0x04, 0x00, 0x00, (uint8_t *)RcvDataCmd, 0x00, 0x16};

uint8_t	SenDataCmd[100];
CmdFrameStr SenFrameCmd = {0x68, 0x04, 0x00, 0x00, (uint8_t *)SenDataCmd, 0x00, 0x16};

void Get_FireWare_Version()
{
    SysMsg.Cmd.Firmware_Send = TRUE;
}

void Get_Compile_Info()
{
     SysMsg.Cmd.CompileInfo_Send = TRUE;
}

void Calc_TarVol_AlowRange()
{    
    SysMsg.AdjVol.MAX_VPP1 = SysMsg.AdjVol.T_VPP1 + 150;
    SysMsg.AdjVol.MIN_VPP1 = SysMsg.AdjVol.T_VPP1 - 150;
    SysMsg.AdjVol.MAX_VNN1 = SysMsg.AdjVol.T_VPP1 + 150;
    SysMsg.AdjVol.MIN_VNN1 = SysMsg.AdjVol.T_VPP1 - 150;
    
    if(SysMsg.AdjVol.Adj_HV == TRUE)
    {
        SysMsg.AdjVol.Adj_HV = FALSE;
        
        SysMsg.AdjVol.MAX_VPP2 = SysMsg.AdjVol.T_VPP2 + 150;
        SysMsg.AdjVol.MIN_VPP2 = SysMsg.AdjVol.T_VPP2 - 150;
        SysMsg.AdjVol.MAX_VNN2 = SysMsg.AdjVol.T_VPP2 + 150;
        SysMsg.AdjVol.MIN_VNN2 = SysMsg.AdjVol.T_VPP2 - 150;
    }
    
    if(SysMsg.AdjVol.Adj_CW == TRUE)
    {
        SysMsg.AdjVol.Adj_CW = FALSE;
        
        SysMsg.AdjVol.MAX_VPP2 = SysMsg.AdjVol.T_VPP2 + 100;
        SysMsg.AdjVol.MIN_VPP2 = SysMsg.AdjVol.T_VPP2 - 100;
        SysMsg.AdjVol.MAX_VNN2 = SysMsg.AdjVol.T_VPP2 + 100;
        SysMsg.AdjVol.MIN_VNN2 = SysMsg.AdjVol.T_VPP2 - 100;
    }
}

void Get_AdjHv_Msg()
{
    SysMsg.AdjVol.T_VPP1 = (RcvFrameCmd.Data[0] << 8) | RcvFrameCmd.Data[1];
    SysMsg.AdjVol.T_VNN1 = (RcvFrameCmd.Data[2] << 8) | RcvFrameCmd.Data[3];
    SysMsg.AdjVol.T_VPP2 = (RcvFrameCmd.Data[4] << 8) | RcvFrameCmd.Data[5];
    SysMsg.AdjVol.T_VNN2 = (RcvFrameCmd.Data[6] << 8) | RcvFrameCmd.Data[7];
    
    SysMsg.AdjVol.Adj_HV = TRUE;
    Calc_TarVol_AlowRange();                                    //计算允许误差范围
    Adjust_Voltage_HV();                                        //执行高压调压处理
    SysMsg.AdjVol.HV_Minitor = TRUE;                            //处理完成打开高压监控 
}

void Get_AdjCw_Msg()
{
    SysMsg.AdjVol.T_VPP1 = (RcvFrameCmd.Data[0] << 8) | RcvFrameCmd.Data[1];
    SysMsg.AdjVol.T_VNN1 = (RcvFrameCmd.Data[2] << 8) | RcvFrameCmd.Data[3];
    SysMsg.AdjVol.T_VPP2 = (RcvFrameCmd.Data[4] << 8) | RcvFrameCmd.Data[5];
    SysMsg.AdjVol.T_VNN2 = (RcvFrameCmd.Data[6] << 8) | RcvFrameCmd.Data[7];
    
    SysMsg.AdjVol.Adj_CW = TRUE;
    Calc_TarVol_AlowRange(); 
    Adjust_Voltage_CW();                            //执行低压调压处理
    SysMsg.AdjVol.CW_Minitor= TRUE;       //处理完成打开低压监控
}

void InValid_CidData()
{
	SenFrameCmd.Len = 1;
	SenFrameCmd.Data[0] = INVALID_CMD;
}

void FrameCmdPackage(uint8_t *pBuf)	//数据打包
{
	uint8_t i = 0;

	SenFrameCmd.Chk = SenFrameCmd.Id + SenFrameCmd.Cid + SenFrameCmd.Len;
	
	for(i=0; i<SenFrameCmd.Len; i++)
	{
		SenFrameCmd.Chk += SenFrameCmd.Data[i];
	}

	pBuf[0] = SenFrameCmd.Header;
	pBuf[1] = SenFrameCmd.Id;
	pBuf[2] = SenFrameCmd.Cid;
	pBuf[3] = SenFrameCmd.Len;
    for(int i=0; i<SenFrameCmd.Len; i++)
	{
		pBuf[4 + i] = SenFrameCmd.Data[i];
	}
    
	pBuf[SenFrameCmd.Len + 6 - 2] = SenFrameCmd.Chk;
	pBuf[SenFrameCmd.Len + 6 - 1] = SenFrameCmd.Tail;
}

void Send_CmdPackage(DMA_Stream_TypeDef* DMAy_Streamx)	//发送已经打包好的命令
{
	DMA_SetCurrDataCounter(DMAy_Streamx, SenFrameCmd.Len + 6);	
	DMA_Cmd(DMAy_Streamx, ENABLE);
}

ErrorStatus ReceiveFrameAnalysis(uint8_t *pData, uint8_t DataLen)
{
    uint8_t CmdCrc = 0;
    
	RcvFrameCmd.Header 		= 	*pData++;
	RcvFrameCmd.Id 			= 	*pData++;
	RcvFrameCmd.Cid 		= 	*pData++;
	RcvFrameCmd.Len 		= 	*pData++;
	for(int i=0; i<(DataLen-6); i++)
	{
		RcvFrameCmd.Data[i] = 	*pData++;
	}
	RcvFrameCmd.Chk 		= 	*pData++;
	RcvFrameCmd.Tail 		= 	*pData;
    
    
    CmdCrc += RcvFrameCmd.Id;
    CmdCrc += RcvFrameCmd.Cid;
    CmdCrc += RcvFrameCmd.Len;
    
    for(int i=0; i<RcvFrameCmd.Len; i++)
    {
        CmdCrc += RcvFrameCmd.Data[i];
    }
    
    if(RcvFrameCmd.Header == 0x68 && RcvFrameCmd.Id == 0x04 && RcvFrameCmd.Tail == 0x16 && CmdCrc == RcvFrameCmd.Chk)
    {
        return SUCCESS;
    }  

    return ERROR;
}

void Cmd_Process()
{
    switch(RcvFrameCmd.Cid)
    {
        case    CMD_FW_VERSION:
                Get_FireWare_Version();
                break;
        
        case    CHK_COMPILE_INFO:
                Get_Compile_Info();
                break;

        case    CMD_ADJUST_HV:
                Get_AdjHv_Msg();
                break;
        
        case    CMD_ADJUST_CW:
                Get_AdjCw_Msg();
                break;
        
        
        default:
                InValid_CidData();
                break;
    } 
}



























































































