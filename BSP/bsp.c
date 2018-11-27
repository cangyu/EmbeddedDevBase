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

    GPIO_InitStructure.GPIO_Pin = LED1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LED1_GPIO, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = LED2_PIN;
    GPIO_Init(LED2_GPIO, &GPIO_InitStructure);
    	
    BSP_LED_SetOff(0);
    BSP_LED_SetOff(1);
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

FRESULT scan_files (
    char* path        /* Start node to be scanned (***also used as work area***) */
)
{
    FRESULT res;
    DIR dir;
    UINT i;
    static FILINFO fno;


    res = f_opendir(&dir, path);                       /* Open the directory */
    if (res == FR_OK) {
        for (;;) {
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
            if (fno.fattrib & AM_DIR) {                    /* It is a directory */
                i = strlen(path);
                sprintf(&path[i], "/%s", fno.fname);
                res = scan_files(path);                    /* Enter the directory */
                if (res != FR_OK) break;
                path[i] = 0;
            } else {                                       /* It is a file. */
                printf("%s/%s\n", path, fno.fname);
            }
        }
        f_closedir(&dir);
    }

    return res;
}

void BSP_Init(void)
{
    SysTick_Config(SystemCoreClock/1000);
  
    BSP_LED_Init();
    BSP_FLAG_SD_EXIST = !SD_Init();
    
    BSP_FS_SD = &BSP_FS_Handle[0];
    BSP_FS_W25QXX = &BSP_FS_Handle[1];
    if(f_mount(BSP_FS_SD, "0:", 1) == FR_OK)
    {
        BSP_LED_SetOn(0);
        char buff[256];
        strcpy(buff, "/");
        scan_files(buff);
    }
    if (f_mount(BSP_FS_W25QXX, "1:", 1) == FR_OK)
    {
        BSP_LED_SetOn(1);
    }
}

