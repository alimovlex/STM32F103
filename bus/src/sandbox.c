#include "stm32f10x_lib.h"
#include "config.h"
#include "usart.h"
//#include "ff.h"
//#define SLAVE_ADDRESS		0x08
GPIO_InitTypeDef GPIOInitStruct;

void LED(void)
{
	 /* Enable GPIOC clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  
  /* Configure PC.4 as Output push-pull */
  GPIOInitStruct.GPIO_Pin = GPIO_Pin_13;
  GPIOInitStruct.GPIO_Speed = GPIO_Speed_10MHz;
  GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIOInitStruct);

  while (1)
  {
    /* Turn on led connected to PC.4 pin */
    GPIO_SetBits(GPIOC, GPIO_Pin_13);
    /* Insert delay */
    Delay(1000);

    /* Turn off led connected to PC.4 pin */
    GPIO_ResetBits(GPIOC, GPIO_Pin_13);
    /* Insert delay */
    Delay(1000);
  }
}

void button(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
		// Cofigure PA1 as input with internal pull-up resistor
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIOInitStruct);
	
	// Initialize GPIOA as output for LED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIOInitStruct);
	
	while (1)
	{
		// If button on PA1 is pressed (button circuit is active low)
		if (!(GPIO_ReadInputData(GPIOA) & GPIO_Pin_0))
		{
			// Turn on LED on PA0 (LED circuit is active low)
			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		}
		else
		{
			// Turn off LED on PA0
			GPIO_SetBits(GPIOC, GPIO_Pin_13);
		}
	}
}

void timer(void)
{

	// Initialize timer interrupt
	TIM1_DeInit();
	
	// Initialize PB12 as push-pull output for LED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIOInitStruct);
	// Initialize PC13 as push-pull output for LED
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOC, &GPIOInitStruct);
	
	while (1)
	{
		// Blink LED on PC13
		GPIOC->BRR = GPIO_Pin_13;
		DelayMC(2500);
		GPIOC->BSRR = GPIO_Pin_13;
		Delay(2500);
	}
}

void usart(void)
{
	USART1_Init();
}
/*
void sd_card(void)
{
	char	buff[1024];	

	FATFS FATFS_Obj;
	DIR dir;
	FIL file;
	UINT nRead, nWritten;
//	static uint8_t ReciveByte=0x00; 		
	USART1_Init();
	f_mount(&FATFS_Obj, "0", 1);
	f_opendir(&dir, "/");
	f_mkdir("0:UARTdata");
  f_open(&file, "0:UARTdata/data.txt", FA_CREATE_NEW | FA_READ | FA_WRITE);
	f_write(&file, &buff, nRead, &nWritten);
	f_close(&file);
	
}
*/
