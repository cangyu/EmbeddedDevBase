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

    //Initialize common utilities
    BSP_BTN_Init();
    BSP_LED_Init();
    BSP_W25QXX_Init();
    BSP_BLE_Init();
    
    //For possible operation later on
    FLASH_Unlock();
    
    //Avoid legacy HW flaw caused by
    //capacitors connected to the keys!
    //If exist, they will be charged when power on!
    BSP_DLY_MS(200);
}
