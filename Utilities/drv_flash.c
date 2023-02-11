#include "drv_flash.h"

void FLASH_Erase(u32 addr)
{
    FLASH_State FLASHState;
    FLASHState = FLASH_ErasePage(addr);
    if (FLASHState != FLASH_COMPLETE){
        //error
    }
}

void FLASH_Write(u32 addr, u32 data)
{
    FLASH_State FLASHState;
    FLASHState = FLASH_ProgramWordData(addr, data);
    if (FLASHState != FLASH_COMPLETE){
        //err++;
    }
}

u32 FLASH_Read(u32 addr)
{
    return rw(addr);
}
