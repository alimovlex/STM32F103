#include "stm32f10x.h"
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
#include "stm32f10x_dac.h"              // Keil::Device:StdPeriph Drivers:DAC
#include "stm32f10x_dma.h"              // Keil::Device:StdPeriph Drivers:DMA
#include "stm32f10x_i2c.h"              // Keil::Device:StdPeriph Drivers:I2C
#include "stm32f10x_rtc.h"              // Keil::Device:StdPeriph Drivers:RTC
#include "stm32f10x_spi.h"              // Keil::Device:StdPeriph Drivers:SPI
#include "stm32f10x_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include "stm32f10x_wwdg.h"             // Keil::Device:StdPeriph Drivers:WWDG
#include "string.h"
#include "Source.h"
#include "UART.h"

void tutorial::LED()
{
	int i;
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* Initialize LED which connected to PC13 */
  // Enable PORTC Clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_SetBits(GPIOC, GPIO_Pin_13); // Set C13 to High level ("1")
  GPIO_ResetBits(GPIOC, GPIO_Pin_13); // Set C13 to Low level ("0")

  /* Initialize Button input PB0 */
  // Enable PORTB Clock
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  /* Configure the GPIO_BUTTON pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  while (1) 
	{
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) != 0) 
		{
    	/* Toggle LED which connected to PC13*/
    	GPIOC->ODR ^= GPIO_Pin_13; // Invert C13

    	/* delay */
    	for(i=0;i<0x100000;i++);

    	/* Toggle LED which connected to PC13*/
    	GPIOC->ODR ^= GPIO_Pin_13;

    	/* delay */
    	for(i=0;i<0x100000;i++);
    }
    else 
			{
    	GPIO_SetBits(GPIOC, GPIO_Pin_13);
    }

  }
}

void tutorial::UART()
{
	// Set System clock
	SetSysClockTo72();
  volatile char RX_FLAG_END_LINE = 0;
	volatile char RX_BUF[80] = {'\0'};
	/* Initialize LED which connected to PC13 */
	GPIO_InitTypeDef  GPIO_InitStructure;
	// Enable PORTC Clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	/* Configure the GPIO_LED pin */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_ResetBits(GPIOC, GPIO_Pin_13); // Set C13 to Low level ("0")

    // Initialize USART
    usart_init();
    USARTSend(" Hello.\r\nUSART1 is ready.\r\n");

    while (1)
    {
    	if (RX_FLAG_END_LINE == 1) {
    		// Reset END_LINE Flag
    		RX_FLAG_END_LINE = 0;

    		USARTSend("\r\nI has received a line:\r\n");
    		USARTSend(RX_BUF);
    		USARTSend("\r\n");
				
    		clear_RXBuffer();
    	}
    }
}

void tutorial::watchdog()
{
	/* Initialize Leds mounted on STM32 board */
  GPIO_InitTypeDef  GPIO_InitStructure;
  /* Initialize LED which connected to PC13, Enable the Clock*/
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* Disable LED */
  GPIO_SetBits(GPIOC, GPIO_Pin_13);

  /* Enable Watchdog*/
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);
  WWDG_DeInit();
  WWDG_SetPrescaler(WWDG_Prescaler_8); //1, 2, 4, 8
  WWDG_SetWindowValue(127); // 64...127
  WWDG_Enable(100);
  WWDG_EnableIT();

  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;    /*WWDG interrupt*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);/*    NVIC initialization*/

  while (1)
  {

  }
}
void init()
{
	tutorial a;
	a.UART();
}


