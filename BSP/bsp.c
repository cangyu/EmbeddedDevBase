#include "bsp.h"

bool BSP_FLAG_SD_EXIST = false;
bool BSP_FLAGE_W25QXX_EXIST = true;

FATFS BSP_FS_Handle[2], *BSP_FS_SD, *BSP_FS_W25QXX;

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
    BSP_LED_Init();
    BSP_FLAG_SD_EXIST = !SD_Init();
    
    BSP_FS_SD = &BSP_FS_Handle[0];
    BSP_FS_W25QXX = &BSP_FS_Handle[1];
    
    f_mount(BSP_FS_SD, "0:", 1);
    f_mount(BSP_FS_W25QXX, "1:", 1);
}

