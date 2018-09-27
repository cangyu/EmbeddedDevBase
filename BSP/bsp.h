#ifndef __BSP_H__
#define __BSP_H__

#ifdef __cplusplus
extern "C" {
#endif
  
#include <stdio.h>
#include <stdint.h>
#include "stm32f10x.h"
#include "bsp_sdio_sdcard.h"

void BSP_LED_SetOn(uint8_t idx);
void BSP_LED_SetOff(uint8_t idx);

void BSP_Init(void);

#ifdef __cplusplus
}
#endif

#endif
