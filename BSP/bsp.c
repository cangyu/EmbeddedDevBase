#include "bsp.h"

void BSP_LED_Init()
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    	
}

void BSP_LED_SetOn(uint8_t idx)
{
    switch(idx)
    {
    case 0:
        GPIO_ResetBits(GPIOB,GPIO_Pin_5);
        break;
    case 1:
        GPIO_ResetBits(GPIOE,GPIO_Pin_5);
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
        GPIO_SetBits(GPIOB,GPIO_Pin_5);
        break;
    case 1:
        GPIO_SetBits(GPIOE,GPIO_Pin_5);
        break;
    default:
        break;
    }
}

void BSP_Init(void)
{
    BSP_LED_Init();
    
    if(!SD_Init())
      printf("SD Card OK!\n");
    else       
        printf("No SD Card!\n");
}

