#include "adjustvoltage.h"

#include "gouble.h"

extern System_MsgStruct System_MsgStr;

uint16_t Vppx_Calculate_AdjVol(uint16_t T_Data)
{
    double Adjvol;
    uint16_t Dac_Val;
    
    Adjvol = 2.069 - T_Data / 43.2;                                  //(1/43.2+1/3.48+1)*1.6=2.096
    Dac_Val = (int)((Adjvol / 3.3 * 4095) + 0.5);
    
    return Dac_Val;
}

uint16_t Vnnx_Calculate_AdjVol(uint16_t T_Data)
{
    double Adjvol, Abs_Adjvol;
    uint16_t Dac_Val;
    
    Adjvol = T_Data * 0.02 - 2.1;    

    Abs_Adjvol = fabs(Adjvol);
    
    Dac_Val = (int)((Abs_Adjvol / 2.048 * 255) + 0.5);               //四舍五入后取整数
    
    return Dac_Val;
}

uint16_t Pcw_Calculate_AdjVol(uint16_t T_Data)
{
    return 0;
}

uint16_t Ncw_Calculate_AdjVol(uint16_t T_Data)
{
    return 0;
}

void Adjust_Voltage_Vpp1(uint16_t T_Vpp1)
{
    uint16_t Dac_Val;
    
    Dac_Val = Vppx_Calculate_AdjVol(T_Vpp1);                         //计算要调节到目标值时HVADJ1的值
    DAC_SetChannel1Data(DAC_Align_12b_R, Dac_Val);                   //调节VPP1至目标值
    DAC_SoftwareTriggerCmd(DAC_Channel_1, ENABLE);                   //软件触发DAC转换
}

void Adjust_Voltage_Vpp2(uint16_t T_Vpp2)
{
    uint16_t Dac_Val;
    
    Dac_Val = Vppx_Calculate_AdjVol(T_Vpp2);                         //计算要调节到目标值时HVADJ3的值
    DAC_SetChannel1Data(DAC_Align_12b_R, Dac_Val);                   //调节VPP2至目标值
    DAC_SoftwareTriggerCmd(DAC_Channel_2, ENABLE);                   //软件触发DAC转换
}

void Adjust_Voltage_Vnn1(uint16_t T_Vnn1)                                           
{
    uint16_t Dac_Val;
    Dac_Val = Vnnx_Calculate_AdjVol(T_Vnn1);                         //计算要调节到目标值时HVADJ2的值
    DacHv_Tlv5626cd_ValueSet(TLV5626CD_A, Dac_Val);
}

void Adjust_Voltage_Vnn2(uint16_t T_Vnn2)
{
    uint16_t Dac_Val;
    Dac_Val = Vnnx_Calculate_AdjVol(T_Vnn2);                         //计算要调节到目标值时HVADJ4的值
    DacHv_Tlv5626cd_ValueSet(TLV5626CD_B, Dac_Val);
}


void Adjust_Voltage_Pcw(uint16_t T_Pcw)
{
    uint16_t Dac_Val;
    Dac_Val = Pcw_Calculate_AdjVol(T_Pcw);                           //计算要调节到目标值时HVADJ5的值
    DacCw_Tlv5626cd_ValueSet(TLV5626CD_B, Dac_Val);
}

void Adjust_Voltage_Ncw(uint16_t T_Ncw)
{
    uint16_t Dac_Val;
    Dac_Val = Ncw_Calculate_AdjVol(T_Ncw);                           //计算要调节到目标值时HVADJ6的值
    DacCw_Tlv5626cd_ValueSet(TLV5626CD_B, Dac_Val);
}


void Adjust_Voltage_HV()    //高压调压处理流程
{   
    if(System_MsgStr.AdVolStr.T_VPP1 > HIGHSET_HV1 && System_MsgStr.AdVolStr.T_VPP1 < LOOWSET_HV1 &&
       System_MsgStr.AdVolStr.T_VNN1 > HIGHSET_HV1 && System_MsgStr.AdVolStr.T_VNN1 < LOOWSET_HV1 && 
       System_MsgStr.AdVolStr.T_VPP2 > HIGHSET_HV2 && System_MsgStr.AdVolStr.T_VPP2 < LOOWSET_HV2 && 
       System_MsgStr.AdVolStr.T_VNN2 > HIGHSET_HV2 && System_MsgStr.AdVolStr.T_VNN2 < LOOWSET_HV2  )
    {
        Adjust_Voltage_Vpp1(System_MsgStr.AdVolStr.T_VPP1);             //调节VPP1至目标值
        Adjust_Voltage_Vnn1(System_MsgStr.AdVolStr.T_VNN1);
        
        Adjust_Voltage_Vpp2(System_MsgStr.AdVolStr.T_VPP2);             //调节VPP2至目标值
        Adjust_Voltage_Vnn2(System_MsgStr.AdVolStr.T_VNN2);
    }
}

void Adjust_Voltage_CW()    //低压调压处理流程
{
    if(System_MsgStr.AdVolStr.T_VPP1 > HIGHSET_HV1 && System_MsgStr.AdVolStr.T_VPP1 < LOOWSET_HV1 &&
       System_MsgStr.AdVolStr.T_VNN1 > HIGHSET_HV1 && System_MsgStr.AdVolStr.T_VNN1 < LOOWSET_HV1 && 
       System_MsgStr.AdVolStr.T_PCW  > HIGHSET_CW  && System_MsgStr.AdVolStr.T_PCW  < LOOWSET_CW  && 
       System_MsgStr.AdVolStr.T_NCW  > HIGHSET_CW  && System_MsgStr.AdVolStr.T_NCW  < LOOWSET_CW   )
    {
        
        Adjust_Voltage_Vpp1(System_MsgStr.AdVolStr.T_VPP1);             //调节VPP1至目标值
        Adjust_Voltage_Vnn1(System_MsgStr.AdVolStr.T_VNN1);             //调节VNN1至目标值
        
        Adjust_Voltage_Pcw(System_MsgStr.AdVolStr.T_PCW);               //调节PCW至目标值
        Adjust_Voltage_Pcw(System_MsgStr.AdVolStr.T_NCW);               //调节NCW至目标值
    }
}




