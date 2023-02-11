#include "ht32.h"
#include "drv_systick.h"
#include "drv_uart.h"
#include "drv_i2c.h"
#include "drv_mpq8875a.h"
#include <stdio.h>

int main(void)
{
    uint8_t temp = 0;

    Delay_Init();
    //Time_Init();
    i2c_init();
    UART_Init();

    printf("\n\rStart Program!\n\r");

    mpq8875a_read_all_register();
    temp = mpq8875a_read_reference_voltage();
    printf("reference_voltage: 0x%02x\n", temp);

    temp = mpq8875a_read_vout_divider_ratio();
    printf("divider_ratio: 0x%02x\n", temp);

    mpq8875a_write_reference_voltage(0x49);
    mpq8875a_write_vout_divider_ratio(0x05);

    temp = mpq8875a_read_reference_voltage();
    printf("reference_voltage2: 0x%02x\n", temp);

    temp = mpq8875a_read_vout_divider_ratio();
    printf("divider_ratio2: 0x%02x\n", temp);

    while (1)                          
    {

    }
}

#if (HT32_LIB_DEBUG == 1)
/*********************************************************************************************************//**
  * @brief  Report both the error name of the source file and the source line number.
  * @param  filename: pointer to the source file name.
  * @param  uline: error line source number.
  * @retval None
  ***********************************************************************************************************/
void assert_error(u8* filename, u32 uline)
{
  /*
     This function is called by IP library that the invalid parameters has been passed to the library API.
     Debug message can be added here.
     Example: printf("Parameter Error: file %s on line %d\r\n", filename, uline);
  */

    while (1)
    {
    }
}
#endif
