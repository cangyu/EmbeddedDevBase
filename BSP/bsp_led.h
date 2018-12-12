#ifndef __BSP_LED_H__
#define __BSP_LED_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "stm32f10x.h"

#define LED0_GPIO GPIOC
#define LED0_PIN GPIO_Pin_0
#define LED1_GPIO GPIOC
#define LED1_PIN GPIO_Pin_6
#define LED2_GPIO GPIOC
#define LED2_PIN GPIO_Pin_7

void BSP_LED_SetOn(uint8_t idx);
void BSP_LED_SetOff(uint8_t idx);
void BSP_LED_Toggle(uint8_t idx);
void BSP_LED_Init(void);

#ifdef __cplusplus
}
#endif

#endif
