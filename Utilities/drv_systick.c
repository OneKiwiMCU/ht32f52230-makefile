#include "drv_systick.h"

static vu32 DelayTime;

void Delay_Init(void)
{
    /* SYSTICK configuration */
    SYSTICK_ClockSourceConfig(SYSTICK_SRC_STCLK);       // Default : CK_AHB/8
    SYSTICK_SetReloadValue(SystemCoreClock / 8 / 1000); // (CK_AHB/8/1000) = 1ms on chip
    SYSTICK_IntConfig(ENABLE);                          // Enable SYSTICK Interrupt
}

void Delay_ms(u32 nTime)
{
    /* Enable the SysTick Counter */
    SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);
    SYSTICK_CounterCmd(SYSTICK_COUNTER_ENABLE);

    DelayTime = nTime;

    while(DelayTime != 0);

    /* Disable SysTick Counter */
    SYSTICK_CounterCmd(SYSTICK_COUNTER_DISABLE);
    /* Clear SysTick Counter */
    SYSTICK_CounterCmd(SYSTICK_COUNTER_CLEAR);
}

void Delay_Timing(void)
{
    if(DelayTime != 0)
    {
        DelayTime--;
    }
}
