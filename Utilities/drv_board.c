#include "drv_board.h"
#include "drv_systick.h"
#include "drv_led.h"
#include "drv_uart.h"
#include "drv_flash.h"


void Board_Init(void)
{
    Delay_Init();
    Time_Init();
    UART_Init();
	
    printf("\n\r1. Start Program!\n\r");
}