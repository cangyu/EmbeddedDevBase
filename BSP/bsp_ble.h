#ifndef __BSP_BLE_H__
#define __BSP_BLE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "stm32f10x.h"
  
#define BLE_UART USART1
#define BLE_UART_BAUD 115200
#define BLE_TX_GPIO GPIOA
#define BLE_TX_PIN GPIO_Pin_9
#define BLE_RX_GPIO GPIOA
#define BLE_RX_PIN GPIO_Pin_10


void BSP_BLE_Init(void);

#ifdef __cplusplus
}
#endif

#endif
