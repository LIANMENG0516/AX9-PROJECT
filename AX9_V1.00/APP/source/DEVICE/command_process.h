#ifndef __COMMAND_PROCESS_H
#define __COMMAND_PROCESS_H

#include "gouble.h"

typedef struct 
{
	uint8_t		Header;
	uint8_t		Id;
	uint8_t		Cid;
	uint8_t 	Len;
	uint8_t 	*Data;
	uint8_t		Chk;
	uint8_t 	Tail;
}CmdFrameStr;


#define FW_VERSION  0x00




#define CMD_FW_VERSION      0x00
#define CHK_COMPILE_INFO    0x01

#define CMD_ADJUST_HV       0x02
#define CMD_ADJUST_CW       0x03






#define INVALID_CMD         0xFF        //�Ƿ�����

void FrameCmdPackage(uint8_t *pBuf);
void Send_CmdPackage(DMA_Stream_TypeDef* DMAy_Streamx);
void Cmd_Process(void);

ErrorStatus ReceiveFrameAnalysis(uint8_t *pData, uint8_t DataLen);

#endif











