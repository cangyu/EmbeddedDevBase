#include "bsp.h"

void BSP_W25_Test()
{
    
}

void main()
{
    BSP_Init();
    
    BSP_W25_Test();
    
    while(1)
    {
        BSP_LED_Toggle(0);
        BSP_DLY_MS(250);
    }
}