#include "adjustvoltage.h"

#include "gouble.h"

extern System_MsgStruct SysMsg;

uint16_t Vppx_Calculate_AdjVol(uint16_t T_Data)
{
    double Adjvol;
    uint16_t Dac_Val;
    
    Adjvol = 2.096 - T_Data / 100 / 43.2;                                  //(1/43.2+1/3.48+1)*1.6=2.096
    Dac_Val = (int)((Adjvol / 3.3 * 4095)+ 0.5);
    
    return Dac_Val;
}

uint16_t Vnnx_Calculate_AdjVol(uint16_t T_Data)
{
    double Adjvol;
    uint16_t Dac_Val;
    
    Adjvol = 2.098 - 0.023 * T_Data / 100;    
    
    Dac_Val = ((int)(Adjvol * 4096 / 2.048)) >> 4;               //���������ȡ����
    
    return Dac_Val;
}

uint16_t Pcw_Calculate_AdjVol(uint16_t T_Data)
{
    uint16_t Dac_Val;
    
    Dac_Val = 259 - 26.4 * T_Data / 100;
    
    return Dac_Val;
}

uint16_t Ncw_Calculate_AdjVol(uint16_t T_Data)
{
    uint16_t Dac_Val;
    
    Dac_Val = 274 - 26.4 * T_Data / 100;    
    
    return Dac_Val;
}

void Adjust_Voltage_Vpp1(uint16_t T_Vpp1)
{
    uint16_t Dac_Val;
    
    Dac_Val = Vppx_Calculate_AdjVol(T_Vpp1);                         //����Ҫ���ڵ�Ŀ��ֵʱHVADJ1��ֵ
    DAC_SetChannel1Data(DAC_Align_12b_R, Dac_Val);                   //����VPP1��Ŀ��ֵ
    DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);                   //�������DACת��
}

void Adjust_Voltage_Vpp2(uint16_t T_Vpp2)
{
    uint16_t Dac_Val;
    
    Dac_Val = Vppx_Calculate_AdjVol(T_Vpp2);                         //����Ҫ���ڵ�Ŀ��ֵʱHVADJ3��ֵ
    DAC_SetChannel2Data(DAC_Align_12b_R, Dac_Val);                   //����VPP2��Ŀ��ֵ
    DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);                   //�������DACת��
}

void Adjust_Voltage_Vnn1_Vnn2(uint16_t T_Vnn1, uint16_t T_Vnn2)                                           
{
    uint16_t Dac_ValA, Dac_ValB;
    
    Dac_ValA = Vnnx_Calculate_AdjVol(T_Vnn1);
    Dac_ValB = Vnnx_Calculate_AdjVol(T_Vnn2);
    DacHv_Tlv5626cd_ValueSet(Dac_ValA, Dac_ValB);
}

void Adjust_Voltage_Pcw(uint16_t T_Pcw)
{
    uint16_t Dac_Val;
    Dac_Val = Pcw_Calculate_AdjVol(T_Pcw);                           //����Ҫ���ڵ�Ŀ��ֵʱHVADJ5��ֵ
    DacCw_Tlv5626cd_ValueSet(TLV5626CD_A, Dac_Val);
}

void Adjust_Voltage_Ncw(uint16_t T_Ncw)
{
    uint16_t Dac_Val;
    Dac_Val = Ncw_Calculate_AdjVol(T_Ncw);                           //����Ҫ���ڵ�Ŀ��ֵʱHVADJ6��ֵ
    DacCw_Tlv5626cd_ValueSet(TLV5626CD_B, Dac_Val);
}


void Adjust_Voltage_HV()    //��ѹ��ѹ��������
{       
    if(SysMsg.AdjVol.T_VPP1 <= HIGHSET_HV1 && SysMsg.AdjVol.T_VPP1 >= LOOWSET_HV1 &&
       SysMsg.AdjVol.T_VNN1 <= HIGHSET_HV1 && SysMsg.AdjVol.T_VNN1 >= LOOWSET_HV1 && 
       SysMsg.AdjVol.T_VPP2 <= HIGHSET_HV2 && SysMsg.AdjVol.T_VPP2 >= LOOWSET_HV2 && 
       SysMsg.AdjVol.T_VNN2 <= HIGHSET_HV2 && SysMsg.AdjVol.T_VNN2 >= LOOWSET_HV2  )
    {
        CTL_VPP1_VNN1_EN(0);                                    //�رո�ѹ���
        CTL_VPP2_VNN2_EN(0);
        
        Adjust_Voltage_Vpp1(SysMsg.AdjVol.T_VPP1);                                  //����VPP1��Ŀ��ֵ
        Adjust_Voltage_Vpp2(SysMsg.AdjVol.T_VPP2);                                  //����VPP2��Ŀ��ֵ
        Adjust_Voltage_Vnn1_Vnn2(SysMsg.AdjVol.T_VNN1, SysMsg.AdjVol.T_VNN2);       //����VNN1, VNN2��Ŀ��ֵ
        
        CTL_VPP1_VNN1_EN(1);                                    //�򿪸�ѹ���
        CTL_VPP2_VNN2_EN(1);
    }
}

void Adjust_Voltage_CW()    //��ѹ��ѹ��������
{
    if(SysMsg.AdjVol.T_VPP1 > HIGHSET_HV1 && SysMsg.AdjVol.T_VPP1 < LOOWSET_HV1 &&
       SysMsg.AdjVol.T_VNN1 > HIGHSET_HV1 && SysMsg.AdjVol.T_VNN1 < LOOWSET_HV1 && 
       SysMsg.AdjVol.T_VPP2 > HIGHSET_CW  && SysMsg.AdjVol.T_VPP2 < LOOWSET_CW  && 
       SysMsg.AdjVol.T_VNN2 > HIGHSET_CW  && SysMsg.AdjVol.T_VNN2 < LOOWSET_CW   )
    {
        
        Adjust_Voltage_Vpp1(SysMsg.AdjVol.T_VPP1);                                  //����VPP1��Ŀ��ֵ
        Adjust_Voltage_Vnn1_Vnn2(SysMsg.AdjVol.T_VNN1, SysMsg.AdjVol.T_VNN2);       //����VNN1, VNN2��Ŀ��ֵ
        
        Adjust_Voltage_Pcw(SysMsg.AdjVol.T_VPP2);              //����PCW��Ŀ��ֵ
        Adjust_Voltage_Pcw(SysMsg.AdjVol.T_VNN2);              //����NCW��Ŀ��ֵ
    }
}




