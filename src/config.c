#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
void Delay(uint32_t ms)
{
        volatile uint32_t nCount;
        RCC_ClocksTypeDef RCC_Clocks;
        RCC_GetClocksFreq (&RCC_Clocks);

        nCount=(RCC_Clocks.HCLK_Frequency/10000)*ms;
        for (; nCount!=0; nCount--);
}


void DelayMC(uint32_t mc)
{
        volatile uint32_t nCount;
        RCC_ClocksTypeDef RCC_Clocks;
        RCC_GetClocksFreq (&RCC_Clocks);

        nCount=(RCC_Clocks.HCLK_Frequency/10000000)*mc;
        for (; nCount!=0; nCount--);
}

void init_leds()
{
  GPIO_InitTypeDef GPIOInitStruct;

    /* Enable GPIOC clock */
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

 /* Configure PC.4 as Output push-pull */
 GPIOInitStruct.GPIO_Pin = GPIO_Pin_13;
 GPIOInitStruct.GPIO_Speed = GPIO_Speed_10MHz;
 GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_Init(GPIOC, &GPIOInitStruct);
}
