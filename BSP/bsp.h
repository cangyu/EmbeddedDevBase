#ifndef __BSP_H__
#define __BSP_H__

#ifdef __cplusplus
extern "C" {
#endif
  
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "ff.h"
#include "stm32f10x.h"
#include "bsp_sdcard.h"

extern FATFS *BSP_FS_SD, *BSP_FS_W25QXX;
  
void BSP_LED_SetOn(uint8_t idx);
void BSP_LED_SetOff(uint8_t idx);
bool BSP_SD_IsAvailable(void);
bool BSP_W25QXX_IsAvailable(void);
void BSP_Init(void);

#ifdef __cplusplus
}
#endif

#endif
