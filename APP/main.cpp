#include "bsp.h"

void main()
{
    BSP_Init();
      
    while(1)
    {
        BSP_LED_Toggle(0);
        BSP_DLY_MS(250);
    }
}