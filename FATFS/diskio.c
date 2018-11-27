/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "bsp.h"

/* Definitions of physical drive number for each drive */
#define DEV_SD 0        /* Map SD card to physical drive 0 */
#define DEV_W25QXX 1    /* Map Winbond SPI Flash to physical drive 1 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;

	switch (pdrv) 
    {
	case DEV_SD :
        stat = BSP_SD_IsAvailable() ? STA_OK : STA_NODISK;
        break;
	case DEV_W25QXX :
        stat = BSP_W25QXX_IsAvailable() ? STA_OK : STA_NODISK;
        break;
    default:
        stat = STA_NODISK;
	}
    
    return stat;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	switch (pdrv) 
    {
	case DEV_SD:
	case DEV_W25QXX:
		return STA_OK;
    default:
        return STA_NODISK;
	}
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;
	int result;
    
    if(!count)
        return RES_PARERR;

	switch (pdrv)
    {
	case DEV_SD :
		result=SD_WriteDisk((u8*)buff,sector,count);
        res = result ? RES_ERROR : RES_OK;
		return res;
	case DEV_W25QXX :
		return RES_OK;
    default:
        return RES_PARERR;
	}	
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;
	int result;
    
    if(!count)
        return RES_PARERR;

	switch (pdrv)
    {
	case DEV_SD :
		result = SD_WriteDisk((u8*)buff,sector,count);
        res = result ? RES_ERROR : RES_OK;
		return res;
	case DEV_W25QXX :
		return RES_OK;
    default:
        return RES_PARERR;
	}
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	switch (pdrv)
    {
	case DEV_SD:
	case DEV_W25QXX:
        return RES_OK;
    default:
        return RES_PARERR;
	}
}

