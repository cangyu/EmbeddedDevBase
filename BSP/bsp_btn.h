#ifndef __BSP_BTN_H__
#define __BSP_BTN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include "stm32f10x.h"


void BSP_BTN_Init(void);
bool BSP_BTN_CheckTrigFlag(void);

#ifdef __cplusplus
}
#endif

#endif
