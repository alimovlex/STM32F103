#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "delay.h"

GPIO_InitTypeDef GPIOInitStruct;
void LED()
{
		// Initialize delay functions
	DelayInit();
	
	// Initialize GPIOA as output for LED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIOInitStruct);
	
	while (1)
	{
		/* LED blink every 1s */
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		DelayMs(1000);
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		DelayMs(1000);
	}
}

