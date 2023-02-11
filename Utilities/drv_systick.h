#ifndef __DRV_SYSTICK_H
#define __DRV_SYSTICK_H

#include "ht32f5xxxx_01.h"

void Delay_Init(void);
void Delay_ms(u32 nTime);
void Delay_Timing(void);

#endif /* __DRV_SYSTICK_H */
