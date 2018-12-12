#ifndef __BSP_W25QXX_H__
#define __BSP_W25QXX_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "stm32f10x.h"

#define W25QXX_SPI_PORT SPI3
#define W25QXX_SCK_PIN GPIO_Pin_3
#define W25QXX_SCK_GPIO GPIOB
#define W25QXX_MISO_PIN GPIO_Pin_4
#define W25QXX_MISO_GPIO GPIOB
#define W25QXX_MOSI_PIN GPIO_Pin_5
#define W25QXX_MOSI_GPIO GPIOB
#define W25QXX_CS_PIN GPIO_Pin_6
#define W25QXX_CS_GPIO GPIOB

#define W25QXX_PAGE_LEN 256u
#define W25QXX_SECTOR_LEN 4096u

#define W25QXX_WriteEnable 0x06 
#define W25QXX_WriteDisable 0x04 
#define W25QXX_ReadStatusReg 0x05 
#define W25QXX_WriteStatusReg 0x01 
#define W25QXX_ReadData 0x03 
#define W25QXX_FastReadData 0x0B 
#define W25QXX_FastReadDual 0x3B 
#define W25QXX_PageProgram 0x02 
#define W25QXX_BlockErase 0xD8 
#define W25QXX_SectorErase 0x20 
#define W25QXX_ChipErase 0xC7 
#define W25QXX_PowerDown 0xB9 
#define W25QXX_ReleasePowerDown 0xAB 
#define W25QXX_DeviceID 0xAB 
#define W25QXX_ManufactDeviceID 0x90 
#define W25QXX_JedecDeviceID 0x9F 
#define W25QXX_WIP_FLAG 0x01
#define W25QXX_DUMMY_BYTE 0xFF

typedef enum{
  W25QXX_NOT_EXIST=0,
  W25Q80 = 0xEF13,
  W25Q16 = 0xEF14,
  W25Q32 = 0xEF15,
  W25Q64 = 0xEF16,
  W25Q128 = 0XEF17
}W25QXX_TYPE;

void BSP_W25QXX_Init();

#ifdef __cplusplus
}
#endif

#endif
