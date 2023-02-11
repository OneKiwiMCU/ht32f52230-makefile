#include "drv_uart.h"

void UART_Init(void)
{
    USART_InitTypeDef USART_InitStructure = {0};
	
    /* Enable peripheral clock of AFIO, UxART                                                               */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{0}};
    CKCUClock.Bit.AFIO                   = 1;
    CKCUClock.Bit.PA = 1;
    CKCUClock.Bit.UART0         = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    /* Turn on UxART Rx internal pull up resistor to prevent unknow state                                     */
    GPIO_PullResistorConfig(HT_GPIOA, GPIO_PIN_5, GPIO_PR_UP);

    /* Config AFIO mode as UxART function.                                                                    */
		//tx
    AFIO_GPxConfig(GPIO_PA, AFIO_PIN_4, AFIO_FUN_USART_UART);//tx
    AFIO_GPxConfig(GPIO_PA, AFIO_PIN_5, AFIO_FUN_USART_UART);//rx

    /* UxART configured as follow:
            - BaudRate = 115200 baud
            - Word Length = 8 Bits
            - One Stop Bit
            - None parity bit
    */

    /* !!! NOTICE !!!
        Notice that the local variable (structure) did not have an initial value.
        Please confirm that there are no missing members in the parameter settings below in this function.
    */
    
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WORDLENGTH_8B;
    USART_InitStructure.USART_StopBits = USART_STOPBITS_1;
    USART_InitStructure.USART_Parity = USART_PARITY_NO;
    USART_InitStructure.USART_Mode = USART_MODE_NORMAL;
    USART_Init(HT_UART0, &USART_InitStructure);

    /* Enable UxART Tx and Rx function                                                                        */
    USART_TxCmd(HT_UART0, ENABLE);
    USART_RxCmd(HT_UART0, ENABLE);
}

u32 UART_PutChar(u32 ch)
{
    while (USART_GetFlagStatus(HT_UART0, USART_FLAG_TXC) == RESET);
    USART_SendData(HT_UART0, ch);
	return ch;
}
u32 UART_GetChar(void)
{
  while (USART_GetFlagStatus(HT_UART0, USART_FLAG_RXDR) == RESET)
  {
  }
  return USART_ReceiveData(HT_UART0);
}


int __backspace(FILE *stream)
{
  if (stream == 0) // Remove the compiler warning
  {
  }
  return 0;
}

int fputc (int ch, FILE *f)
{
  if (f == 0) // Remove the compiler warning
  {
  }
  
  return (UART_PutChar(ch));
}

int fgetc (FILE *f)
{
  if (f == 0) // Remove the compiler warning
  {
  }
  return (UART_GetChar());
}

void _sys_exit(int return_code)
{
  if (return_code == 0) // Remove the compiler warning
  {
  }

label:  goto label;  /* endless loop                                                                        */
}
