#include "bsp.h"

FATFS fs;
FIL file;
FRESULT f_res;
UINT fnum;
BYTE ReadBuffer[1024]={0};
BYTE WriteBuffer[] = {"LLF RC LOG.\n"};

void main()
{
    BSP_Init();
    
    printf("Testing FATFS over SD card...\n");
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
    
	f_mount(NULL,"0:",1);
      
    while(1)
    {
        BSP_LED_Toggle(0);
        BSP_DLY_MS(250);
    }
}