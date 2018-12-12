#include "bsp.h"

void BSP_BTN_Init(void)
{
    /*Clock*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); 
  
    /*GPIO*/
    GPIO_InitTypeDef GPIO_InitStructure;
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}

bool BSP_BTN_CheckTrigFlag(void)
{
    bool t1 = !GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0);
    bool t2 = !GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5);
    
    return (t1 && t2);
}