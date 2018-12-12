#include "bsp.h"

uint32_t volatile BSP_DLY_COUNTER = 0;

void SysTick_Handler(void)
{
    if(BSP_DLY_COUNTER)
    {
        --BSP_DLY_COUNTER;
    }
}

void BSP_DLY_MS(uint32_t n)
{
    BSP_DLY_COUNTER = n;
    while(BSP_DLY_COUNTER);
}

void BSP_LED_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);

    GPIO_InitStructure.GPIO_Pin = LED1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED1_GPIO, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = LED2_PIN;
    GPIO_Init(LED2_GPIO, &GPIO_InitStructure);
    	
    BSP_LED_SetOff(0);
    BSP_LED_SetOff(1);
}

void BSP_LED_SetOn(uint8_t idx)
{
    switch(idx)
    {
    case 0:
        GPIO_ResetBits(LED1_GPIO,LED1_PIN);
        break;
    case 1:
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
        GPIO_SetBits(LED1_GPIO,LED1_PIN);
        break;
    case 1:
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
        LED1_GPIO->ODR ^= LED1_PIN;
        break;
    case 1:
        LED2_GPIO->ODR ^= LED2_PIN;
        break;
    default:
        break;
    }
}

void BSP_Init(void)
{
    SysTick_Config(SystemCoreClock/1000);
  
    BSP_LED_Init();
}

