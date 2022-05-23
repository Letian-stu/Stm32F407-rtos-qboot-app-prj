/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-05-17     armink       the first version
 */

#ifndef _FAL_CFG_H_
#define _FAL_CFG_H_

#include <rtconfig.h>
#include <board.h>

#define NOR_FLASH_DEV_NAME             "w25q16"

/* ===================== Flash device Configuration ========================= */
extern const struct fal_flash_dev stm32_onchip_flash;
/* ===================== Flash device Configuration ========================= */
extern struct fal_flash_dev nor_flash0;

/* flash device table */
#define FAL_FLASH_DEV_TABLE                                          \
{                                                                    \
    &stm32_onchip_flash,                                             \
    &nor_flash0,                                                     \
}

/* ====================== Partition Configuration ========================== */
#ifdef FAL_PART_HAS_TABLE_CFG
/* partition table */
#define FAL_PART_TABLE                                                                  \
{                                                                                       \
    /*                           name               dev        开始地址      大小    0 */          \
    {FAL_PART_MAGIC_WORD,      "qboot",           "onchip_flash",                      0,   128*1024, 0}, \
    {FAL_PART_MAGIC_WORD,        "app",           "onchip_flash",               128*1024,   445*1024, 0}, \
    {FAL_PART_MAGIC_WORD,    "factory",           "onchip_flash",         (128+448)*1024,   445*1024, 0}, \
    {FAL_PART_MAGIC_WORD, "filesystem",       NOR_FLASH_DEV_NAME,                      0,  1020*1024, 0}, \
    {FAL_PART_MAGIC_WORD,   "download",       NOR_FLASH_DEV_NAME,              1024*1024,   510*1024, 0}, \
    {FAL_PART_MAGIC_WORD,  "easyflash",       NOR_FLASH_DEV_NAME,        (1024+512)*1024,   510*1024, 0}, \
}
#endif /* FAL_PART_HAS_TABLE_CFG */

#endif /* _FAL_CFG_H_ */

