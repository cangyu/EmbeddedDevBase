#include "bsp.h"

void BSP_LED_SetOn(uint8_t idx)
{
    switch(idx)
    {
    case 0:
        GPIO_ResetBits(LED0_GPIO,LED0_PIN);
        break;
    case 1:
        GPIO_ResetBits(LED1_GPIO,LED1_PIN);
        break;
    case 2:
        GPIO_ResetBits(LED2_GPIO,LED2_PIN);
        break;
    default:
        break;
    }
}

void BSP_LED_SetOff(uint8_t idx)
{
    switch(idx)
    {
    case 0:
        GPIO_SetBits(LED0_GPIO,LED0_PIN);
        break;
    case 1:
        GPIO_SetBits(LED1_GPIO,LED1_PIN);
        break;
    case 2:
        GPIO_SetBits(LED2_GPIO,LED2_PIN);
        break;
    default:
        break;
    }
}

void BSP_LED_Toggle(uint8_t idx)
{
    switch(idx)
    {
    case 0:
        LED0_GPIO->ODR ^= LED0_PIN;
        break;
    case 1:
        LED1_GPIO->ODR ^= LED1_PIN;
        break;
    case 2:
        LED2_GPIO->ODR ^= LED2_PIN;
        break;
    default:
        break;
    }
}

void BSP_LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = LED0_PIN;
    GPIO_Init(LED0_GPIO, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = LED1_PIN;
    GPIO_Init(LED1_GPIO, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = LED2_PIN;
    GPIO_Init(LED2_GPIO, &GPIO_InitStructure);
    	
    BSP_LED_SetOff(0);
    BSP_LED_SetOff(1);
    BSP_LED_SetOff(2);
}
