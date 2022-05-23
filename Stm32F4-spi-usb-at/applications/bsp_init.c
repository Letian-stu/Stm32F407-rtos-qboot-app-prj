/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-21     tian       the first version
 */
#include <rtthread.h>
#include "fal.h"
#include "drv_spi.h"
#include "dfs_fs.h"
#include "spi_flash_sfud.h"
#include "bsp_init.h"

#define DBG_TAG "INIT"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/*app version*/
#define version "V1.0.1"

/*app partition begin address*/
#define RT_APP_PART_ADDR    0x08020000

static int ota_app_vtor_reconfig(void)
{
    #define NVIC_VTOR_MASK   0x3FFFFF80
    /* Set the Vector Table base location by user application firmware definition */
    SCB->VTOR = RT_APP_PART_ADDR & NVIC_VTOR_MASK;

    return 0;
}
INIT_BOARD_EXPORT(ota_app_vtor_reconfig);

//挂载spi
int rt_hw_spi_flash_init(void)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();
    rt_hw_spi_device_attach("spi1", "spi10", GPIOB, GPIO_PIN_14);

    if (RT_NULL == rt_sfud_flash_probe("w25q16", "spi10"))
    {
        return -RT_ERROR;
    }
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_spi_flash_init);

int mnt_init(void)
{
    fal_init();                                             // 这个函数只能调用一次，这里调用了其他地方就不能用
    LOG_I("*************************");
    LOG_I("The app version is %s",version);
    LOG_I("*************************");
    fal_blk_device_create("filesystem");                    // 注意调用该函数前必须要先调用fal_init函数初始化
    if (dfs_mount("filesystem", "/", "elm", 0, 0) == 0)     // "filesystem":挂载的分区名称，"/":挂载路径，这里挂载到跟目录下
    {
        LOG_I("filesystem mount successful!");
    }
    else
    {
        dfs_mkfs("elm", "filesystem");                      // 如果是第一次挂载文件系统必须要先格式化
        if(dfs_mount("filesystem", "/", "elm", 0, 0) != 0)
        {
            LOG_I("filesystem mount failed!");
        }
        else
        {
            LOG_I("filesystem mount success!");
        }
    }

    return 0;
}
INIT_ENV_EXPORT(mnt_init);

void fs_unmount(void)
{
    if(rt_device_find("filesystem") != RT_NULL)
    {
        if(dfs_unmount("/") == 0)
        {
            rt_kprintf("filesystem unmount success!\n");
        }
        else
        {
            rt_kprintf("filesystem unmount failed!\n");
        }
    }
}
MSH_CMD_EXPORT(fs_unmount, fs_unmount sample);


void fs_mount(void)
{
    if(rt_device_find("filesystem") != RT_NULL)
    {
        if(dfs_mount("filesystem","/","elm",0,0)==0)
        {
            rt_kprintf("filesystem mount success!\n");
        }
        else
        {
            rt_kprintf("filesystem mount failed!\n");
        }
    }
}
MSH_CMD_EXPORT(fs_mount, fs_mount sample);
