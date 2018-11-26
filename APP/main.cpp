#include "bsp.h"

void main()
{
    BSP_Init();
      
    while(1)
    {
        //printf("Hello!\n");
        BSP_LED_Toggle(0);
        BSP_DLY_MS(500);
    }
}