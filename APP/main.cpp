#include "bsp.h"
#include <stdio.h>

FATFS fs;
FIL file;
DIR dir;
FRESULT f_res;
UINT fnum;
char WrtBuf[1024];

void BSP_SD_Init()
{
    //Mount
	f_res = f_mount(&fs,"0:",1);
	if(f_res == FR_NO_FILESYSTEM)
	{
		printf("No filesystem, formating...\n");
		f_res=f_mkfs("0:",0,0);								
		if(f_res == FR_OK)
		{
			printf("Format Done!\n");
			
            f_res = f_mount(NULL,"0:",1);
            if(f_res != FR_OK)
                printf("Failed to unmount!\n");
            
			f_res = f_mount(&fs,"0:",1);
			if (f_res != FR_OK)
                printf("Failed to mount!\n");
		}
		else
		{
			printf("Failed to format the SD card!\n");
			while(1);
		}
	}
    else if(f_res!=FR_OK)
    {
        printf("Failed to mount!\n");
        while(1);
    }
    else
        printf("SD card mounterd!\n");
    
    //Create folder
    printf("Trying open the log folder...\n");
    f_res=f_opendir(&dir,"0:LLF_RC_LOG");
    if(f_res!=FR_OK)
    {
        printf("Log folder does not exist!\n");
        f_res=f_mkdir("0:LLF_RC_LOG");
        if(f_res != FR_OK)
        {
            printf("Failed to create folder!\n");
            while(1);
        }
        else
          printf("Folder created!\n");
    }
    else
    {
        printf("Log folder exists!\n");
        
        printf("Trying to close the log folder...\n");
        f_res=f_closedir(&dir);
        if(f_res != FR_OK)
        {
            printf("Failed to close folder!\n");
            while(1);
        }
        else
          printf("Folder closed!\n");
    }
    
    //Create Log file
	printf("Trying to create the log file...\n");	
	f_res = f_open(&file, "0:LLF_RC_LOG/20181212.txt",FA_CREATE_ALWAYS | FA_WRITE);
	if (f_res == FR_OK)
	{   
        printf("Log file opened!\n"); 
        for(int i = 0; i<100; i++)
        {
            int cnt = sprintf(WrtBuf, "%d\n", i);
            f_res = f_write(&file, WrtBuf, cnt, &fnum);
            if(f_res == FR_OK)
            {
                printf("%d write ok!\n", i);
            }
            else
                printf("%d write failed!\n", i);
        }
        f_res = f_close(&file);
        if(f_res == FR_OK)
          printf("log file closed!\n");
        else
          printf("Failed to close the log file!\n");
	}
	else
	{	
		printf("Failed to create the log file!\n");
	}
    
    //Unmount
	f_mount(NULL,"0:",1);
}

void main()
{
    BSP_Init();
    
    BSP_SD_Init();
    
    while(1)
    {
        BSP_LED_Toggle(0);
        BSP_DLY_MS(250);
    }
}