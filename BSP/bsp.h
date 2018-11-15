#ifndef __BSP_H__
#define __BSP_H__

#ifdef __cplusplus
extern "C" {
#endif
  
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f10x.h"
  
#define LED1_GPIO GPIOB
#define LED1_PIN GPIO_Pin_5
#define LED2_GPIO GPIOE
#define LED2_PIN GPIO_Pin_5

extern volatile uint32_t BSP_DLY_COUNTER;

void BSP_DLY_MS(uint32_t n);
void BSP_LED_SetOn(uint8_t idx);
void BSP_LED_SetOff(uint8_t idx);
void BSP_LED_Toggle(uint8_t idx);
void BSP_Init(void);

#ifdef __cplusplus
}
#endif

#endif
