/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-21     RT-Thread    first version
 */

#include <rtthread.h>
#include "stm32f4xx_hal.h"


#define DBG_TAG "main"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

int F4_clock_information(void)
{
    LOG_I("System Clock information");
    LOG_I("SYSCLK_Frequency = %d", HAL_RCC_GetSysClockFreq());
    LOG_I("HCLK_Frequency   = %d", HAL_RCC_GetHCLKFreq());
    LOG_I("PCLK1_Frequency  = %d", HAL_RCC_GetPCLK1Freq());
    LOG_I("PCLK2_Frequency  = %d", HAL_RCC_GetPCLK2Freq());
    return RT_EOK;
}
INIT_DEVICE_EXPORT(F4_clock_information);

int main(void)
{
    while (1)
    {
        rt_thread_mdelay(1000);
    }

    return RT_EOK;
}
