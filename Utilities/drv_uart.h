#ifndef __DRV_UART_H
#define __DRV_UART_H

#include "ht32f5xxxx_01.h"

void UART_Init(void);
u32 UART_PutChar(u32 ch);
u32 UART_GetChar(void);

#endif /* __DRV_UART_H */
