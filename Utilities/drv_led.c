#include "drv_led.h"

void LED_Init(void)
{
    /* Enable peripheral clock */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO = 1;
    CKCUClock.Bit.PA = 1;
	CKCUClock.Bit.PB = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);
	
	// LED1
    AFIO_GPxConfig(GPIO_PA, AFIO_PIN_3, AFIO_FUN_GPIO);
    GPIO_PullResistorConfig(HT_GPIOA, GPIO_PIN_3, GPIO_PR_DOWN);
    GPIO_WriteOutBits(HT_GPIOA, GPIO_PIN_3, RESET);
    GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_3, GPIO_DIR_OUT);
	
	//LED2
	AFIO_GPxConfig(GPIO_PB, AFIO_PIN_12, AFIO_FUN_GPIO);
    GPIO_PullResistorConfig(HT_GPIOB, GPIO_PIN_12, GPIO_PR_DOWN);
    GPIO_WriteOutBits(HT_GPIOB, GPIO_PIN_12, RESET);
    GPIO_DirectionConfig(HT_GPIOB, GPIO_PIN_12, GPIO_DIR_OUT);
	
	//LED3
	AFIO_GPxConfig(GPIO_PA, AFIO_PIN_1, AFIO_FUN_GPIO);
    GPIO_PullResistorConfig(HT_GPIOA, GPIO_PIN_1, GPIO_PR_DOWN);
    GPIO_WriteOutBits(HT_GPIOA, GPIO_PIN_1, RESET);
    GPIO_DirectionConfig(HT_GPIOA, GPIO_PIN_1, GPIO_DIR_OUT);
	
	
}

void Button_Init(void)
{
    EXTI_InitTypeDef EXTI_InitStruct;

    /* Enable peripheral clock */
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    CKCUClock.Bit.AFIO = 1;
    CKCUClock.Bit.EXTI = 1;
    CKCUClock.Bit.PB   = 1;
    CKCU_PeripClockConfig(CKCUClock, ENABLE);

    AFIO_GPxConfig(GPIO_PB, AFIO_PIN_0, AFIO_FUN_GPIO);
    GPIO_InputConfig(HT_GPIOB, GPIO_PIN_0, ENABLE);
    GPIO_PullResistorConfig(HT_GPIOB, GPIO_PIN_0, GPIO_PR_DISABLE);
    AFIO_EXTISourceConfig(AFIO_EXTI_CH_0, AFIO_ESS_PB);

    AFIO_GPxConfig(GPIO_PB, AFIO_PIN_1, AFIO_FUN_GPIO);
    GPIO_InputConfig(HT_GPIOB, GPIO_PIN_1, ENABLE);
    GPIO_PullResistorConfig(HT_GPIOB, GPIO_PIN_1, GPIO_PR_DISABLE);
    AFIO_EXTISourceConfig(AFIO_EXTI_CH_1, AFIO_ESS_PB);

    AFIO_GPxConfig(GPIO_PB, AFIO_PIN_2, AFIO_FUN_GPIO);
    GPIO_InputConfig(HT_GPIOB, GPIO_PIN_2, ENABLE);
    GPIO_PullResistorConfig(HT_GPIOB, GPIO_PIN_2, GPIO_PR_DISABLE);
    AFIO_EXTISourceConfig(AFIO_EXTI_CH_2, AFIO_ESS_PB);

    /* Configure EXTI Channel n as rising edge trigger */
    EXTI_InitStruct.EXTI_Channel = EXTI_CHANNEL_0;
    EXTI_InitStruct.EXTI_Debounce = EXTI_DEBOUNCE_DISABLE;
    EXTI_InitStruct.EXTI_DebounceCnt = 0;
    EXTI_InitStruct.EXTI_IntType = EXTI_BOTH_EDGE;
    EXTI_Init(&EXTI_InitStruct);

    EXTI_InitStruct.EXTI_Channel = EXTI_CHANNEL_1;
    EXTI_InitStruct.EXTI_Debounce = EXTI_DEBOUNCE_DISABLE;
    EXTI_InitStruct.EXTI_DebounceCnt = 0;
    EXTI_InitStruct.EXTI_IntType = EXTI_BOTH_EDGE;
    EXTI_Init(&EXTI_InitStruct);

    EXTI_InitStruct.EXTI_Channel = EXTI_CHANNEL_2;
    EXTI_InitStruct.EXTI_Debounce = EXTI_DEBOUNCE_DISABLE;
    EXTI_InitStruct.EXTI_DebounceCnt = 0;
    EXTI_InitStruct.EXTI_IntType = EXTI_BOTH_EDGE;
    EXTI_Init(&EXTI_InitStruct);

    /* Enable EXTI & NVIC line Interrupt */
    EXTI_IntConfig(EXTI_CHANNEL_0, ENABLE);
    NVIC_EnableIRQ(EXTI0_IRQn);

    EXTI_IntConfig(EXTI_CHANNEL_1, ENABLE);
    NVIC_EnableIRQ(EXTI1_IRQn);

    EXTI_IntConfig(EXTI_CHANNEL_2, ENABLE);
    NVIC_EnableIRQ(EXTI2_IRQn);
}

void LED1_On(void)
{
    GPIO_SetOutBits(HT_GPIOA, GPIO_PIN_3);
}

void LED1_Off(void)
{
    GPIO_ClearOutBits(HT_GPIOA, GPIO_PIN_3);
}

void LED1_Toggle(void)
{
	HT_GPIOA->DOUTR ^= GPIO_PIN_3;
}

void LED2_On(void)
{
	GPIO_SetOutBits(HT_GPIOB, GPIO_PIN_12);
}

void LED2_Off(void)
{
	GPIO_ClearOutBits(HT_GPIOB, GPIO_PIN_12);
}

void LED2_Toggle(void)
{
	HT_GPIOB->DOUTR ^= GPIO_PIN_12;
}

void LED3_On(void)
{
	GPIO_SetOutBits(HT_GPIOA, GPIO_PIN_1);
}

void LED3_Off(void)
{
	GPIO_ClearOutBits(HT_GPIOA, GPIO_PIN_1);
}

void LED3_Toggle(void)
{
	HT_GPIOA->DOUTR ^= GPIO_PIN_1;
}
