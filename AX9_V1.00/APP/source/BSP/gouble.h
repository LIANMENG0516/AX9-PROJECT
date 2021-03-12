#ifndef __GOUBLE_H
#define __GOUBLE_H

#include "stdlib.h"
#include "stdio.h"
#include "math.h"

#include "gpio.h"
#include "nvic.h"
#include "systick.h"
#include "usart.h"
#include "dma.h"
#include "spi.h"
#include "dac.h"
#include "adc.h"

#include "board.h"
#include "system.h"
#include "tmp468.h"
#include "adt7302.h"
#include "emc2305.h"
#include "tlv5626cd.h"
#include "adjustvoltage.h"
#include "command_process.h"

#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usbd_cdc_vcp.h"

#include "includes.h"
#include "os_cfg_app.h"
#include "os.h"

#include "app.h"
#include "app_led.h"
#include "app_fan.h"
#include "app_usb.h"
#include "app_timer.h"
#include "app_adjvol.h"

#define USE_UCOSIII

#define APP_START_TASK_PRIO 				3		//优先级
#define APP_START_STK_SIZE 					256		//堆栈大小

#define APP_LED_TASK_PRIO 					4
#define APP_LED_STK_SIZE 					256

#define APP_USB_TASK_PRIO 					5
#define APP_USB_STK_SIZE 					256

#define APP_AdjVol_TASK_PRIO                6
#define APP_ADJVOL_STK_SIZE                 256

#define APP_COM_TASK_PRIO                   7
#define APP_COM_STK_SIZE                    256

#define APP_FAN_TASK_PRIO                   8
#define APP_FAN_STK_SIZE                    256

#endif
