#include "bsp.h"

uint32_t volatile BSP_DLY_COUNTER = 0;
bool BSP_FLAG_SD_EXIST = false;
bool BSP_FLAGE_W25QXX_EXIST = true;

FATFS BSP_FS_Handle[2], *BSP_FS_SD, *BSP_FS_W25QXX;

void BSP_DLY_MS(uint32_t n)
{
    BSP_DLY_COUNTER = n;
    while(BSP_DLY_COUNTER);
}

void BSP_LED_Init(void)
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

bool BSP_SD_IsAvailable(void)
{
    return BSP_FLAG_SD_EXIST;
}

bool BSP_W25QXX_IsAvailable(void)
{
    return true;
}

void BSP_Init(void)
{
    SysTick_Config(SystemCoreClock/1000);
  
    BSP_LED_Init();
    BSP_FLAG_SD_EXIST = !SD_Init();
    
    BSP_FS_SD = &BSP_FS_Handle[0];
    BSP_FS_W25QXX = &BSP_FS_Handle[1];
    
    f_mount(BSP_FS_SD, "0:", 1);
    f_mount(BSP_FS_W25QXX, "1:", 1);
}

