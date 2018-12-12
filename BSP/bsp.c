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

void BSP_Init(void)
{
    //Systick interrupt set to 1000 Hz
    SysTick_Config(SystemCoreClock/1000);
    
    //Order of following statements MUST be kept!
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); 

    BSP_LED_Init();
    BSP_W25QXX_Init();
}
