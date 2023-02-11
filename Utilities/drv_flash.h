#ifndef __DRV_FLASH_H
#define __DRV_FLASH_H

#include "ht32f5xxxx_01.h"


#define ADDRESS_TIME1       0x6C00  //(1024 * 27)
#define ADDRESS_TIME2       0x7000  //(1024 * 28)
#define ADDRESS_TIME3       0x7400  //(1024 * 29)

void FLASH_Erase(u32 addr);
void FLASH_Write(u32 addr, u32 data);
u32 FLASH_Read(u32 addr);

#endif /* __DRV_FLASH_H */
