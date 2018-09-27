#include "bsp.h"

void delay_ms(uint32_t n)
{
    uint32_t tmp = 0;
    
    for(uint32_t i = 0; i< n; i++)
      for(uint32_t j = 0; j<80; j++)
        for(uint32_t k = 0; k<90; k++)
          tmp += 1;
}

void main()
{
    BSP_Init();
      
    while(1)
    {
        printf("Test\n");
        delay_ms(300);
    }
}