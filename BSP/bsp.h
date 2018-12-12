#ifndef __BSP_H__
#define __BSP_H__

#ifdef __cplusplus
extern "C" {
#endif
  
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_w25qxx.h"
#include "bsp_ble.h"
#include "bsp_btn.h"

void BSP_DLY_MS(uint32_t n);
void BSP_Init(void);

#ifdef __cplusplus
}
#endif

#endif
