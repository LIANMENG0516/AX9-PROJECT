#include "command_process.h"

extern System_MsgStruct System_MsgStr;

extern Com_Buffer DebugComRX;
extern Com_Buffer DebugComTX;

extern Com_Buffer CommuComRX;
extern Com_Buffer CommuComTX;

uint8_t DateStr[11] = __DATE__;
uint8_t TimeStr[8]  = __TIME__;

static uint8_t	RcvDataCmd[100];
static CmdFrameStr RcvFrameCmd = {0x68, 0x04, 0x00, 0x00, (uint8_t *)RcvDataCmd, 0x00, 0x16};

static uint8_t	SenDataCmd[100];
static CmdFrameStr SenFrameCmd = {0x68, 0x04, 0x00, 0x00, (uint8_t *)SenDataCmd, 0x00, 0x16};

void Get_FireWare_Version()
{
    SenFrameCmd.Cid = CMD_FW_VERSION;
    SenFrameCmd.Len = 1;
	SenFrameCmd.Data[0] = FW_VERSION;
}

void Get_Compile_Info()
{
    SenFrameCmd.Len = sizeof(DateStr) + sizeof(TimeStr);
	
	memcpy(&SenFrameCmd.Data[0], DateStr, 11);
	memcpy(&SenFrameCmd.Data[11], TimeStr, 8);
}

void Get_AdjHv_Msg()
{
    System_MsgStr.AdVolStr.CMD_HVFlag = TRUE;
    
    System_MsgStr.AdVolStr.T_VPP1 = (RcvFrameCmd.Data[0] << 8) | RcvFrameCmd.Data[1];
    System_MsgStr.AdVolStr.T_VNN1 = (RcvFrameCmd.Data[2] << 8) | RcvFrameCmd.Data[3];
    System_MsgStr.AdVolStr.T_VPP2 = (RcvFrameCmd.Data[4] << 8) | RcvFrameCmd.Data[5];
    System_MsgStr.AdVolStr.T_VPP2 = (RcvFrameCmd.Data[6] << 8) | RcvFrameCmd.Data[7];
}

void Get_AdjCw_Msg()
{
    System_MsgStr.AdVolStr.CMD_CWFlag = TRUE;
    
    System_MsgStr.AdVolStr.T_VPP1 = (RcvFrameCmd.Data[0] << 8) | RcvFrameCmd.Data[1];
    System_MsgStr.AdVolStr.T_VNN1 = (RcvFrameCmd.Data[2] << 8) | RcvFrameCmd.Data[3];
    System_MsgStr.AdVolStr.T_PCW  = (RcvFrameCmd.Data[4] << 8) | RcvFrameCmd.Data[5];
    System_MsgStr.AdVolStr.T_NCW  = (RcvFrameCmd.Data[6] << 8) | RcvFrameCmd.Data[7];
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



























































































