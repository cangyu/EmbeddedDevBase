#include "bsp.h"

W25QXX_TYPE BSP_W25QXX_LocalInstance = W25QXX_NOT_EXIST;

static inline void BSP_W25QXX_CS_LOW(void)
{
    GPIO_ResetBits(W25QXX_CS_GPIO, W25QXX_CS_PIN);
}

static inline void BSP_W25QXX_CS_HIGH(void)
{
    GPIO_SetBits(W25QXX_CS_GPIO, W25QXX_CS_PIN);
}

static uint8_t BSP_W25QXX_SendByte(uint8_t x)
{
    while (SPI_I2S_GetFlagStatus(W25QXX_SPI_PORT, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(W25QXX_SPI_PORT, x);
    while (SPI_I2S_GetFlagStatus(W25QXX_SPI_PORT, SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_I2S_ReceiveData(W25QXX_SPI_PORT);
}

static uint8_t BSP_W25QXX_GetByte(void)
{
    return BSP_W25QXX_SendByte(W25QXX_DUMMY_BYTE);
}

static uint16_t BSP_W25QXX_GetType(void)
{
    uint16_t ret = 0;
    
    BSP_W25QXX_CS_LOW();
    BSP_W25QXX_SendByte(W25QXX_ManufactDeviceID);
    BSP_W25QXX_SendByte(0x00);
    BSP_W25QXX_SendByte(0x00);
    BSP_W25QXX_SendByte(0x00);
    
    ret |= BSP_W25QXX_GetByte() << 8;
    ret |= BSP_W25QXX_GetByte();
    
    BSP_W25QXX_CS_HIGH();
    return ret;
}

void BSP_W25QXX_Init()
{
    /* Clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
    
    /* GPIO */
    GPIO_InitTypeDef GPIO_InitStructure;

    //W25QXX-CLK
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = W25QXX_SCK_PIN;
    GPIO_Init(W25QXX_SCK_GPIO, &GPIO_InitStructure);
    
    //W25QXX-MISO
    GPIO_InitStructure.GPIO_Pin = W25QXX_MISO_PIN;
    GPIO_Init(W25QXX_MISO_GPIO, &GPIO_InitStructure);
    
    //W25QXX-MOSI
    GPIO_InitStructure.GPIO_Pin = W25QXX_MOSI_PIN;
    GPIO_Init(W25QXX_MOSI_GPIO, &GPIO_InitStructure);
    
    //W25QXX-CS
    GPIO_InitStructure.GPIO_Pin = W25QXX_CS_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(W25QXX_CS_GPIO, &GPIO_InitStructure);
    
    //Deselect the device at startup
    BSP_W25QXX_CS_HIGH(); 

    /* SPI */
    SPI_InitTypeDef SPI_InitStructure;
    
    SPI_I2S_DeInit(W25QXX_SPI_PORT);
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(W25QXX_SPI_PORT, &SPI_InitStructure);
    SPI_Cmd(W25QXX_SPI_PORT, ENABLE);
    
    //There should exist a W25Qxx SPI Flash!
    //Fake or broken otherwise, behaviour undefined!
    BSP_W25QXX_LocalInstance = (W25QXX_TYPE)BSP_W25QXX_GetType();
    if(BSP_W25QXX_LocalInstance == W25Q128)
        printf("W25Q128 detected!\n");
    else if(BSP_W25QXX_LocalInstance == W25Q64)
        printf("W25Q64 detected!\n");
    else
        printf("Fake or broken!\n");
}

void BSP_W25QXX_WriteEnable(void)
{
    BSP_W25QXX_CS_LOW();
    BSP_W25QXX_SendByte(W25QXX_WriteEnable);
    BSP_W25QXX_CS_HIGH();
}

void BSP_W25QXX_WaitForWriteEnd(void)
{
    BSP_W25QXX_CS_LOW();
    BSP_W25QXX_SendByte(W25QXX_ReadStatusReg);
    
    uint8_t FLASH_Status = BSP_W25QXX_SendByte(W25QXX_DUMMY_BYTE);
    while((FLASH_Status & W25QXX_WIP_FLAG) == SET)
    {
        BSP_DLY_MS(10);
        FLASH_Status = BSP_W25QXX_SendByte(W25QXX_DUMMY_BYTE);
    }

    BSP_W25QXX_CS_HIGH();
}

void BSP_W25QXX_PowerDown(void)   
{
    BSP_W25QXX_CS_LOW();
    BSP_W25QXX_SendByte(W25QXX_PowerDown);
    BSP_W25QXX_CS_HIGH();
}

void BSP_W25QXX_WakeUp(void)   
{
    BSP_W25QXX_CS_LOW();
    BSP_W25QXX_SendByte(W25QXX_ReleasePowerDown);
    BSP_W25QXX_CS_HIGH();
}  

void BSP_W25QXX_SectorErase(uint32_t SectorAddr)
{
    BSP_W25QXX_WriteEnable();
    BSP_W25QXX_WaitForWriteEnd();
    BSP_W25QXX_CS_LOW();
    BSP_W25QXX_SendByte(W25QXX_SectorErase);
    BSP_W25QXX_SendByte((SectorAddr & 0xFF0000) >> 16);
    BSP_W25QXX_SendByte((SectorAddr & 0xFF00) >> 8);
    BSP_W25QXX_SendByte(SectorAddr & 0xFF);
    BSP_W25QXX_CS_HIGH();
    BSP_W25QXX_WaitForWriteEnd();
}

void BSP_W25QXX_ChipErase(void)
{
    BSP_W25QXX_WriteEnable();
    BSP_W25QXX_CS_LOW();
    BSP_W25QXX_SendByte(W25QXX_ChipErase);
    BSP_W25QXX_CS_HIGH();
    BSP_W25QXX_WaitForWriteEnd();
}

void BSP_W25QXX_PageWrite(uint8_t *src, uint32_t dst, uint16_t n)
{
    if(n > W25QXX_PAGE_LEN)
        n = W25QXX_PAGE_LEN;
    
    BSP_W25QXX_WriteEnable();
    BSP_W25QXX_CS_LOW();
    BSP_W25QXX_SendByte(W25QXX_PageProgram);
    BSP_W25QXX_SendByte((dst & 0xFF0000) >> 16);
    BSP_W25QXX_SendByte((dst & 0xFF00) >> 8);
    BSP_W25QXX_SendByte(dst & 0xFF);

    while (n--)
        BSP_W25QXX_SendByte(*src++);
    
    BSP_W25QXX_CS_HIGH();
    BSP_W25QXX_WaitForWriteEnd();
}

void BSP_W25QXX_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

    Addr = WriteAddr % W25QXX_PAGE_LEN;
    count = W25QXX_PAGE_LEN - Addr;
    NumOfPage =  NumByteToWrite / W25QXX_PAGE_LEN;
    NumOfSingle = NumByteToWrite % W25QXX_PAGE_LEN;

    if (Addr == 0)
    {
        if (NumOfPage == 0)
        {
            BSP_W25QXX_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
        }
        else
        {
            while (NumOfPage--)
            {
                BSP_W25QXX_PageWrite(pBuffer, WriteAddr, W25QXX_PAGE_LEN);
                WriteAddr += W25QXX_PAGE_LEN;
                pBuffer += W25QXX_PAGE_LEN;
            }

            BSP_W25QXX_PageWrite(pBuffer, WriteAddr, NumOfSingle);
        }
    }
    else
    {
        if (NumOfPage == 0)
        {
            if (NumOfSingle > count)
            {
                temp = NumOfSingle - count;

                BSP_W25QXX_PageWrite(pBuffer, WriteAddr, count);
                WriteAddr +=  count;
                pBuffer += count;

                BSP_W25QXX_PageWrite(pBuffer, WriteAddr, temp);
            }
            else
            {
                BSP_W25QXX_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
            }
        }
        else
        {
            NumByteToWrite -= count;
            NumOfPage =  NumByteToWrite / W25QXX_PAGE_LEN;
            NumOfSingle = NumByteToWrite % W25QXX_PAGE_LEN;

            BSP_W25QXX_PageWrite(pBuffer, WriteAddr, count);
            WriteAddr +=  count;
            pBuffer += count;

            while (NumOfPage--)
            {
                BSP_W25QXX_PageWrite(pBuffer, WriteAddr, W25QXX_PAGE_LEN);
                WriteAddr +=  W25QXX_PAGE_LEN;
                pBuffer += W25QXX_PAGE_LEN;
            }

            if (NumOfSingle != 0)
            {
                BSP_W25QXX_PageWrite(pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}

void BSP_W25QXX_BufferRead(uint8_t *dst, uint32_t src, uint16_t n)
{
    BSP_W25QXX_CS_LOW();
    
    BSP_W25QXX_SendByte(W25QXX_ReadData);
    BSP_W25QXX_SendByte((src & 0xFF0000) >> 16);
    BSP_W25QXX_SendByte((src& 0xFF00) >> 8);
    BSP_W25QXX_SendByte(src & 0xFF);

    while (n--)
        *dst++ = BSP_W25QXX_SendByte(W25QXX_DUMMY_BYTE);

    BSP_W25QXX_CS_HIGH();
}
