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
#include "bsp_w25qxx.h"
  
#define LED1_GPIO GPIOB
#define LED1_PIN GPIO_Pin_5
#define LED2_GPIO GPIOE
#define LED2_PIN GPIO_Pin_5


void BSP_DLY_MS(uint32_t n);
void BSP_LED_SetOn(uint8_t idx);
void BSP_LED_SetOff(uint8_t idx);
void BSP_LED_Toggle(uint8_t idx);
void BSP_Init(void);

#ifdef __cplusplus
}
#endif

#endif
