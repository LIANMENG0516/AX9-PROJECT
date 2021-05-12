#include "power.h"

extern System_MsgStruct SysMsg;

void Power_Insert()
{
    SysMsg.PwrInfo.Ac_Insert = AC_INSERT_CHK() ? TRUE : FALSE;
    SysMsg.PwrInfo.Bat1_Insert = BAT1_INSERT_CHK() ? FALSE : TRUE;
    SysMsg.PwrInfo.Bat2_Insert = BAT2_INSERT_CHK() ? FALSE : TRUE;
}

uint8_t CheckBatteryState()
{
    uint8_t batState;
    
    batState = (BAT_STAT1() << 1) + BAT_STAT2();
    
    return batState;
}

void Battery_Power_Read()
{
    uint8_t batState;
    
    static bool bat1_NeedCharge = TRUE, bat2_NeedCharge = TRUE;
    static uint16_t bat1ChargeRecoverCnt = 0, bat2ChargeRecoverCnt = 0;
    
    Power_Insert();
    Bat1_PowerRead();
    Bat2_PowerRead();
    batState = CheckBatteryState();
    
    if(SysMsg.PwrInfo.Ac_Insert == TRUE)
    {
        if(SysMsg.PwrInfo.Bat1_Insert == TRUE && bat1_NeedCharge == TRUE)
        {
            if(SysMsg.PwrInfo.Bat1_Power == 100)
            {
                if(batState == BAT_STATE_FULL || batState == BAT_STATE_ERROR)
                {
                    CHARGE_CTL(0);
                    CHARGE_EN(0);
                    BAT1_C_SHIFT_EN(0);
                    bat1_NeedCharge = FALSE;
                    SysMsg.PwrInfo.Bat1_Err = FALSE;
                }
            }
            else if(SysMsg.PwrInfo.Bat1_Power != 100 && batState == BAT_STATE_ERROR)
            {
                if(++bat1ChargeRecoverCnt >= 100)
                {
                    CHARGE_CTL(0);
                    CHARGE_EN(0);
                    BAT1_C_SHIFT_EN(0);
                    bat1_NeedCharge = FALSE;
                    SysMsg.PwrInfo.Bat1_Err = TRUE;
                }
                else
                {
                    if(SysMsg.SystemState == SYSTEM_ON)
                    {
                        CHARGE_CTL(0);
                    }
                    else
                    {
                        CHARGE_CTL(1);
                    }
                    CHARGE_EN(1);
                    BAT1_C_SHIFT_EN(1);
                    bat1_NeedCharge = TRUE;
                    SysMsg.PwrInfo.Bat1_Err = FALSE;
                }
            }
            else if(SysMsg.PwrInfo.Bat1_Power != 100 && batState == BAT_STATE_CHARGE)
            {
                if(SysMsg.SystemState == SYSTEM_ON)
                {
                    CHARGE_CTL(0);
                }
                else
                {
                    CHARGE_CTL(1);
                }
                CHARGE_EN(1);
                BAT1_C_SHIFT_EN(1);
                bat1_NeedCharge = TRUE;
                SysMsg.PwrInfo.Bat1_Err = FALSE;
            }
            else
            {
                CHARGE_CTL(0);
                CHARGE_EN(0);
                BAT1_C_SHIFT_EN(0);
                bat1_NeedCharge = FALSE;
                SysMsg.PwrInfo.Bat1_Err = FALSE;
            }
        }
        else if(SysMsg.PwrInfo.Bat2_Insert == TRUE && bat2_NeedCharge == TRUE)
        {
            if(SysMsg.PwrInfo.Bat2_Power == 100)
            {
                if(batState == BAT_STATE_FULL || batState == BAT_STATE_ERROR)
                {
                    CHARGE_CTL(0);
                    CHARGE_EN(0);
                    BAT2_C_SHIFT_EN(0);
                    SysMsg.PwrInfo.Bat2_Err = FALSE;
                    bat2_NeedCharge = FALSE;
                }
            }
            else if(SysMsg.PwrInfo.Bat1_Power != 100 && batState == BAT_STATE_ERROR)
            {
                if(++bat2ChargeRecoverCnt >= 100)
                {
                    CHARGE_CTL(0);
                    CHARGE_EN(0);
                    BAT2_C_SHIFT_EN(0);
                    SysMsg.PwrInfo.Bat2_Err = TRUE;
                    bat2_NeedCharge = FALSE;
                }
                else
                {
                    if(SysMsg.SystemState == SYSTEM_ON)
                    {
                        CHARGE_CTL(0);
                    }
                    else
                    {
                        CHARGE_CTL(1);
                    }
                    CHARGE_EN(1);
                    BAT2_C_SHIFT_EN(1);
                    SysMsg.PwrInfo.Bat2_Err = FALSE;
                    bat2_NeedCharge = TRUE;
                }
            }
            else if(SysMsg.PwrInfo.Bat2_Power != 100 && batState == BAT_STATE_CHARGE)
            {
                if(SysMsg.SystemState == SYSTEM_ON)
                {
                    CHARGE_CTL(0);
                }
                else
                {
                    CHARGE_CTL(1);
                }
                CHARGE_EN(1);
                BAT2_C_SHIFT_EN(1);
                SysMsg.PwrInfo.Bat2_Err = FALSE;
                bat2_NeedCharge = TRUE;
            }
            else
            {
                CHARGE_CTL(0);
                CHARGE_EN(0);
                BAT2_C_SHIFT_EN(0);
                SysMsg.PwrInfo.Bat2_Err = FALSE;
                bat2_NeedCharge = FALSE;
            }
        }
        else
        {
            CHARGE_CTL(0);
            CHARGE_EN(0);
            BAT1_C_SHIFT_EN(0);
            BAT2_C_SHIFT_EN(0);
            bat1_NeedCharge = FALSE;
            bat2_NeedCharge = FALSE;
            SysMsg.PwrInfo.Bat1_Err = FALSE;
            SysMsg.PwrInfo.Bat2_Err = FALSE;
            
        }
    }
}


















