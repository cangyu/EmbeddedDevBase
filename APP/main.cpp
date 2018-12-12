#include "bsp.h"

void main()
{
    BSP_Init();
    
    if(BSP_BTN_CheckTrigFlag())
    {
        
    }
    
    while(1)
    {
        BSP_LED_Toggle(1);
        BSP_DLY_MS(250);
    }
}