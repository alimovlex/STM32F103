#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"              // Keil::Device:StdPeriph Drivers:I2C
#include "delay.h"
#include "uart.h"
#include "dma.h"
#include "timer.h"
#include "i2c.h"
#include "spi.h"
#define SLAVE_ADDRESS		0x08
GPIO_InitTypeDef GPIOInitStruct;
uint8_t receivedByte;
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

void button(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
		// Cofigure PA1 as input with internal pull-up resistor
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOA, &GPIOInitStruct);
	DelayInit();
	
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
	DelayInit();
	
	// Initialize timer interrupt
	TIM2_INT_Init();
	
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
		DelayMs(2500);
		GPIOC->BSRR = GPIO_Pin_13;
		DelayMs(2500);
	}
}

void UART(void)
{
	DelayInit();
	//lcd16x2_init(LCD16X2_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
	
	// Initialize USART with receive interrupt
	USART2_Init();
	
	while (1)
	{
	}
}

void DMA(void)
{
	DelayInit();
	//lcd16x2_init(LCD16X2_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
	
	// Initialize PA0 for button input
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIOInitStruct);
	// Initialize DMA
	DMA1_Init();
	
	// Wait until button is pressed
	//lcd16x2_clrscr();
	//lcd16x2_puts("Press Button to\nStart Transfer");
	while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));
	// Start transfer data using DMA
	DMA_Cmd(DMA1_Channel1, ENABLE);

	while (1)
	{
	}
}

void I2C(void)
{
	DelayInit();
	//lcd16x2_init(LCD16X2_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
	
	// Initialize I2C
	i2c_init();
	
	while (1)
	{
		// Write 0x01 to slave (turn on LED blinking)
		i2c_write(SLAVE_ADDRESS, 0x01);
		DelayMs(5);
		// Read LED blinking status (off/on)
		i2c_read(SLAVE_ADDRESS, &receivedByte);
		// Display LED blinking status
		//lcd16x2_clrscr();
		if (receivedByte == 0)
		{
			//lcd16x2_puts("LED Blinking Off");
		}
		else if (receivedByte == 1)
		{
			//lcd16x2_puts("LED Blinking On");
		}
		DelayMs(2500);
		
		// Write 0x00 to slave (turn off LED blinking)
		i2c_write(SLAVE_ADDRESS, 0x00);
		DelayMs(5);
		// Read LED blinking status (off/on)
		i2c_read(SLAVE_ADDRESS, &receivedByte);
		// Display LED blinking status
		//lcd16x2_clrscr();
		if (receivedByte == 0)
		{
			//lcd16x2_puts("LED Blinking Off");
		}
		else if (receivedByte == 1)
		{
			//lcd16x2_puts("LED Blinking On");
		}
		DelayMs(2500);
	}
}

void SPI(void)
{
	DelayInit();
	//lcd16x2_init(LCD16X2_DISPLAY_ON_CURSOR_OFF_BLINK_OFF);
	
	SPIx_Init();
	
	while (1)
	{
		// Enable slave
		SPIx_EnableSlave();
		// Write command to slave to turn on LED blinking
		SPIx_Transfer((uint8_t) '1');
		DelayUs(10);
		// Write command to slave for asking LED blinking status
		SPIx_Transfer((uint8_t) '?');
		DelayUs(10);
		// Read LED blinking status (off/on) from slave by transmitting dummy byte
		receivedByte = SPIx_Transfer(0);
		// Disable slave
		SPIx_DisableSlave();
		// Display LED blinking status
		//lcd16x2_clrscr();
		if (receivedByte == 0)
		{
			//lcd16x2_puts("LED Blinking Off");
		}
		else if (receivedByte == 1)
		{
			//lcd16x2_puts("LED Blinking On");
		}
		DelayMs(2500);
		
		// Enable slave
		SPIx_EnableSlave();
		// Write command to slave to turn off LED blinking
		SPIx_Transfer((uint8_t) '0');
		DelayUs(10);
		// Write command to slave for asking LED blinking status
		SPIx_Transfer((uint8_t) '?');
		DelayUs(10);
		// Read LED blinking status (off/on) from slave by transmitting dummy byte
		receivedByte = SPIx_Transfer(0);
		// Disable slave
		SPIx_DisableSlave();
		// Display LED blinking status
		//lcd16x2_clrscr();
		if (receivedByte == 0)
		{
			//lcd16x2_puts("LED Blinking Off");
		}
		else if (receivedByte == 1)
		{
			//lcd16x2_puts("LED Blinking On");
		}
		DelayMs(2500);
	}
}
